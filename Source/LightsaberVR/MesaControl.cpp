// Fill out your copyright notice in the Description page of Project Settings.

#include "MesaControl.h"
#include "Components/StaticMeshComponent.h"
#include "Public/UObject/ConstructorHelpers.h"
#include "Materials/Material.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/Engine.h"
#include "Engine/StaticMesh.h"
#include "Boton.h"
#include "BotonStart.h"
#include "BotonExit.h"


// Sets default values
AMesaControl::AMesaControl()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Centro"));

    static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
    static ConstructorHelpers::FObjectFinder<UMaterial> MeshMaterial(TEXT("Material'/Game/LightsaberVR/Materials/MesaMaterial.MesaMaterial'"));

    Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesa"));
    Mesh->SetupAttachment(RootComponent);
    Mesh->SetRelativeLocation(FVector(0.0f, 0.0f, -5.0f));
    Mesh->SetWorldScale3D(FVector(0.7f, 2.0f, 0.1f));
    if (MeshAsset.Succeeded()) {
        Mesh->SetStaticMesh(MeshAsset.Object);
        if (MeshMaterial.Succeeded()) {
            Mesh->SetMaterial(0, MeshMaterial.Object);
        }
    }
    
}

// Called when the game starts or when spawned
void AMesaControl::BeginPlay()
{
	Super::BeginPlay();
    UWorld * const World = GetWorld();
    if (World) {
        FActorSpawnParameters SpawnParams;
        SpawnParams.Owner = this;
        SpawnParams.Instigator = Instigator;

        BotonIniciar = World->SpawnActor<ABoton>(ABotonStart::StaticClass(), FVector(0.0f, -80.0f, 0.0f), FRotator::ZeroRotator, SpawnParams);
        BotonIniciar->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);//segun el compilador de unral debo usar esto

        BotonSalir = World->SpawnActor<ABoton>(ABotonExit::StaticClass(), FVector(0.0f, 80.0f, 0.0f), FRotator::ZeroRotator, SpawnParams);
        BotonSalir->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);//segun el compilador de unral debo usar esto
    }
	
}

// Called every frame
void AMesaControl::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

