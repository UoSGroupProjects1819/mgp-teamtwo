// Fill out your copyright notice in the Description page of Project Settings.

#include "PZCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/PawnNoiseEmitterComponent.h"
#include "Perception/PawnSensingComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "DrawDebugHelpers.h"
#include "PZCharacterMovement.h"
#include "PZPhysicsActor.h"

#define COLLISION_PICKUP ECC_GameTraceChannel1

APZCharacter::APZCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UPZCharacterMovement>(ACharacter::CharacterMovementComponentName))
{
	// Create a CameraComponent
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->RelativeLocation = FVector(0, 0, BaseEyeHeight);
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person view' (when controlling this pawn)
	FirstPersonMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	FirstPersonMesh->SetupAttachment(FirstPersonCameraComponent);
	FirstPersonMesh->SetOnlyOwnerSee(true);
	FirstPersonMesh->bCastDynamicShadow = false;
	FirstPersonMesh->CastShadow = false;
	FirstPersonMesh->bReceivesDecals = false;
	FirstPersonMesh->MeshComponentUpdateFlag = EMeshComponentUpdateFlag::OnlyTickPoseWhenRendered;
	FirstPersonMesh->PrimaryComponentTick.AddPrerequisite(this, PrimaryActorTick);

	// Cached character movement component
	PZCharacterMovement = Cast<UPZCharacterMovement>(GetCharacterMovement());

	// Create a PawnNoiseEmitterComponent which will be used to emit sounds to AI characters.
	PawnNoiseEmitterComp = CreateDefaultSubobject<UPawnNoiseEmitterComponent>(TEXT("PawnNoiseEmitterComp"));

	SceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComp"));
	SceneComp->SetupAttachment(FirstPersonMesh);

	PhysicsHandleComp = CreateDefaultSubobject<UPhysicsHandleComponent>(TEXT("PhysicsHandle"));

	Health = 0;
	MaxHealth = 100;
	PickupDistance = 150.0f;
	LaunchVelocity = 1000.0f;
	MaxOutlineDistance = 150.0f;
	bHasNewFocus = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void APZCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if (Health == 0)
	{
		Health = MaxHealth;
	}
}

void APZCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Controller)
	{
		APZPhysicsActor* Actor = GetPhysicsActorInView();
		if (CurrentPhysicsActor != Actor)
		{
			if (CurrentPhysicsActor)
			{
				CurrentPhysicsActor->OnEndFocus();
			}

			bHasNewFocus = true;
		}

		CurrentPhysicsActor = Actor;
		if (Actor)
		{
			if (bHasNewFocus)
			{
				Actor->OnStartFocus();
				UE_LOG(LogTemp, Display, TEXT("Hit Pickup"))
				bHasNewFocus = false;
			}
		}
	}

	if (bIsCarryingActor)
	{
		const FVector CarryLocation = SceneComp->GetComponentLocation();
		PhysicsHandleComp->SetTargetLocation(CarryLocation);
	}
}

void APZCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &APZCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveBackward", this, &APZCharacter::MoveBackward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APZCharacter::MoveRight);
	PlayerInputComponent->BindAxis("MoveLeft", this, &APZCharacter::MoveLeft);
	PlayerInputComponent->BindAxis("Turn", this, &APZCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APZCharacter::AddControllerPitchInput);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &APZCharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &APZCharacter::StopJumping);
	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &APZCharacter::Sprint);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &APZCharacter::StopSprinting);
	PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &APZCharacter::StartCrouch);
	PlayerInputComponent->BindAction("Crouch", IE_Released, this, &APZCharacter::StopCrouch);
	PlayerInputComponent->BindAction("ToggleCrouch", IE_Pressed, this, &APZCharacter::ToggleCrouch);

	PlayerInputComponent->BindAction("Pickup", IE_Pressed, this, &APZCharacter::OnPickup);
	PlayerInputComponent->BindAction("Drop", IE_Pressed, this, &APZCharacter::OnDropped);
	PlayerInputComponent->BindAction("Throw", IE_Pressed, this, &APZCharacter::OnThrow);
}

APZPhysicsActor* APZCharacter::GetPhysicsActorInView()
{
	FVector CamLoc;
	FRotator CamRot;

	if (Controller == nullptr)
		return nullptr;

	Controller->GetPlayerViewPoint(CamLoc, CamRot);
	const FVector StartTrace = CamLoc;
	const FVector Direction = CamRot.Vector();
	const FVector EndTrace = StartTrace + (Direction * MaxOutlineDistance);
	const FHitResult Hit = RayTrace(StartTrace, EndTrace);
	if (Hit.bBlockingHit)
	{
		return Cast<APZPhysicsActor>(Hit.GetActor());
	}

	return nullptr;
}

