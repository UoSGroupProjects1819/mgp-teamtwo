// Fill out your copyright notice in the Description page of Project Settings.

#include "PZCharacterBase.h"
#include "Kismet/GameplayStatics.h"
#include "Components/CapsuleComponent.h"

APZCharacterBase::APZCharacterBase(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	Health = 0;
	MaxHealth = 0;
	bIsDead = false;
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
		UE_LOG(LogTemp, Display, TEXT("%s::TakeDamage() %d Class:%s Causer:%s"), *GetName(), int32(Damage), *GetNameSafe(DamageEvent.DamageTypeClass), *GetNameSafe(DamageCauser));
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
	if (IsPendingKill() || GetWorld()->GetAuthGameMode() == nullptr)
	{
		return false;
	}

	Health = FMath::Min<int32>(0.0f, Health);
	PlayDeath();

	return true;
}

void APZCharacterBase::PlayDeath()
{
	if (bIsDead)
	{
		return;
	}

	TearOff();
	DetachFromControllerPendingDestroy();
	bIsDead = true;

	PlayDeathSound();
	PlayRagdoll();
}

void APZCharacterBase::PlayRagdoll()
{
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECR_Ignore);
	SetActorEnableCollision(true);
}

void APZCharacterBase::PlayDeathSound()
{
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), DeathSound, GetActorLocation());
}

int32 APZCharacterBase::GetHealth() const
{
	return Health;
}

int32 APZCharacterBase::GetMaxHealth() const
{
	return MaxHealth;
}

bool APZCharacterBase::IsDead() const
{
	return bIsDead;
}

