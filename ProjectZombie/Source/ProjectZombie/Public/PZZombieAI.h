// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "PZZombieAI.generated.h"

class UBehaviorTreeComponent;

UCLASS()
class PROJECTZOMBIE_API APZZombieAI : public AAIController
{
	GENERATED_BODY()
	
public:
	APZZombieAI();

	virtual void Possess(APawn* InPawn) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI")
	FName LocationKey;

	UPROPERTY(Transient)
	TArray<AActor*> AITargetPoints;

private:
	UPROPERTY(Transient)
	UBehaviorTreeComponent* BehaviorComp;
	UPROPERTY(Transient)
	UBlackboardComponent* BlackboardComp;

public:
	FORCEINLINE UBehaviorTreeComponent* GetBehaviorComp() const { return BehaviorComp; }
	FORCEINLINE UBlackboardComponent* GetBlackboardComp() const { return BlackboardComp; }
};
