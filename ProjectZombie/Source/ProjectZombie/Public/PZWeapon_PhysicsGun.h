// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PZWeaponBase.h"
#include "PZWeapon_PhysicsGun.generated.h"

class UPhysicsHandleComponent;

UCLASS()
class PROJECTZOMBIE_API APZWeapon_PhysicsGun : public APZWeaponBase
{
	GENERATED_BODY()

public:
	APZWeapon_PhysicsGun();

	virtual void Tick(float DeltaSeconds) override;

	virtual void StartFire();
	virtual void StopFire();
	virtual void StartAltFire();
	virtual void StopAltFire();

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
	USceneComponent* PickupLocation;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
	UPhysicsHandleComponent* PhysicsHandleComp;

public:
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void OnPickup();

	UFUNCTION(BlueprintCallable, Category = "Wepaon")
	void OnDropped();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void OnLaunched();

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	bool bIsCarrying;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	float PickupDistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	float LaunchVelocity;

	UPROPERTY(BlueprintReadOnly, Category = "Weapon")
	UPrimitiveComponent* PickedUpObject;
};
