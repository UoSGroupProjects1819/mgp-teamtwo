// Fill out your copyright notice in the Description page of Project Settings.

#include "PZCharacterMovement.h"

UPZCharacterMovement::UPZCharacterMovement()
{
	SprintSpeed = 1200.0f;
	NavAgentProps.bCanCrouch = true;
}

float UPZCharacterMovement::GetMaxSpeed() const
{
	return bIsSprinting ? SprintSpeed : Super::GetMaxSpeed();
}
