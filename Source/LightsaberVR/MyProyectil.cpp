// Fill out your copyright notice in the Description page of Project Settings.

#include "MyProyectil.h"

// Sets default values
AMyProyectil::AMyProyectil()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
    Velocidad = 1000.0f;
    Poder = 30.0f;
    bLanzado = false;
}

// Called when the game starts or when spawned
void AMyProyectil::BeginPlay()
{
    Super::BeginPlay();
}

// Called every frame
void AMyProyectil::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    if (bLanzado)
    {
        SetActorLocation(GetActorLocation() + GetActorForwardVector() * Velocidad * DeltaTime);
    }
}

void AMyProyectil::Lanzar()
{
    if (GEngine) //no hacer esta verificaci�n provocaba error al iniciar el editor
        GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT("lanzando"));

        bLanzado=true;
}
