// Fill out your copyright notice in the Description page of Project Settings.

#include "PZCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/PawnNoiseEmitterComponent.h"
#include "Perception/PawnSensingComponent.h"
#include "PZWeaponBase.h"
#include "PZCharacterMovement.h"

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

	PZCharacterMovement = Cast<UPZCharacterMovement>(GetCharacterMovement());

	// Create a PawnNoiseEmitterComponent which will be used to emit sounds to AI characters.
	PawnNoiseEmitterComp = CreateDefaultSubobject<UPawnNoiseEmitterComponent>(TEXT("PawnNoiseEmitterComp"));

	Health = 0;
	MaxHealth = 100;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void APZCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if (Health == 0)
	{
		Health = MaxHealth;
	}

	CreateInventory();
}

void APZCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
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

	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &APZCharacter::StartFire);
	PlayerInputComponent->BindAction("Fire", IE_Released, this, &APZCharacter::StopAltFire);
	PlayerInputComponent->BindAction("AltFire", IE_Pressed, this, &APZCharacter::StartAltFire);
	PlayerInputComponent->BindAction("AltFire", IE_Released, this, &APZCharacter::StopAltFire);
}

void APZCharacter::CreateNoise(USoundBase* Sound, float Volume)
{
	if (Sound)
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), Sound, GetActorLocation());

		MakeNoise(Volume, this, GetActorLocation());
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

void APZCharacter::StartFire()
{
	if (Weapon)
	{
		Weapon->StartFire();
	}
}

void APZCharacter::StopFire()
{
	if (Weapon)
	{
		Weapon->StopFire();
	}
}

void APZCharacter::StartAltFire()
{
	if (Weapon)
	{
		Weapon->StartAltFire();
	}
}

void APZCharacter::StopAltFire()
{
	if (Weapon)
	{
		Weapon->StopAltFire();
	}
}

void APZCharacter::CreateInventory()
{
	for (int32 i = 0; i < DefaultInventoryClasses.Num(); i++)
	{
		if (DefaultInventoryClasses[i])
		{
			FActorSpawnParameters SpawnInfo;
			SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
			APZWeaponBase* Weap =  GetWorld()->SpawnActor<APZWeaponBase>(DefaultInventoryClasses[i], SpawnInfo);
			AddWeapon(Weap);
		}
	}

	if (Inventory.Num() > 0)
	{
		EquipWeapon(Inventory[0]);
	}
}

void APZCharacter::DestroyInventory()
{

}

void APZCharacter::AddWeapon(APZWeaponBase* Weap)
{
	if (Weap)
	{
		Weap->GivenTo(this);
		Inventory.AddUnique(Weap);
	}
}

void APZCharacter::RemoveWeapon(APZWeaponBase* Weap)
{
	if (Weap)
	{
		Weap->Removed();
		Inventory.Remove(Weap);
	}
}

void APZCharacter::EquipWeapon(APZWeaponBase* Weap)
{
	if (Weap)
	{
		Weap->AttachToOwner();
		Weapon = Weap;
	}
}

