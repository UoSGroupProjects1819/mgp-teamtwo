// Fill out your copyright notice in the Description page of Project Settings.

#include "PZZombie.h"
#include "PZZombieAI.h"

APZZombie::APZZombie()
{
	AIControllerClass = APZZombieAI::StaticClass();
}

void APZZombie::OnMelee()
{
	FVector MeleeLoc = GetControlRotation().Vector();
	FRotator MeleeRot = GetControlRotation();
	const FVector MeleeDir = MeleeRot.Vector();

	FVector StartTrace = FVector::ZeroVector;
	StartTrace = StartTrace + MeleeDir * ((GetActorLocation() - StartTrace) | MeleeDir);

	const FVector EndTrace = StartTrace + MeleeDir * MeleeRange;
	const FHitResult Impact = MeleeTrace(StartTrace, EndTrace);

	AActor* DamagedActor = Impact.GetActor();
	if (DamagedActor != nullptr && DamagedActor != this)
	{
		FDamageEvent MeleeDamageEvent(MeleeDamageType);
		DamagedActor->TakeDamage(MeleeDamage, MeleeDamageEvent, Controller, this);
	}
}

FHitResult APZZombie::MeleeTrace(const FVector& StartTrace, const FVector& EndTrace) const
{
	FCollisionQueryParams TraceParams(SCENE_QUERY_STAT(MeleeTrace), true, Instigator);
	TraceParams.bTraceAsyncScene = true;

	FHitResult Hit(ForceInit);
	GetWorld()->LineTraceSingleByChannel(Hit, StartTrace, EndTrace, ECC_GameTraceChannel1, TraceParams);
	return Hit;
}
