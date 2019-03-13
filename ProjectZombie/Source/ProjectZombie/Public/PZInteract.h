// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PZInteract.generated.h"

UINTERFACE(MinimalAPI)
class UPZInteract : public UInterface
{
	GENERATED_BODY()
};

class PROJECTZOMBIE_API IPZInteract
{
	GENERATED_BODY()

public:
	virtual void OnBeginInteract() = 0;
	virtual void OnEndInteract() = 0;
	virtual void OnInteract(APawn* InPawn) = 0;
};
