// Fill out your copyright notice in the Description page of Project Settings.

#include "Puerta.h"
#include "Public/UObject/ConstructorHelpers.h"
#include "Engine/StaticMesh.h"
#include "Materials/Material.h"


// Sets default values
APuerta::APuerta()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

    static ConstructorHelpers::FObjectFinder<UStaticMesh> PuertaAsset(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
    static ConstructorHelpers::FObjectFinder<UMaterial> PuertaMaterial(TEXT("Material'/Game/LightsaberVR/Materials/HandleSaberMaterial.HandleSaberMaterial'"));

    MeshPuerta = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PuertaMesh"));
    MeshPuerta->SetupAttachment(RootComponent);

    MeshPuerta->SetWorldScale3D(FVector(1.0f, 3.0f, 2.0f));
    if (PuertaAsset.Succeeded()) {
        MeshPuerta->SetStaticMesh(PuertaAsset.Object);
        if (PuertaMaterial.Succeeded()) {
            MeshPuerta->SetMaterial(0, PuertaMaterial.Object);
        }
    }

    ColisionPuerta = CreateDefaultSubobject<UBoxComponent>(TEXT("ColisionPuerta"));
    ColisionPuerta->SetupAttachment(RootComponent);
    ColisionPuerta->InitBoxExtent(FVector(100.0f, 300.0f, 200.0f));
    //ColisionPuerta->OnComponentBeginOverlap.AddDynamic(this, &ASable::OnBeginOverlapLaser);
    //ColisionLaser->OnComponentEndOverlap.AddDynamic(this, &ASable::OnEndOverlapLaser);

    VelocidadActivacion = 50.0f;//escala 1 por segundo
    bAnimando = false;

    bActivado = true;

}

// Called when the game starts or when spawned
void APuerta::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APuerta::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    if (bAnimando) {
        if (bActivado) {//he activado, y esto animando, osea sale la espada hasta escala 1, activado significa cerrado
            FVector Location = MeshPuerta->GetRelativeTransform().GetLocation();
            Location += FVector(0.0f, 0.0f, VelocidadActivacion*DeltaTime);
            if (Location.Z >= 0.0f) {
                Location.Z = 0.0f;
                bAnimando = false;
            }
            MeshPuerta->SetRelativeLocation(Location);
        }
        else {//he activado, y esto animando, osea sale la espada hasta escala 1
            FVector Location = MeshPuerta->GetRelativeTransform().GetLocation();
            Location += FVector(0.0f, 0.0f, -VelocidadActivacion*DeltaTime);
            if (Location.Z <= -200.0f) {
                Location.Z = -200.0f;
                bAnimando = false;
            }
            MeshPuerta->SetRelativeLocation(Location);
        }
    }
}

/*void APuerta::ClientAbrir() {
    if (bActivado) {
        bActivado = false;
        bAnimando = true;
    }
}

void APuerta::ClientCerrar() {
    if (!bActivado) {
        bActivado = true;
        bAnimando = true;
        //debo iniciar animacion
    }
}*/

