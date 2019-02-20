// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PZCharacterMovement.generated.h"

UCLASS()
class PROJECTZOMBIE_API UPZCharacterMovement : public UCharacterMovementComponent
{
	GENERATED_BODY()
	
public:
	UPZCharacterMovement();

	virtual float GetMaxSpeed() const override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Movement: Sprint", meta = (DisplayName = "Sprint Speed"))
	float SprintSpeed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character Movement: Sprint", meta = (DisplayName = "Sprint"))
	bool bIsSprinting;
};
