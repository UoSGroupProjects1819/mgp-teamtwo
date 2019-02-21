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
		APZWaypoint* CurrentWaypoint = Cast<APZWaypoint>(BlackboardComp->GetValueAsObject("Waypoint"));

		TArray<AActor*> Waypoints = AIController->GetWaypoints();
		int32 RandomIndex;
		APZWaypoint* NextWaypoint = nullptr;
		do
		{
			RandomIndex = FMath::RandRange(0, Waypoints.Num() -1);
			NextWaypoint = Cast<APZWaypoint>(Waypoints[RandomIndex]);

		} while (CurrentWaypoint == NextWaypoint);

		BlackboardComp->SetValueAsObject("Waypoint", NextWaypoint);
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}
