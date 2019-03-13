// Fill out your copyright notice in the Description page of Project Settings.

#include "PZPhysicsActor.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Perception/AISense_Hearing.h"

APZPhysicsActor::APZPhysicsActor()
{
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetupAttachment(RootComponent);
	MeshComp->SetSimulatePhysics(true);
	MeshComp->SetNotifyRigidBodyCollision(true);
	MeshComp->GetBodyInstance()->bUseCCD = true;
	MeshComp->OnComponentHit.AddDynamic(this, &APZPhysicsActor::OnHit);

	PerceptionStimuliSourceComp = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(TEXT("NoiseComp"));
}

void APZPhysicsActor::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	float Magnitude = NormalImpulse.Size();
	float ActorMass = MeshComp->GetMass() * 100.0f;
	float NoiseVolume = MeshComp->GetMass() / 100.0f;
	if (Magnitude > ActorMass && Hit.bBlockingHit)
	{
		UAISense_Hearing::ReportNoiseEvent(GetWorld(), Hit.Location, NoiseVolume, this, 500.0f, FName(TEXT("Noise")));
		UE_LOG(LogTemp, Display, TEXT("Nosie"))
	}
}

