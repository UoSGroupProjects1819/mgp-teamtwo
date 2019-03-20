// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PZCharacterBase.h"
#include "PZZombie.generated.h"

class UPawnSensingComponent;
class UAIPerceptionComponent;
class UBehaviorTree;

UCLASS()
class PROJECTZOMBIE_API APZZombie : public APZCharacterBase
{
	GENERATED_BODY()
	
public:
	/** Default UObject constructor. */
	APZZombie(const FObjectInitializer& ObjectInitializer);

	virtual void Tick(float DeltaSeconds) override;
	virtual void BeginPlay() override;

private:
	/** AI sensing component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI", meta = (AllowPrivateAccess = "true"))
	UPawnSensingComponent* PawnSensingComp;

	/** Melee collision capsule component */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Collision", meta = (AllowPrivateAccess = "true"))
	UCapsuleComponent* MeleeCollisionComp;

public:
	/** Zombies AI behavior. */
	UPROPERTY(EditAnywhere, Category = "AI")
	UBehaviorTree* BehaviorTree;

	/** Called when the zombie senses a pawn within cone of vision. */
	UFUNCTION(BlueprintCallable, Category = "AI")
	void OnSeePlayer(APawn* InPawn);

	/** Called when zombie senses sounds made a pawn within hearing range. */
	UFUNCTION(BlueprintCallable, Category = "AI")
	void OnHearPlayer(APawn* InPawn, const FVector& Location, float Volume);

	/** Flag to see if zombie has sensed player. */
	UPROPERTY(BlueprintReadOnly, Category = "AI")
	bool bSensedPlayer;

	/** Called to perform melee attack. */
	UFUNCTION(BlueprintCallable, Category = "Pawn")
	void OnMelee();

	/** Called when player pawn is within melee attack range. */
	UFUNCTION()
	void OnMeleeCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	/** Damage applied on melee. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pawn")
	float MeleeDamage;

	/** Type of damage dealt on melee */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pawn")
	TSubclassOf<UDamageType> MeleeDamageType;

	/** Sound played when zombie is idle. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	USoundBase* IdleSound;

	/** Sound played when zombie has sensed pawn. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	USoundBase* SenseSound;
	
	/** Sound played when zombie is patrolling. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	USoundBase* PatrolSound;
};
