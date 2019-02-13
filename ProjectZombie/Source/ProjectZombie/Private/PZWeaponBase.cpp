// Fill out your copyright notice in the Description page of Project Settings.

#include "PZWeaponBase.h"

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

