// Fill out your copyright notice in the Description page of Project Settings.

#include "PZWeapon_PhysicsGun.h"
#include "Kismet/GameplayStatics.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "PZCharacter.h"

APZWeapon_PhysicsGun::APZWeapon_PhysicsGun()
{
	PickupLocation = CreateDefaultSubobject<USceneComponent>(TEXT("PickupLocation"));
	PickupLocation->SetupAttachment(GetMesh());

	PhysicsHandleComp = CreateDefaultSubobject<UPhysicsHandleComponent>(TEXT("PhysicsHandle"));

	PickupDistance = 500.0f;
	LaunchVelocity = 1200.0f;
	bIsCarrying = false;

	PrimaryActorTick.bCanEverTick = true;
}

void APZWeapon_PhysicsGun::Tick(float DeltaSeconds)
{
	if (bIsCarrying)
	{
		const FVector NewLocation = PickupLocation->GetComponentLocation();
		PhysicsHandleComp->SetTargetLocation(NewLocation);
	}
}

void APZWeapon_PhysicsGun::StartFire()
{
	if (!bIsCarrying)
	{
		OnPickup();
	}
	else
	{
		OnDropped();
	}
}

void APZWeapon_PhysicsGun::StopFire()
{

}

void APZWeapon_PhysicsGun::StartAltFire()
{
	if (bIsCarrying)
	{
		OnLaunched();
	}
}

void APZWeapon_PhysicsGun::StopAltFire()
{

}

void APZWeapon_PhysicsGun::OnPickup()
{
	if (!bIsCarrying)
	{
		APlayerController* PlayerController = Cast<APlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
		if (PlayerController)
		{
			FVector StartTrace = FVector::ZeroVector;
			FVector ShootDir = FVector::ZeroVector;
			FRotator CamRot = FRotator::ZeroRotator;

			PlayerController->GetPlayerViewPoint(StartTrace, CamRot);
			ShootDir = CamRot.Vector();
			StartTrace = StartTrace + ShootDir * ((PZOwner->GetActorLocation() - StartTrace) | ShootDir);

			const FVector EndTrace = StartTrace + ShootDir * PickupDistance;
			const FHitResult Impact = WeaponTrace(StartTrace, EndTrace);
			if (Impact.bBlockingHit)
			{
				UE_LOG(LogTemp, Display, TEXT("Hit"))
				UPrimitiveComponent* PhysicsComponent = Impact.GetComponent();
				if (PhysicsComponent != nullptr && PhysicsComponent->IsSimulatingPhysics())
				{
					PhysicsHandleComp->GrabComponentAtLocationWithRotation(PhysicsComponent, NAME_None, PhysicsComponent->GetComponentLocation(), PhysicsComponent->GetComponentRotation());
					PickedUpObject = PhysicsComponent;
					bIsCarrying = true;
					UE_LOG(LogTemp, Display, TEXT("Pickup"))
				}
			}
		}
	}
}

void APZWeapon_PhysicsGun::OnDropped()
{
	if (bIsCarrying)
	{
		PhysicsHandleComp->ReleaseComponent();
		PickedUpObject = nullptr;
		bIsCarrying = false;
		UE_LOG(LogTemp, Display, TEXT("Release"))
	}
}

void APZWeapon_PhysicsGun::OnLaunched()
{
	if (PickedUpObject)
	{
		const FVector LaunchDirection = PZOwner->GetActorForwardVector();
		const FRotator LauncRotation = PZOwner->GetControlRotation();
		const FVector Direction = LaunchDirection + LauncRotation.Vector();
		PickedUpObject->AddImpulse(Direction * LaunchVelocity, NAME_None, true);
		OnDropped();
	}
}
