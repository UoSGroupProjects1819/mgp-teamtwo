// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PZPhysicsActor.generated.h"

class UAIPerceptionStimuliSourceComponent;
class UAISense;

UCLASS()
class PROJECTZOMBIE_API APZPhysicsActor : public AActor
{
	GENERATED_BODY()
	
public:
	/** Default constructor. */
	APZPhysicsActor();

private:
	/** Physics actor mesh component. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* MeshComp;

	/** AI perception stimuli source component. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI", meta = (AllowPrivateAccess = "true"))
	UAIPerceptionStimuliSourceComponent* PerceptionStimuliSourceComp;

public:
	UFUNCTION()
	virtual void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};
