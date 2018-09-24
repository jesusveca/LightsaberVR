// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/UObject/ConstructorHelpers.h"
#include "Engine/Engine.h"
#include "Engine/StaticMesh.h"
#include "Materials/Material.h"
#include "Kismet/GameplayStatics.h"
#include "VRPawn.h"


#include "MyProyectil.h"

// Sets default values
AMyProyectil::AMyProyectil()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
    Velocidad = 1000.0f;
    Poder = 30.0f;
    bLanzado = false;

    static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));
    static ConstructorHelpers::FObjectFinder<UMaterial> MeshMaterial(TEXT("Material'/Game/LightsaberVR/Materials/RedSaberMaterial.RedSaberMaterial'"));

    Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
    RootComponent = Mesh;
    Mesh->SetWorldScale3D(FVector(0.25f, 0.25f, 0.25f));
    if (MeshAsset.Succeeded())
    {
        Mesh->SetStaticMesh(MeshAsset.Object);
        if (MeshMaterial.Succeeded())
        {
            Mesh->SetMaterial(0, MeshMaterial.Object);
        }
    }

    Colision = CreateDefaultSubobject<USphereComponent>(TEXT("Colision"));
    Colision->SetupAttachment(RootComponent);
    Colision->InitSphereRadius(12.5f);
    Colision->SetCollisionProfileName(TEXT("ProyectilEnemigo"));
    Colision->OnComponentBeginOverlap.AddDynamic(this, &AMyProyectil::OnBeginOverlap);

    EfectoImpacto = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("EfectoImpacto"));
    EfectoImpacto->SetupAttachment(RootComponent);
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

    bLanzado = true;
}

void AMyProyectil::OnBeginOverlap(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
    if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr) && (OtherActor != GetOwner()))
    {                //no es necesario el ultimo, solo para este caso particular en el que no quiero que el propio conejo active esta funconalidad
        if (GEngine) //no hacer esta verificaci�n provocaba error al iniciar el editor
            GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT("Overlap"));
        AVRPawn *const Player = Cast<AVRPawn>(OtherActor);
        if (Player && !Player->IsPendingKill())
        {
            USphereComponent *const CuerpoPlayer = Cast<USphereComponent>(OtherComp);
            if (CuerpoPlayer)
            {
                //Player->RecibirAtaque(Poder, GetActorLocation());
                Destroy();
            }
        }
        /*else {
            EfectoImpacto->Activate(false);
            EfectoImpacto->SetRelativeLocation(GetActorLocation());
            EfectoImpacto->Activate(true);
            UWorld * const World = GetWorld();
            if (World) {
                UGameplayStatics::SpawnEmitterAtLocation(World, EfectoImpacto->Template, FTransform(FRotator::ZeroRotator, GetActorLocation()));
            }
            Destroy();
        }*/
    }
}
