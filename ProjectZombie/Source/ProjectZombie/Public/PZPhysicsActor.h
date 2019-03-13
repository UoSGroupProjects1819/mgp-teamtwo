// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PZInteract.h"
#include "GameFramework/Actor.h"
#include "PZPhysicsActor.generated.h"

class UAIPerceptionStimuliSourceComponent;
class UAISense;

UCLASS()
class PROJECTZOMBIE_API APZPhysicsActor : public AActor, public IPZInteract
{
	GENERATED_BODY()
	
public:
	/** Default constructor. */
	APZPhysicsActor();

	// IPZInteract Interface 
	virtual void OnBeginInteract() override;
	virtual void OnEndInteract() override;
	virtual void OnInteract(APawn* InPawn) override;

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
