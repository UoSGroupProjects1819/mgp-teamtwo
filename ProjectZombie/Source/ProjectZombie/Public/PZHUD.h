// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "PZHUD.generated.h"

UCLASS()
class PROJECTZOMBIE_API APZHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	APZHUD();

	virtual void DrawHUD() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UI)
	UTexture2D* CrosshairTex;
};
