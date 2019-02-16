// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PZCharacterBase.h"
#include "PZZombie.generated.h"

class UBehaviorTree;

UCLASS()
class PROJECTZOMBIE_API APZZombie : public APZCharacterBase
{
	GENERATED_BODY()
	
public:
	APZZombie();

	UPROPERTY(EditAnywhere, Category = "AI")
	UBehaviorTree* BehaviorTree;

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
