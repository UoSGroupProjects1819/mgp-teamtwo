// Fill out your copyright notice in the Description page of Project Settings.

#include "PZCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "PZCharacter.h"
#include "PZWeaponBase.h"

APZCharacter::APZCharacter()
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
	FirstPersonMesh->MeshComponentUpdateFlag = EMeshComponentUpdateFlag::OnlyTickPoseWhenRendered;

	MaxHealth = 100;

	PrimaryActorTick.bCanEverTick = true;
}

void APZCharacter::BeginPlay()
{
	Super::BeginPlay();
	
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
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &APZCharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &APZCharacter::StopJumping);
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

void APZCharacter::CreateInventory()
{
	for (int32 i = 0; i < DefaultInventoryClasses.Num(); i++)
	{

	}
}

void APZCharacter::DestroyInventory()
{

}

void APZCharacter::AddWeapon(APZWeaponBase* Weap)
{
	if (Weap)
	{
		Inventory.AddUnique(Weap);
		Weap->GivenTo(this);
	}
}

void APZCharacter::RemoveWeapon(APZWeaponBase* Weap)
{
	if (Weap)
	{
		Inventory.Remove(Weap);
		Weap->Removed();
	}
}

void APZCharacter::EquipWeapon(APZWeaponBase* Weap)
{
	if (Weap)
	{
		Weapon = Weap;
	}
}

