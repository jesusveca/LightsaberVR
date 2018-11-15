// Fill out your copyright notice in the Description page of Project Settings.

#include "Trampa.h"
#include "Public/UObject/ConstructorHelpers.h"
#include "Engine/StaticMesh.h"
#include "Materials/Material.h"


// Sets default values
ATrampa::ATrampa()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> PuertaAsset(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	static ConstructorHelpers::FObjectFinder<UMaterial> PuertaMaterial(TEXT("Material'/Game/LightsaberVR/Materials/HandleSaberMaterial.HandleSaberMaterial'"));

	MeshTrampa = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TrampaMesh"));
	MeshTrampa->SetupAttachment(RootComponent);

	MeshTrampa->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));

	MeshTrampa->SetWorldScale3D(FVector(0.25f, 0.25f, 0.25f));
	if (PuertaAsset.Succeeded()) {
		MeshTrampa->SetStaticMesh(PuertaAsset.Object);
		if (PuertaMaterial.Succeeded()) {
			MeshTrampa->SetMaterial(0, PuertaMaterial.Object);
		}
	}

	ColisionTrampa = CreateDefaultSubobject<USphereComponent>(TEXT("ColisionTrampa"));
	ColisionTrampa->SetupAttachment(RootComponent);
	ColisionTrampa->InitSphereRadius(50.0f);
	//ColisionTrampa->InitBoxExtent(FVector(60.0f, 60.0f, 60.0f));


	VelocidadActivacion = 50.0f;//escala 1 por segundo
	bAnimando = false;
	bActivado = true;





}

// Called when the game starts or when spawned
void ATrampa::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATrampa::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (bAnimando) {
		if (bActivado) {//he activado, y esto animando, osea sale la espada hasta escala 1, activado significa cerrado
			FVector Location = MeshTrampa->GetRelativeTransform().GetLocation();
			Location += FVector(0.0f, 0.0f, VelocidadActivacion*DeltaTime);
			if (Location.Z >= 0.0f) {
				Location.Z = 0.0f;
				bAnimando = false;
			}
			MeshTrampa->SetRelativeLocation(Location);
		}
		else {//he activado, y esto animando, osea sale la espada hasta escala 1
			FVector Location = MeshTrampa->GetRelativeTransform().GetLocation();
			Location += FVector(0.0f, 0.0f, -VelocidadActivacion * DeltaTime);
			if (Location.Z <= -200.0f) {
				Location.Z = -200.0f;
				bAnimando = false;
			}
			MeshTrampa->SetRelativeLocation(Location);
		}
	}

}

