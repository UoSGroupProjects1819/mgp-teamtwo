// Fill out your copyright notice in the Description page of Project Settings.

#include "PZZombie.h"
#include "Perception/PawnSensingComponent.h"
#include "DrawDebugHelpers.h"
#include "PZZombieAI.h"

APZZombie::APZZombie(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComp"));
	PawnSensingComp->SetPeripheralVisionAngle(90.0f);

	AIControllerClass = APZZombieAI::StaticClass();
	MaxHealth = 50;
	MeleeRange = 200.0f;
}

void APZZombie::BeginPlay()
{
	Super::BeginPlay();

	if (PawnSensingComp)
	{
		PawnSensingComp->OnSeePawn.AddDynamic(this, &APZZombie::OnSeePlayer);
	}
}

void APZZombie::OnSeePlayer(APawn* Pawn)
{
	APZZombieAI* AIController = Cast<APZZombieAI>(GetController());
	if (AIController)
	{
		UE_LOG(LogTemp, Display, TEXT("I See You!"));
		AIController->OnSight(Pawn);
		float Dist = GetDistanceTo(Pawn);
		if (Dist == MeleeRange)
		{
			OnMelee();
		}
	}
}

void APZZombie::OnHearNoise(AActor* OtherActor, const FVector& Location, float Volume)
{
	APZZombieAI* AIController = Cast<APZZombieAI>(GetController());
	if (AIController)
	{
		APawn* Pawn = Cast<APawn>(OtherActor);
		if (Pawn != this)
		{
			UE_LOG(LogTemp, Display, TEXT("I Hear You!"));
			AIController->OnHear(OtherActor);
		}
	}
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
	DrawDebugLine(GetWorld(), StartTrace, EndTrace, FColor::Green, false, 1, 0, 1);
	GetWorld()->LineTraceSingleByChannel(Hit, StartTrace, EndTrace, ECC_GameTraceChannel2, TraceParams);
	return Hit;
}
