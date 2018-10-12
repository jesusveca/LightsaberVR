// Fill out your copyright notice in the Description page of Project Settings.

#include "LightsaberVRGameModeBase.h"
#include "Public/UObject/ConstructorHelpers.h"

ALightsaberVRGameModeBase::ALightsaberVRGameModeBase() {
    PrimaryActorTick.bCanEverTick = true;

}

ALightsaberVRGameModeBase::ALightsaberVRGameModeBase(const FObjectInitializer & ObjectInitializer) {
    PrimaryActorTick.bCanEverTick = true;

}

void ALightsaberVRGameModeBase::PerderJuego_Implementation() {
}

void ALightsaberVRGameModeBase::GanarJuego_Implementation() {
}



