// Fill out your copyright notice in the Description page of Project Settings.

#include "PZCharacterBase.h"

APZCharacterBase::APZCharacterBase()
{
	PrimaryActorTick.bCanEverTick = true;
}

void APZCharacterBase::BeginPlay()
{
	Super::BeginPlay();

	if (Health == 0)
	{
		Health = MaxHealth;
	}
}

float APZCharacterBase::TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	int32 ResultDamage = FMath::TruncToInt(Damage);
	if (ResultDamage > 0)
	{
		Health -= ResultDamage;
		if (Health <= 0)
		{
			// TODO: Die
		}
		else
		{
			ApplyDamageMomentum(Damage, DamageEvent, EventInstigator ? EventInstigator->GetPawn() : nullptr, DamageCauser);
		}
	}

	return float(ResultDamage);
}

