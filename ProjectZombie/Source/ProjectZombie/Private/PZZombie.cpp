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
	PawnSensingComp->SightRadius = 1000.0f;
	PawnSensingComp->HearingThreshold = 300.0f;
	PawnSensingComp->LOSHearingThreshold = 600.0f;

	MeleeCollisionComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("MeleeCollision"));
	MeleeCollisionComp->SetupAttachment(GetCapsuleComponent());
	MeleeCollisionComp->SetRelativeLocation(FVector(45.0f, 0.0f, 25.0f));
	MeleeCollisionComp->SetCapsuleHalfHeight(60.0f);
	MeleeCollisionComp->SetCapsuleRadius(35.0f);

	AIControllerClass = APZZombieAI::StaticClass();
	MaxHealth = 50;
	MeleeDamage = 100.0f;
}

void APZZombie::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void APZZombie::BeginPlay()
{
	Super::BeginPlay();

	if (PawnSensingComp)
	{
		PawnSensingComp->OnSeePawn.AddDynamic(this, &APZZombie::OnSeePlayer);
		PawnSensingComp->OnHearNoise.AddDynamic(this, &APZZombie::OnHearPlayer);
	}

	if (MeleeCollisionComp)
	{
		MeleeCollisionComp->OnComponentBeginOverlap.AddDynamic(this, &APZZombie::OnMeleeCollisionBeginOverlap);
	}
}

void APZZombie::OnSeePlayer(APawn* InPawn)
{
	bSensedPlayer = true;
	LastSeenTime = GetWorld()->GetTimeSeconds();

	APZZombieAI* AIController = Cast<APZZombieAI>(GetController());
	if (AIController)
	{
		UE_LOG(LogTemp, Display, TEXT("Sensed Pawn: %s"), *GetNameSafe(InPawn));
		AIController->SetTargetPlayer(InPawn);
	}
}

void APZZombie::OnHearPlayer(APawn* InPawn, const FVector& Location, float Volume)
{
	bSensedPlayer = true;
	LastHeardTime = GetWorld()->GetTimeSeconds();

	APZZombieAI* AIController = Cast<APZZombieAI>(GetController());
	if (AIController && InPawn != this)
	{
		UE_LOG(LogTemp, Display, TEXT("Sensed Pawn: %s"), *GetNameSafe(InPawn));
		AIController->SetTargetPlayer(InPawn);
	}
}

void APZZombie::OnMelee()
{

}

void APZZombie::OnMeleeCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

}
