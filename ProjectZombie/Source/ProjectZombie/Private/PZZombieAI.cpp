// Fill out your copyright notice in the Description page of Project Settings.

#include "PZZombieAI.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "PZZombie.h"

APZZombieAI::APZZombieAI()
{
	BehaviorComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorComp"));
	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComp"));
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

void APZZombieAI::OnSight(APawn* InPawn)
{
	if (BlackboardComp)
	{
		BlackboardComp->SetValueAsObject(BlackboardKey, InPawn);
	}
}
