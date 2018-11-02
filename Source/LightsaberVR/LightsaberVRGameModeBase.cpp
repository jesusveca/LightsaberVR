// Fill out your copyright notice in the Description page of Project Settings.

#include "LightsaberVRGameModeBase.h"
#include "Public/UObject/ConstructorHelpers.h"
#include "LightsaberMultiPlayerController.h"

ALightsaberVRGameModeBase::ALightsaberVRGameModeBase() {
    PrimaryActorTick.bCanEverTick = true;

    static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("BlueprintGeneratedClass'/Game/LightsaberVR/Blueprints/Pawns/VRPawnBP.VRPawnBP_C'"));
    if (PlayerPawnBPClass.Succeeded()) {
        Pawn1 = PlayerPawnBPClass.Class;
    }
    static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass2(TEXT("BlueprintGeneratedClass'/Game/LightsaberVR/Blueprints/Pawns/MasterPawnBP.MasterPawnBP_C'"));
    if (PlayerPawnBPClass2.Succeeded()) {
        Pawn2 = PlayerPawnBPClass2.Class;
    }

    PlayerControllerClass = ALightsaberMultiPlayerController::StaticClass();
}

ALightsaberVRGameModeBase::ALightsaberVRGameModeBase(const FObjectInitializer & ObjectInitializer) {
    PrimaryActorTick.bCanEverTick = true;

    static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("BlueprintGeneratedClass'/Game/LightsaberVR/Blueprints/Pawns/VRPawnBP.VRPawnBP_C'"));
    if (PlayerPawnBPClass.Succeeded()) {
        Pawn1 = PlayerPawnBPClass.Class;
    }
    static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass2(TEXT("BlueprintGeneratedClass'/Game/LightsaberVR/Blueprints/Pawns/MasterPawnBP.MasterPawnBP_C'"));
    if (PlayerPawnBPClass2.Succeeded()) {
        Pawn2 = PlayerPawnBPClass2.Class;
    }

    PlayerControllerClass = ALightsaberMultiPlayerController::StaticClass();
}

void ALightsaberVRGameModeBase::PerderJuego_Implementation() {
}

void ALightsaberVRGameModeBase::GanarJuego_Implementation() {
}

UClass* ALightsaberVRGameModeBase::GetDefaultPawnClassForController(AController* InController)
{
	/* Override Functionality to get Pawn from PlayerController */
	ALightsaberMultiPlayerController * MyController = Cast<ALightsaberMultiPlayerController>(InController);
	if (MyController)
	{
        return MyController->GetPlayerPawnClass();
	}
 
	/* If we don't get the right Controller, use the Default Pawn */
	return DefaultPawnClass;
}


