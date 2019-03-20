// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTaskPatrol.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "PZZombieAI.h"
#include "PZWaypoint.h"

EBTNodeResult::Type UBTTaskPatrol::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	APZZombieAI* AIController = Cast<APZZombieAI>(OwnerComp.GetAIOwner());
	if (AIController)
	{
		UBlackboardComponent* BlackboardComp = AIController->GetBlackboardComp();
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}
