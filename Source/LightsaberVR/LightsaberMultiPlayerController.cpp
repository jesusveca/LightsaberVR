// Fill out your copyright notice in the Description page of Project Settings.

#include "LightsaberMultiPlayerController.h"
#include "UnrealNetwork.h"
#include "Public/UObject/ConstructorHelpers.h"
#include "Engine/World.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/GameModeBase.h"

ALightsaberMultiPlayerController::ALightsaberMultiPlayerController(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	/* Initialize The Values */
    static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("BlueprintGeneratedClass'/Game/LightsaberVR/Blueprints/Pawns/VRPawnBP.VRPawnBP_C'"));
    if (PlayerPawnBPClass.Succeeded()) {
        PawnToUseA = PlayerPawnBPClass.Class;
    }
    static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass2(TEXT("BlueprintGeneratedClass'/Game/LightsaberVR/Blueprints/Pawns/MasterPawnBP.MasterPawnBP_C'"));
    if (PlayerPawnBPClass2.Succeeded()) {
        PawnToUseB = PlayerPawnBPClass2.Class;
    }

    static ConstructorHelpers::FClassFinder<UUserWidget> HUDWidgetClass(TEXT("WidgetBlueprintGeneratedClass'/Game/LightsaberVR/UMG/menu.menu_C'"));
    //deberia buscar una grafica
    if (HUDWidgetClass.Succeeded()) {
        TypeHUDWidget = HUDWidgetClass.Class;
    }
 
	/* Make sure the PawnClass is Replicated */
	bReplicates = true;
}
 
void ALightsaberMultiPlayerController::BeginPlay() {
	Super::BeginPlay();
 
	DeterminePawnClass();
    if (Role != ENetRole::ROLE_Authority) {
        bShowMouseCursor = true;
        FInputModeGameAndUI Mode = FInputModeGameAndUI();

        Mode.SetHideCursorDuringCapture(false);
        if (TypeHUDWidget) {
            UUserWidget * HUD = CreateWidget<UUserWidget>(GetWorld(), TypeHUDWidget);//le doy el mundo sobre el que se instancia, y lo que instanciare
            if (HUD) {
                HUD->SetOwningPlayer(this);
                HUD->AddToViewport(1);
                Mode.SetWidgetToFocus(HUD->TakeWidget());
                HUD->SetUserFocus(this);
            }
        }
        //que cree y luego lo agregue
        SetInputMode(Mode);
        bEnableMouseOverEvents = true;
        bEnableClickEvents = true;
    }
}
 
// Pawn Class
void ALightsaberMultiPlayerController::DeterminePawnClass_Implementation() {
	if (Role < ROLE_Authority) {//somos clientes
        ServerSetPawn(PawnToUseB);
	}
    else {
        ServerSetPawn(PawnToUseA);
    }
}
 
bool ALightsaberMultiPlayerController::ServerSetPawn_Validate(TSubclassOf<APawn> InPawnClass) {
	return true;
}
 
void ALightsaberMultiPlayerController::ServerSetPawn_Implementation(TSubclassOf<APawn> InPawnClass) {
	MyPawnClass = InPawnClass;
 
	/* Just in case we didn't get the PawnClass on the Server in time... */
	GetWorld()->GetAuthGameMode()->RestartPlayer(this);
}
 
// Replication
void ALightsaberMultiPlayerController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const {
	DOREPLIFETIME(ALightsaberMultiPlayerController, MyPawnClass);
}





