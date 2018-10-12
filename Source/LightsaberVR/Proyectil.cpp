// Fill out your copyright notice in the Description page of Project Settings.

#include "Proyectil.h"
#include "Public/UObject/ConstructorHelpers.h"
#include "Engine/Engine.h"
#include "Engine/StaticMesh.h"
#include "Materials/Material.h"
#include "Kismet/GameplayStatics.h"
#include "IA/SCharacter.h"


// Sets default values
AProyectil::AProyectil() {
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    Velocidad = 1000.0f;
    Poder = 25.0f;
    bLanzado = false;

    Velocidad = 1000.0f;
    Poder = 30.0f;
    bLanzado = false;

    static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));
    static ConstructorHelpers::FObjectFinder<UMaterial> MeshMaterial(TEXT("Material'/Game/LightsaberVR/Materials/BlueSaberMaterial.BlueSaberMaterial'"));

    Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
    RootComponent = Mesh;
    Mesh->SetWorldScale3D(FVector(0.15f, 0.15f, 0.15f));
    if (MeshAsset.Succeeded()) {
        Mesh->SetStaticMesh(MeshAsset.Object);
        if (MeshMaterial.Succeeded()) {
            Mesh->SetMaterial(0, MeshMaterial.Object);
        }
    }
    //Mesh->SetCollisionProfileName(TEXT("Custom"));
    //Mesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    //Mesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);

    Colision = CreateDefaultSubobject<USphereComponent>(TEXT("Colision"));
    Colision->SetupAttachment(RootComponent);
    Colision->InitSphereRadius(12.5f);
    Colision->SetCollisionProfileName(TEXT("Proyectil"));
    Colision->OnComponentBeginOverlap.AddDynamic(this, &AProyectil::OnBeginOverlap);


    EfectoImpacto = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("EfectoImpacto"));
    EfectoImpacto->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AProyectil::BeginPlay() {
	Super::BeginPlay();
	
}

// Called every frame
void AProyectil::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
    if (bLanzado) {
        SetActorLocation(GetActorLocation() + GetActorForwardVector() * Velocidad * DeltaTime);
    }

}

void AProyectil::Lanzar() {
    bLanzado = true;
}

void AProyectil::RecibirGolpe() {
    Destroy();
}

void AProyectil::OnBeginOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult) {
    if ( (OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr) && (OtherActor != GetOwner())) { //no es necesario el ultimo, solo para este caso particular en el que no quiero que el propio conejo active esta funconalidad
        if(GEngine)//no hacer esta verificación provocaba error al iniciar el editor
            GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT("Overlap"));
        ASCharacter* const Enemigo = Cast<ASCharacter>(OtherActor);
        if (Enemigo && !Enemigo->IsPendingKill()) {
            //Player->RecibirAtaque(Poder, GetActorLocation());
            Enemigo->RecibirAtaque(Poder);
            Destroy();
        }
    }

}
