// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PZCharacterBase.h"
#include "PZCharacter.generated.h"

class UCameraComponent;
class UPawnNoiseEmitterComponent;
class USoundBase;
class APZWeaponBase;
class UPZCharacterMovement;

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

	/** Cached PZCharacterMovement casted CharacterMovement */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character", meta = (AllowPrivateAccess = "true"))
	UPZCharacterMovement* PZCharacterMovement;

	/** Noise Emitter component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character", meta = (AllowPrivateAccess = "true"))
	UPawnNoiseEmitterComponent* PawnNoiseEmitterComp;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/** Called every time character makes a sound in the game. */
	UFUNCTION(BlueprintCallable, Category = "Pawn")
	virtual void CreateNoise(USoundBase* Sound, float Volume);

	/** Handles moving forward */
	void MoveForward(float Value);

	/** Handles moving backward */
	void MoveBackward(float Value);

	/** Handles strafing movement right */
	void MoveRight(float Value);

	/** Handles strafing movement left */
	void MoveLeft(float Value);

	/** Spawn weapon in character inventory. */
	UFUNCTION(BlueprintCallable, Category = "Pawn")
	void CreateInventory();

	/** Remove all weapons from character inventory. */
	UFUNCTION(BlueprintCallable, Category = "Pawn")
	void DestroyInventory();

	/** Add weapon to character inventory. */
	UFUNCTION(BlueprintCallable, Category = "Pawn")
	void AddWeapon(APZWeaponBase* Weap);

	/** Remove weapon from character inventory. */
	UFUNCTION(BlueprintCallable, Category = "Pawn")
	void RemoveWeapon(APZWeaponBase* Weap);

	/** Equip weapon from character inventory. */
	UFUNCTION(BlueprintCallable, Category = "Pawn")
	void EquipWeapon(APZWeaponBase* Weap);

	/** List of default weapons to spawn in character inventory. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pawn")
	TArray<TSubclassOf<APZWeaponBase>> DefaultInventoryClasses;

	/** List of items in player inventory. */
	UPROPERTY(BlueprintReadOnly, Category = "Pawn")
	TArray<APZWeaponBase*> Inventory;

	/** Weapon currently equipped by character. */
	UPROPERTY(BlueprintReadOnly, Category = "Pawn")
	APZWeaponBase* Weapon;

	/** Returns FirstPersonMesh subobject. */
	FORCEINLINE USkeletalMeshComponent* GetFirstPersonMesh() const { return FirstPersonMesh; }

	/** Returns FirstPersonCamera subobject. */
	FORCEINLINE UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }
};
