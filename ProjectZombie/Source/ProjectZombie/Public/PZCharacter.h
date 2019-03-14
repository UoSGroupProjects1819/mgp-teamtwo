// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PZCharacterBase.h"
#include "PZCharacter.generated.h"

class UCameraComponent;
class UPawnNoiseEmitterComponent;
class UPZCharacterMovement;
class UPhysicsHandleComponent;
class USoundBase;

UCLASS()
class PROJECTZOMBIE_API APZCharacter : public APZCharacterBase
{
	GENERATED_BODY()

public:
	APZCharacter(const FObjectInitializer& ObjectInitializer);

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

	/** Scene component, used to carry physics actor */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character", meta = (AllowPrivateAccess = "true"))
	USceneComponent* SceneComp;

	/** Physics handle component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character", meta = (AllowPrivateAccess = "true"))
	UPhysicsHandleComponent* PhysicsHandleComp;


public:	
	// Being ACharcter interface.
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End ACharacter interface.

	/** Called every time character makes a sound in the game. */
	UFUNCTION(BlueprintCallable, Category = "Pawn")
	virtual void CreateNoise(USoundBase* Sound, float Volume);

	/** Sound played by footsteps. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pawn")
	USoundBase* FootstepSound;

	/** Handles moving forward */
	UFUNCTION(BlueprintCallable, Category = "Pawn")
	void MoveForward(float Value);

	/** Handles moving backward */
	UFUNCTION(BlueprintCallable, Category = "Pawn")
	void MoveBackward(float Value);

	/** Handles strafing movement right */
	UFUNCTION(BlueprintCallable, Category = "Pawn")
	void MoveRight(float Value);

	/** Handles strafing movement left */
	UFUNCTION(BlueprintCallable, Category = "Pawn")
	void MoveLeft(float Value);

	/** Make the character sprint */
	UFUNCTION(BlueprintCallable, Category = "Pawm")
	virtual void Sprint();

	/** Stop the character from sprinting. */
	UFUNCTION(BlueprintCallable, Category = "Pawn")
	virtual void StopSprinting();

	/** Make the character crouch. */
	UFUNCTION(BlueprintCallable, Category = "Pawn")
	virtual void StartCrouch();

	/** Make the character crouch. */
	UFUNCTION(BlueprintCallable, Category = "Pawn")
	virtual void StopCrouch();

	/** Make the character crouch, toggled version. */
	UFUNCTION(BlueprintCallable, Category = "Pawn")
	virtual void ToggleCrouch();

	/** Pickup up physics actor. */
	UFUNCTION(BlueprintCallable, Category = "Pawn")
	virtual void OnPickup();

	/** Throw player held physics actor. */
	UFUNCTION(BlueprintCallable, Category = "Pawn")
	virtual void OnThrow();

	/** Drop player held physics actor. */
	UFUNCTION(BlueprintCallable, Category = "Pawn")
	virtual void OnDropped();

	/** True if player is currently carrying a physics actor. */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Pawn")
	bool bIsCarryingActor;

	/** Max pickup distance for p[physics actors. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pawn")
	float PickupDistance;

	/** Launch velocity when throwing pickup physics actors. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pawn")
	float LaunchVelocity;

	/** Currently held physics actor. */
	UPROPERTY(BlueprintReadOnly, Category = "Pawn")
	UPrimitiveComponent* CurrentPickup;

protected:
	/** Fire a ray trace from the players camera. */
	FHitResult RayTrace(const FVector StartTrace, const FVector EndTrace) const;

public:
	/** Returns FirstPersonMesh subobject. */
	FORCEINLINE USkeletalMeshComponent* GetFirstPersonMesh() const { return FirstPersonMesh; }

	/** Returns FirstPersonCamera subobject. */
	FORCEINLINE UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }
};
