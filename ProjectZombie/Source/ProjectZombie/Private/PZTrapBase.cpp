// Fill out your copyright notice in the Description page of Project Settings.

#include "PZTrapBase.h"
#include "Components/BoxComponent.h"

APZTrapBase::APZTrapBase()
{
	// Use a box as a simple collision representation
	CollisionComp = CreateDefaultSubobject<UBoxComponent>(TEXT("SphereComp"));
	CollisionComp->InitBoxExtent(FVector(30.0f, 30.0f, 30.0f));
	CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &APZTrapBase::OnOverlapBegin);

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetupAttachment(CollisionComp);
}

void APZTrapBase::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* otherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

}

