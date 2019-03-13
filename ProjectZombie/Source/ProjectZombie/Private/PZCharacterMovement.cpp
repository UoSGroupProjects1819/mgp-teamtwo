// Fill out your copyright notice in the Description page of Project Settings.

#include "PZCharacterMovement.h"

UPZCharacterMovement::UPZCharacterMovement()
{
	MaxWalkSpeed = 440.0f;
	MaxWalkSpeedCrouched = 220.0f;
	SprintSpeed = 880.0f;
	NavAgentProps.bCanCrouch = true;
}

float UPZCharacterMovement::GetMaxSpeed() const
{
	if (bIsSprinting && !IsCrouching())
	{
		return SprintSpeed;
	}

	return Super::GetMaxSpeed();
}
