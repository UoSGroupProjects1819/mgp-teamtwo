// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PZCharacterBase.h"
#include "PZZombie.generated.h"

class UBehaviorTree;
class UPawnSensingComponent;

UCLASS()
class PROJECTZOMBIE_API APZZombie : public APZCharacterBase
{
	GENERATED_BODY()
	
public:
	APZZombie(const FObjectInitializer& ObjectInitializer);

	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI", meta = (AllowPrivateAccess = "true"))
	UPawnSensingComponent* PawnSensingComp;

public:
	UPROPERTY(EditAnywhere, Category = "AI")
	UBehaviorTree* BehaviorTree;

	UFUNCTION(BlueprintCallable, Category = "AI")
	void OnSeePlayer(APawn* Pawn);

	UFUNCTION(BlueprintCallable, Category = "AI")
	void OnHearNoise(APawn* OtherActor, const FVector& Location, float Volume);

	UFUNCTION(BlueprintCallable, Category = "Pawn")
	void OnMelee();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pawn")
	float MeleeDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pawn")
	float MeleeRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pawn")
	TSubclassOf<UDamageType> MeleeDamageType;

private:
	FHitResult MeleeTrace(const FVector& StartTrace, const FVector& EndTrace) const;
};
