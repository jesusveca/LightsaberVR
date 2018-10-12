// Fill out your copyright notice in the Description page of Project Settings.

#include "ParteC.h"
#include "Public/UObject/ConstructorHelpers.h"
#include "Engine/StaticMesh.h"
#include "Materials/Material.h"
#include "Components/BoxComponent.h"

AParteC::AParteC() {
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    Part = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Parte"));
    RootComponent = Part;
    
    static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
    static ConstructorHelpers::FObjectFinder<UMaterial> MeshMaterial(TEXT("Material'/Game/LightsaberVR/Materials/BlueSaberMaterial.BlueSaberMaterial'"));

    Part->SetWorldScale3D(FVector(0.25f, 0.25f, 0.25f));
    if (MeshAsset.Succeeded()) {
        Part->SetStaticMesh(MeshAsset.Object);
    }
    Part->SetCollisionProfileName(TEXT("Arma"));
    Part->SetSimulatePhysics(true);

    Colision = CreateDefaultSubobject<UBoxComponent>(TEXT("Colision"));
    Colision->SetupAttachment(RootComponent);
    Colision->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
    Colision->InitBoxExtent(FVector(25.0f, 25.0f, 25.0f));

	static ConstructorHelpers::FObjectFinder<UMaterial> MaterialNormalAsset(TEXT("Material'/Game/LightsaberVR/Materials/ObjetoCNormalMaterial.ObjetoCNormalMaterial'"));//de usar este creo que debo crear un obtener un  material y ponerselo, este tiene el pivot en el centro de la esfera
	if (MaterialNormalAsset.Succeeded()) {
		MaterialNormal = MaterialNormalAsset.Object;
        Part->SetMaterial(0, MaterialNormalAsset.Object);
	}

	static ConstructorHelpers::FObjectFinder<UMaterial> MaterialActiveAsset(TEXT("Material'/Game/LightsaberVR/Materials/ObjetoCActiveMaterial.ObjetoCActiveMaterial'"));//de usar este creo que debo crear un obtener un  material y ponerselo, este tiene el pivot en el centro de la esfera
	if (MaterialActiveAsset.Succeeded()) {
		MaterialActive = MaterialActiveAsset.Object;
	}
}

void AParteC::BeginPlay() {
    Super::BeginPlay();
}

void AParteC::Tick(float DeltaTime) {
    Super::Tick(DeltaTime);
}

void AParteC::AccionPrincipal() {
}

void AParteC::AccionSecundaria() {
}

void AParteC::Sujetar(UMotionControllerComponent * Controller) {
    Part->SetSimulatePhysics(false);
    AttachToComponent(Controller, FAttachmentTransformRules::KeepRelativeTransform);
    SetActorRelativeLocation(FVector(10.0, 0.0, 0.0f));
}

void AParteC::Soltar() {
    Part->SetSimulatePhysics(true);
}

void AParteC::ActivateObjetivo() {
    Part->SetMaterial(0, MaterialActive);
}

void AParteC::DeactivateObjetivo() {
    Part->SetMaterial(0, MaterialNormal);
}






