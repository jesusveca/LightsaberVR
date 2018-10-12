// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "LightsaberVRGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class LIGHTSABERVR_API ALightsaberVRGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
            
    ALightsaberVRGameModeBase();

    ALightsaberVRGameModeBase(const FObjectInitializer & ObjectInitializer);
	
	
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "LightsaberVR")
    void PerderJuego();
    void PerderJuego_Implementation();

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "LightsaberVR")
    void GanarJuego();
    void GanarJuego_Implementation();
	
};
