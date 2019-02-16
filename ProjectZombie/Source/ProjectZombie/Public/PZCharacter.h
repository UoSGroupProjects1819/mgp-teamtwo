// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PZCharacterBase.h"
#include "PZCharacter.generated.h"

class UCameraComponent;
class APZWeaponBase;

UCLASS()
class PROJECTZOMBIE_API APZCharacter : public APZCharacterBase
{
	GENERATED_BODY()

public:
	APZCharacter();

private:
	/** First person mesh */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Mesh", meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* FirstPersonMesh;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/** Handles moving forward */
	void MoveForward(float Value);

	/** Handles moving backward */
	void MoveBackward(float Value);

	/** Handles strafing movement right */
	void MoveRight(float Value);

	/** Handles strafing movement left */
	void MoveLeft(float Value);

	UFUNCTION(BlueprintCallable, Category = "Pawn")
	void CreateInventory();

	UFUNCTION(BlueprintCallable, Category = "Pawn")
	void DestroyInventory();

	UFUNCTION(BlueprintCallable, Category = "Pawn")
	void AddWeapon(APZWeaponBase* Weap);

	UFUNCTION(BlueprintCallable, Category = "Pawn")
	void RemoveWeapon(APZWeaponBase* Weap);

	UFUNCTION(BlueprintCallable, Category = "Pawn")
	void EquipWeapon(APZWeaponBase* Weap);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pawn")
	TArray<TSubclassOf<APZWeaponBase>> DefaultInventoryClasses;

	UPROPERTY(BlueprintReadOnly, Category = "Pawn")
	TArray<APZWeaponBase*> Inventory;

	UPROPERTY(BlueprintReadOnly, Category = "Pawn")
	APZWeaponBase* Weapon;

	FORCEINLINE USkeletalMeshComponent* GetFirstPersonMesh() const { return FirstPersonMesh; }
	FORCEINLINE UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }
};
