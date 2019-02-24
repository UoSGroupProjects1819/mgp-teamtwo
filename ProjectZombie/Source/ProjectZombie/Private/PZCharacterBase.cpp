// Fill out your copyright notice in the Description page of Project Settings.

#include "PZCharacterBase.h"

APZCharacterBase::APZCharacterBase(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	Health = 0;
	MaxHealth = 0;
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
			Die(DamageEvent, EventInstigator, DamageCauser);
		}
		else
		{
			ApplyDamageMomentum(Damage, DamageEvent, EventInstigator ? EventInstigator->GetPawn() : nullptr, DamageCauser);
		}
	}

	return float(ResultDamage);
}

bool APZCharacterBase::Die(FDamageEvent const& DamageEvent, AController* KIller, AActor* DamageCauser)
{
	Health = FMath::Min<int32>(0.0f, Health);

	PlayDeath();
	return true;
}

void APZCharacterBase::PlayDeath()
{
	SetLifeSpan(0.15f);
	PlayRagdoll();
}

void APZCharacterBase::PlayRagdoll()
{

}

