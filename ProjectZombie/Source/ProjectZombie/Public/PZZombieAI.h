// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "PZZombieAI.generated.h"

class UBehaviorTreeComponent;
class APZWaypoint;
class APZPhysicsActor;
class APZCharacter;

UCLASS()
class PROJECTZOMBIE_API APZZombieAI : public AAIController
{
	GENERATED_BODY()
	
public:
	APZZombieAI();

public:
	virtual void Possess(APawn* InPawn) override;

	UFUNCTION()
	virtual void SetTargetPlayer(APawn* PawnTarget);

	UFUNCTION()
	virtual void SetWaypoint(APZWaypoint* NewWaypoint);

	UFUNCTION()
	virtual void SetDistraction(APZPhysicsActor* NewActor);

	UFUNCTION()
	APZCharacter* GetTargetPlayer();

	UFUNCTION()
	APZWaypoint* GetWaypoint();

	UFUNCTION()
	APZPhysicsActor* GetDistraction();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FName PlayerKey;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI")
	FName WaypointKey;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI")
	FName DistractionKey;

private:
	UPROPERTY(Transient)
	UBehaviorTreeComponent* BehaviorComp;
	UPROPERTY(Transient)
	UBlackboardComponent* BlackboardComp;

public:
	FORCEINLINE UBehaviorTreeComponent* GetBehaviorComp() const { return BehaviorComp; }
	FORCEINLINE UBlackboardComponent* GetBlackboardComp() const { return BlackboardComp; }
};
