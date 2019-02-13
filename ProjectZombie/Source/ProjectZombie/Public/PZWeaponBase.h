// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PZWeaponBase.generated.h"

UCLASS()
class PROJECTZOMBIE_API APZWeaponBase : public AActor
{
	GENERATED_BODY()
	
public:	
	APZWeaponBase();

private:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Mesh", meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* Mesh;

public:
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	virtual void StartFire();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	virtual void StopFire();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	virtual void StartAltFire();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	virtual void StopAltFire();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void AttachToOwner();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void DetachFromOwner();
};
