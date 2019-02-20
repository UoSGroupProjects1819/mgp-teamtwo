// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PZWeaponBase.generated.h"

class APZCharacter;

UCLASS(Abstract, Blueprintable)
class PROJECTZOMBIE_API APZWeaponBase : public AActor
{
	GENERATED_BODY()
	
public:	
	APZWeaponBase();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	FName HandsAttachSocket;

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

	virtual void GivenTo(APZCharacter* NewOwner);
	virtual void Removed();

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Weapon")
	APZCharacter* PZOwner;

	FHitResult WeaponTrace(const FVector& StartTrace, const FVector& EndTrace) const;

public:
	FORCEINLINE USkeletalMeshComponent* GetMesh() const { return Mesh; }
};
