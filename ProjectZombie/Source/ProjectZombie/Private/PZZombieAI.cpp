// Fill out your copyright notice in the Description page of Project Settings.

#include "PZZombieAI.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Kismet/GameplayStatics.h"
#include "PZZombie.h"
#include "PZWaypoint.h"
#include "PZPhysicsActor.h"
#include "PZCharacter.h"

APZZombieAI::APZZombieAI()
{
	BehaviorComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorComp"));
	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComp"));

	WaypointKey = "PatrolPoint";
	PlayerKey = "Player";
	DistractionKey = "Distraction";
}

void APZZombieAI::Possess(APawn* InPawn)
{
	Super::Possess(InPawn);

	APZZombie* AIZombie = Cast<APZZombie>(InPawn);
	if (AIZombie)
	{
		if (AIZombie->BehaviorTree->BlackboardAsset)
		{
			BlackboardComp->InitializeBlackboard(*(AIZombie->BehaviorTree->BlackboardAsset));
			BehaviorComp->StartTree(*AIZombie->BehaviorTree);
		}
	}
}

void APZZombieAI::SetTargetPlayer(APawn* PawnTarget)
{
	if (BlackboardComp)
	{
		BlackboardComp->SetValueAsObject(PlayerKey, PawnTarget);
	}
}

void APZZombieAI::SetWaypoint(APZWaypoint* NewWaypoint)
{
	if (BlackboardComp)
	{
		BlackboardComp->SetValueAsObject(WaypointKey, NewWaypoint);
	}
}

void APZZombieAI::SetDistraction(APZPhysicsActor* NewActor)
{
	if (BlackboardComp)
	{
		BlackboardComp->SetValueAsObject(DistractionKey, NewActor);
	}
}

APZCharacter* APZZombieAI::GetTargetPlayer()
{
	return nullptr;
}

APZWaypoint* APZZombieAI::GetWaypoint()
{
	return nullptr;
}

APZPhysicsActor* APZZombieAI::GetDistraction()
{
	return nullptr;
}
