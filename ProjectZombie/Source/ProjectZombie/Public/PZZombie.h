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

	virtual void BeginPlay() override;

private:
	/** AI sensing component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI", meta = (AllowPrivateAccess = "true"))
	UPawnSensingComponent* PawnSensingComp;

	/** Melee collision capsule component */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Collision", meta = (AllowPrivateAccess = "true"))
	UCapsuleComponent* MeleeCollisionComp;

	///** AI perception component */
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI", meta = (AllowPrivateAccess = "true"))
	//UAIPerceptionComponent* AIPerceptionComp;

public:
	UPROPERTY(EditAnywhere, Category = "AI")
	UBehaviorTree* BehaviorTree;

	UFUNCTION(BlueprintCallable, Category = "AI")
	void OnSeePlayer(APawn* InPawn);

	UFUNCTION(BlueprintCallable, Category = "AI")
	void OnHearPlayer(APawn* InPawn, const FVector& Location, float Volume);

	UFUNCTION(BlueprintCallable, Category = "Pawn")
	void OnMelee();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	USoundBase* IdleSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	USoundBase* SeenSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	USoundBase* HuntingSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	USoundBase* PatrolSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pawn")
	float MeleeDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pawn")
	float MeleeRange;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Pawn")
	bool bCanHear;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pawn")
	TSubclassOf<UDamageType> MeleeDamageType;

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
	FHitResult MeleeTrace(const FVector& StartTrace, const FVector& EndTrace) const;
};
