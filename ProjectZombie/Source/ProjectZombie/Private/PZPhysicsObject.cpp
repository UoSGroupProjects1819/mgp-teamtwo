// Fill out your copyright notice in the Description page of Project Settings.

#include "PZPhysicsObject.h"
#include "Components/SphereComponent.h"

APZPhysicsObject::APZPhysicsObject()
{
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetupAttachment(RootComponent);
	MeshComp->SetSimulatePhysics(true);
	MeshComp->GetBodyInstance()->bUseCCD = true;
}

