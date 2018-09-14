// Fill out your copyright notice in the Description page of Project Settings.

#include "Boton.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/Material.h"


// Sets default values
ABoton::ABoton()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    bPressed = false;
}

// Called when the game starts or when spawned
void ABoton::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABoton::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    FVector PosicionActual = Boton->GetRelativeTransform().GetLocation();
    if (!bPressed && bPressing && PosicionActual.Z <= AlturaContacto) {
        Presionado();//bPressed = true;
        bPosicionPresionado = false;
        SendSignalPressed();
    }

}

void ABoton::SendSignalPressed() {
    UE_LOG(LogClass, Log, TEXT("Send Signal Pressed"));
    /*APanelBotones * Panel = Cast<APanelBotones>(GetOwner());
    if (Panel) {
        Panel->Press(TareaAsociada);
    }*/
}

void ABoton::SendSignalReleased() {
    /*UE_LOG(LogClass, Log, TEXT("Send Signal Released"));
    APanelBotones * Panel = Cast<APanelBotones>(GetOwner());
    if (Panel) {
        Panel->Release(TareaAsociada);
    }*/
}

void ABoton::Presionado() {
    bPressed = true;
    Boton->SetMaterial(0, MaterialPresionado);
}

void ABoton::NoPresionado() {
    bPressed = false;
    Boton->SetMaterial(0, MaterialNormal);
}
