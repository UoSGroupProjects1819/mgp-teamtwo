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

public:
	virtual void Possess(APawn* InPawn) override;
	
	UFUNCTION(BlueprintCallable, Category = "AI")
	virtual void OnSight(APawn* InPawn);

	UFUNCTION(BlueprintCallable, Category = "AI")
	virtual void OnHear(AActor* OtherActor);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI")
	FName PlayerKey = "PlayerTarget";

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI")
	FName WaypointKey = "Waypoint";

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI")
	FName SoundKey = "SoundTarget";

	UPROPERTY(Transient)
	TArray<AActor*> AIWaypoints;

	inline TArray<AActor*> GetWaypoints() const 
	{
		return AIWaypoints;
	}

private:
	UPROPERTY(Transient)
	UBehaviorTreeComponent* BehaviorComp;
	UPROPERTY(Transient)
	UBlackboardComponent* BlackboardComp;

public:
	FORCEINLINE UBehaviorTreeComponent* GetBehaviorComp() const { return BehaviorComp; }
	FORCEINLINE UBlackboardComponent* GetBlackboardComp() const { return BlackboardComp; }
};