void APZCharacter::CreateNoise(USoundBase* Sound, float Volume)
{
	if (Sound)
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), Sound, GetActorLocation());
		MakeNoise(Volume, this, GetActorLocation());

		LastNoiseVolume = Volume;
		LastNoiseTime = GetWorld()->GetTimeSeconds();
	}
}

void APZCharacter::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		// Find out which way is forward
		const FRotator Rotation = GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// Add movement in forward direction
		AddMovementInput(Direction, Value);
	}
}

void APZCharacter::MoveBackward(float Value)
{
	MoveForward(Value * -1);
}

void APZCharacter::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		// Find out which way is right
		const FRotator Rotation = GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// Add movement in right direction
		AddMovementInput(Direction, Value);
	}
}

void APZCharacter::MoveLeft(float Value)
{
	MoveRight(Value * -1);
}

void APZCharacter::Sprint()
{
	if (PZCharacterMovement)
	{
		PZCharacterMovement->bIsSprinting = true;
	}
}

void APZCharacter::StopSprinting()
{
	if (PZCharacterMovement)
	{
		PZCharacterMovement->bIsSprinting = false;
	}
}

void APZCharacter::StartCrouch()
{
	Crouch(false);
}

void APZCharacter::StopCrouch()
{
	UnCrouch(false);
}

void APZCharacter::ToggleCrouch()
{
	bIsCrouched ? UnCrouch(false) : Crouch(false);
}

void APZCharacter::OnPickup()
{
	if (!bIsCarryingActor)
	{
		if (Controller)
		{
			FVector StartTrace = FVector::ZeroVector;
			FVector ShootDir = FVector::ZeroVector;
			FRotator CamRot = FRotator::ZeroRotator;

			Controller->GetPlayerViewPoint(StartTrace, CamRot);
			ShootDir = CamRot.Vector();
			StartTrace = StartTrace + ShootDir * ((GetActorLocation() - StartTrace) | ShootDir);

			const FVector EndTrace = StartTrace + ShootDir * PickupDistance;
			const FHitResult Impact = RayTrace(StartTrace, EndTrace);
			if (Impact.bBlockingHit)
			{
				UPrimitiveComponent* PhysicsComponent = Impact.GetComponent();
				if (PhysicsComponent != nullptr && PhysicsComponent->IsSimulatingPhysics())
				{
					PhysicsHandleComp->GrabComponentAtLocationWithRotation(PhysicsComponent, NAME_None, PhysicsComponent->GetComponentLocation(), PhysicsComponent->GetComponentRotation());
					CurrentPickup = PhysicsComponent;
					bIsCarryingActor = true;
					UE_LOG(LogTemp, Display, TEXT("Caryying Pickup"))
				}
			}
		}
	}
}

void APZCharacter::OnThrow()
{
	if (bIsCarryingActor && CurrentPickup != nullptr)
	{
		const FVector LaunchDirection = GetActorForwardVector();
		const FRotator LauncRotation = GetControlRotation();
		const FVector Direction = LaunchDirection + LauncRotation.Vector();
		CurrentPickup->AddImpulse(Direction * LaunchVelocity, NAME_None, true);
		UE_LOG(LogTemp, Display, TEXT("Thrown Pickup"))
		OnDropped();
	}
}

void APZCharacter::OnDropped()
{
	if (bIsCarryingActor)
	{
		PhysicsHandleComp->ReleaseComponent();
		CurrentPickup = nullptr;
		bIsCarryingActor = false;
		UE_LOG(LogTemp, Display, TEXT("Dropped Pickup"))
	}
}

FHitResult APZCharacter::RayTrace(const FVector StartTrace, const FVector EndTrace) const
{
	FCollisionQueryParams TraceParams(SCENE_QUERY_STAT(RayTrace), true, Instigator);
	TraceParams.bTraceAsyncScene = true;
	TraceParams.bReturnPhysicalMaterial = true;
	TraceParams.bTraceComplex = true;

	FHitResult Hit(ForceInit);
	GetWorld()->LineTraceSingleByChannel(Hit, StartTrace, EndTrace, COLLISION_PICKUP, TraceParams);
	return Hit;
}

