// Fill out your copyright notice in the Description page of Project Settings.

#include "PuertaJuego.h"
#include "Public/UObject/ConstructorHelpers.h"
#include "Engine/StaticMesh.h"
#include "Materials/Material.h"



// Sets default values
APuertaJuego::APuertaJuego()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> PuertaAsset(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	static ConstructorHelpers::FObjectFinder<UMaterial> PuertaMaterial(TEXT("Material'/Game/LightsaberVR/Materials/HandleSaberMaterial.HandleSaberMaterial'"));

	MeshPuertaJuego = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PuertaJuegoMesh"));
	MeshPuertaJuego->SetupAttachment(RootComponent);

	MeshPuertaJuego->SetWorldScale3D(FVector(0.25f, 1.0f, 1.0f));
	if (PuertaAsset.Succeeded()) {
		MeshPuertaJuego->SetStaticMesh(PuertaAsset.Object);
		if (PuertaMaterial.Succeeded()) {
			MeshPuertaJuego->SetMaterial(0, PuertaMaterial.Object);
		}
	}

	ColisionPuertaJuego = CreateDefaultSubobject<UBoxComponent>(TEXT("ColisionPuertaJuego"));
	ColisionPuertaJuego->SetupAttachment(RootComponent);
	ColisionPuertaJuego->InitBoxExtent(FVector(60.0f, 60.0f, 60.0f));
	//ColisionPuerta->OnComponentBeginOverlap.AddDynamic(this, &ASable::OnBeginOverlapLaser);
	//ColisionLaser->OnComponentEndOverlap.AddDynamic(this, &ASable::OnEndOverlapLaser);

	VelocidadActivacion = 50.0f;//escala 1 por segundo
	bAnimando = false;
	bActivado = true;

}

// Called when the game starts or when spawned
void APuertaJuego::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APuertaJuego::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (bAnimando) {
		if (bActivado) {//he activado, y esto animando, osea sale la espada hasta escala 1, activado significa cerrado
			FVector Location = MeshPuertaJuego->GetRelativeTransform().GetLocation();
			Location += FVector(0.0f, 0.0f, VelocidadActivacion*DeltaTime);
			if (Location.Z >= 0.0f) {
				Location.Z = 0.0f;
				bAnimando = false;
			}
			MeshPuertaJuego->SetRelativeLocation(Location);
		}
		else {//he activado, y esto animando, osea sale la espada hasta escala 1
			FVector Location = MeshPuertaJuego->GetRelativeTransform().GetLocation();
			Location += FVector(0.0f, 0.0f, -VelocidadActivacion * DeltaTime);
			if (Location.Z <= -200.0f) {
				Location.Z = -200.0f;
				bAnimando = false;
			}
			MeshPuertaJuego->SetRelativeLocation(Location);
		}
	}
}

