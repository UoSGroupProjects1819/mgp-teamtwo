// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PZPhysicsObject.generated.h"

class USphereComponent;

UCLASS()
class PROJECTZOMBIE_API APZPhysicsObject : public AActor
{
	GENERATED_BODY()
	
public:	
	APZPhysicsObject();

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh", meta=(AllowPrivateAccess="true"))
	UStaticMeshComponent* MeshComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh", meta=(AllowPrivateAccess="true"))
	USphereComponent* SphereCollisionComp;

public:

};
