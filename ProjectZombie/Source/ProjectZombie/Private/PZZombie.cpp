// Fill out your copyright notice in the Description page of Project Settings.

#include "PZZombie.h"
#include "Perception/PawnSensingComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Components/CapsuleComponent.h"
#include "DrawDebugHelpers.h"
#include "PZZombieAI.h"
#include "PZCharacter.h"

APZZombie::APZZombie(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComp"));
	PawnSensingComp->SetPeripheralVisionAngle(60.0f);
	PawnSensingComp->SightRadius = 2000.0f;
	PawnSensingComp->HearingThreshold = 600.0f;
	PawnSensingComp->LOSHearingThreshold = 1200.0f;

	MeleeCollisionComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("MeleeCollision"));
	MeleeCollisionComp->SetupAttachment(GetCapsuleComponent());

	//AIPerceptionComp = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("PerceptionComp"));

	AIControllerClass = APZZombieAI::StaticClass();
	//MaxHealth = 50;
	MeleeRange = 150.0f;
	MeleeDamage = 100.0f;
	bCanHear = false;
}

void APZZombie::BeginPlay()
{
	Super::BeginPlay();

	if (PawnSensingComp)
	{
		PawnSensingComp->OnSeePawn.AddDynamic(this, &APZZombie::OnSeePlayer);
		PawnSensingComp->OnHearNoise.AddDynamic(this, &APZZombie::OnHearPlayer);
	}
}

void APZZombie::OnSeePlayer(APawn* InPawn)
{
	APZZombieAI* AIController = Cast<APZZombieAI>(GetController());
	if (AIController)
	{
		UE_LOG(LogTemp, Display, TEXT("I See You!"));
		AIController->OnSight(InPawn);
	}
}

void APZZombie::OnHearPlayer(APawn* InPawn, const FVector& Location, float Volume)
{
	APZZombieAI* AIController = Cast<APZZombieAI>(GetController());
	if (AIController && InPawn != this)
	{
		UE_LOG(LogTemp, Display, TEXT("I Hear You!"));
		AIController->OnHear(InPawn);
		bCanHear = true;
	}
}

void APZZombie::OnMelee()
{
	APZZombieAI* AIController = Cast<APZZombieAI>(GetController());
	if (AIController)
	{
		FVector MeleeDir = FVector::ZeroVector;
		FVector StartTrace = FVector::ZeroVector;

		FRotator MeleeRot = FRotator::ZeroRotator;
		AIController->GetPlayerViewPoint(StartTrace, MeleeRot);
		MeleeDir = MeleeRot.Vector();

		StartTrace = StartTrace + MeleeDir * ((GetActorLocation() - StartTrace) | MeleeDir);

		const FVector EndTrace = StartTrace + MeleeDir * MeleeRange;
		const FHitResult Impact = MeleeTrace(StartTrace, EndTrace);

		AActor* DamagedActor = Impact.GetActor();

		if (DamagedActor != nullptr && DamagedActor != this)
		{
			FDamageEvent MeleeDamageEvent(MeleeDamageType);
			DamagedActor->TakeDamage(MeleeDamage, MeleeDamageEvent, GetController(), this);
		}
	}
}

void APZZombie::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor != nullptr)
	{
		APZCharacter* Char = Cast<APZCharacter>(OtherActor);
		if (Char)
		{
			FDamageEvent MeleeDamageEvent(MeleeDamageType);
			Char->TakeDamage(MeleeDamage, MeleeDamageEvent, GetController(), this);
		}
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
