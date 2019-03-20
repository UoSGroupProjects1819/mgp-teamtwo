// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PZCharacterBase.generated.h"

class USoundBase;

UCLASS()
class PROJECTZOMBIE_API APZCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	APZCharacterBase(const FObjectInitializer& ObjectInitializer);

	virtual void BeginPlay() override;

	/** Apply damage to this pawn */
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	/** Called when we run out of health */
	UFUNCTION(BlueprintCallable, Category = "Pawn")
	virtual bool Die(FDamageEvent const& DamageEvent, AController* KIller, AActor* DamageCauser);

	/** Simulate pawn death */
	UFUNCTION(BlueprintCallable, Category = "Pawn")
	virtual void PlayDeath();

	/** Simulate pawn ragdoll */
	UFUNCTION(BlueprintCallable, Category = "Pawn")
	virtual void PlayRagdoll();

	/** Play sound on death */
	UFUNCTION(BlueprintCallable, Category = "Pawn")
	virtual void PlayDeathSound();

	/** Get pawn health */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Pawn")
	int32 GetHealth() const;

	/** Get pawn max health */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Pawn")
	int32 GetMaxHealth() const;

	/** Returns true if the pawn is dead */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Pawn")
	bool IsDead() const;

protected:
	/** Sound player on death */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Pawn")
	USoundBase* DeathSound;

	/** Current health of the pawn */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pawn")
	int32 Health;

	/** Max health of the pawn */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pawn")
	int32 MaxHealth;

	/** True if pawn is dead */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Pawn")
	bool bIsDead;
};
