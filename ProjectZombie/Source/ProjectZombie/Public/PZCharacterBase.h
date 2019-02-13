// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PZCharacterBase.generated.h"

UCLASS()
class PROJECTZOMBIE_API APZCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	APZCharacterBase();

	virtual void BeginPlay() override;

	/** Apply damage to this pawn */
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

protected:
	/** Current health of the pawn */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pawn")
	int32 Health;

	/** Max health of the pawn */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pawn")
	int32 MaxHealth;
};
