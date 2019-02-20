// Fill out your copyright notice in the Description page of Project Settings.

#include "PZWeaponBase.h"
#include "DrawDebugHelpers.h"
#include "PZCharacter.h"

#define COLLISION_WEAPON ECC_GameTraceChannel1

APZWeaponBase::APZWeaponBase()
{
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh1P"));
	Mesh->SetupAttachment(GetRootComponent());
	Mesh->SetOnlyOwnerSee(true);
	Mesh->bSelfShadowOnly = true;
	Mesh->MeshComponentUpdateFlag = EMeshComponentUpdateFlag::OnlyTickPoseWhenRendered;

	bOnlyRelevantToOwner = true;
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
	if (PZOwner)
	{
		Mesh->AttachToComponent(PZOwner->GetFirstPersonMesh(), FAttachmentTransformRules::KeepRelativeTransform, HandsAttachSocket);
	}
}

void APZWeaponBase::DetachFromOwner()
{
	if (PZOwner)
	{

	}
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
	DrawDebugLine(GetWorld(), StartTrace, EndTrace, FColor::Red, false, 1, 0, 1);
	GetWorld()->LineTraceSingleByChannel(Hit, StartTrace, EndTrace, COLLISION_WEAPON, TraceParams);
	return Hit;
}

