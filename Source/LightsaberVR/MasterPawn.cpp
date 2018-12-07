// Fill out your copyright notice in the Description page of Project Settings.

#include "MasterPawn.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"


// Sets default values
AMasterPawn::AMasterPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    SpawnCollisionHandlingMethod = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

    VRCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    VRCamera->SetupAttachment(RootComponent);
    VRCamera->SetRelativeRotation(FRotator(-85.0f, 0.0f, 0.0f));

    Velocidad = 1000.0f;

    bMouseInWorld = true;

}

// Called when the game starts or when spawned
void AMasterPawn::BeginPlay()
{
	Super::BeginPlay();
    SetActorLocation(FVector(-500.0f, 1500.0f, 2500.0f));
    SetActorRotation(FRotator(0.0f, 90.0f, 0.0f));
	
}

// Called every frame
void AMasterPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    if (Movimiento != FVector::ZeroVector) {
        FVector Desplazamiento = Movimiento.X * GetActorForwardVector() + Movimiento.Y * GetActorRightVector();
        SetActorLocation(GetActorLocation() + Desplazamiento.GetSafeNormal()*Velocidad*DeltaTime);
    }

}

// Called to bind functionality to input
void AMasterPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
    InputComponent->BindAxis("MoveForward", this, &AMasterPawn::MoveForward);
    InputComponent->BindAxis("MoveRight", this, &AMasterPawn::MoveRight);
}

void AMasterPawn::MoveForward(float AxisValue) {
    Movimiento.X = AxisValue;
}

void AMasterPawn::MoveRight(float AxisValue) {
    Movimiento.Y = AxisValue;
}

