// Fill out your copyright notice in the Description page of Project Settings.

#include "PZWeaponBase.h"
#include "PZCharacter.h"

#define COLLISION_WEAPON ECC_EngineTraceChannel1

APZWeaponBase::APZWeaponBase()
{
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh1P"));
	Mesh->SetupAttachment(GetRootComponent());
	Mesh->SetOnlyOwnerSee(true);
	Mesh->bCastDynamicShadow = false;
	Mesh->CastShadow = false;
	Mesh->bSelfShadowOnly = true;
	Mesh->MeshComponentUpdateFlag = EMeshComponentUpdateFlag::OnlyTickPoseWhenRendered;

	PrimaryActorTick.bCanEverTick = true;
}

void APZWeaponBase::StartFire()
{

}

void APZWeaponBase::StopFire()
{

}

void APZWeaponBase::StartAltFire()
{

}

void APZWeaponBase::StopAltFire()
{

}

void APZWeaponBase::AttachToOwner()
{

}

void APZWeaponBase::DetachFromOwner()
{

}

void APZWeaponBase::GivenTo(APZCharacter* NewOwner)
{
	Instigator = NewOwner;
	SetOwner(NewOwner);
	PZOwner = NewOwner;
}

void APZWeaponBase::Removed()
{
	Instigator = nullptr;
	SetOwner(nullptr);
	PZOwner = nullptr;
}

FHitResult APZWeaponBase::WeaponTrace(const FVector& StartTrace, const FVector& EndTrace) const
{
	FCollisionQueryParams TraceParams(SCENE_QUERY_STAT(WeaponTrace), true, Instigator);
	TraceParams.bTraceAsyncScene = true;
	TraceParams.bReturnPhysicalMaterial = true;

	FHitResult Hit(ForceInit);
	GetWorld()->LineTraceSingleByChannel(Hit, StartTrace, EndTrace, COLLISION_WEAPON, TraceParams);
	return Hit;
}

