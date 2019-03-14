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

	///** AI perception component */
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI", meta = (AllowPrivateAccess = "true"))
	//UAIPerceptionComponent* AIPerceptionComp;

public:
	UPROPERTY(EditAnywhere, Category = "AI")
	UBehaviorTree* BehaviorTree;

	UFUNCTION(BlueprintCallable, Category = "AI")
	void OnSeePlayer(APawn* InPawn);

	UFUNCTION(BlueprintCallable, Category = "AI")
	void OnHearNoise(APawn* InPawn, const FVector& Location, float Volume);

	UFUNCTION(BlueprintCallable, Category = "Pawn")
	void OnMelee();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pawn")
	float MeleeDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pawn")
	float MeleeRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pawn")
	TSubclassOf<UDamageType> MeleeDamageType;

protected:
	FHitResult MeleeTrace(const FVector& StartTrace, const FVector& EndTrace) const;
};
