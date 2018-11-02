// Fill out your copyright notice in the Description page of Project Settings.

#include "MasterPawn.h"
#include "Camera/CameraComponent.h"


// Sets default values
AMasterPawn::AMasterPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    SpawnCollisionHandlingMethod = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

    VRCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    VRCamera->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AMasterPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMasterPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMasterPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

