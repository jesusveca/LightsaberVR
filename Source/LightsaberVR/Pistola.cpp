// Fill out your copyright notice in the Description page of Project Settings.

#include "Pistola.h"
#include "Public/UObject/ConstructorHelpers.h"
#include "Engine/StaticMesh.h"
#include "Engine/Engine.h"
#include "Materials/Material.h"
#include "Components/CapsuleComponent.h"
#include "Proyectil.h"
// Sets default values
APistola::APistola()
{
    PrimaryActorTick.bCanEverTick = true;

    // MeshPistola = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MeshPistola"));
    MeshPistola = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshPistola"));

    RootComponent = MeshPistola;
    static ConstructorHelpers::FObjectFinder<UStaticMesh> MangoAsset(TEXT("StaticMesh'/Game/LightsaberVR/Meshes/Lightsaber/SableMango.SableMango'"));
    static ConstructorHelpers::FObjectFinder<UMaterial> MangoMaterial(TEXT("Material'/Game/LightsaberVR/Materials/HandleSaberMaterial.HandleSaberMaterial'"));

    MeshPistola->SetWorldScale3D(FVector(0.8f, 0.8f, 1.0f));
    if (MangoAsset.Succeeded())
    {
        MeshPistola->SetStaticMesh(MangoAsset.Object);
        if (MangoMaterial.Succeeded())
        {
            MeshPistola->SetMaterial(0, MangoMaterial.Object);
        }
    }
    MeshPistola->SetCollisionProfileName(TEXT("Arma"));
    MeshPistola->SetSimulatePhysics(true);
    ColisionPistola = CreateDefaultSubobject<UCapsuleComponent>(TEXT("ColisionPistola"));
    ColisionPistola->SetupAttachment(RootComponent);
    ColisionPistola->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
    ColisionPistola->InitCapsuleSize(1.5f, 51.0f);
    ColisionPistola->OnComponentBeginOverlap.AddDynamic(this, &APistola::OnBeginOverlapPistola);
    ColisionPistola->OnComponentEndOverlap.AddDynamic(this, &APistola::OnEndOverlapPistola);
}

void APistola::BeginPlay()
{
    Super::BeginPlay();
}

void APistola::OnBeginOverlapPistola(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
    if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr) && (OtherActor != GetOwner()))
    {
        if (GEngine) //no hacer esta verificaci�n provocaba error al iniciar el editor
            GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT("oVERLAPsIPISTLA"));

        // AProyectilEnemigo *const Proyectil = Cast<AProyectilEnemigo>(OtherActor);
        // if (Proyectil && !Proyectil->IsPendingKill())
        // {
        // 	USphereComponent *const ColisionProyectil = Cast<USphereComponent>(OtherComp); //para la casa no necesito verificar que haya tocado su staticmesh
        // 	if (ColisionProyectil)
        // 	{
        // 		Proyectil->RecibirGolpe();
        // 		//ColisionController->GetComponentLocation() - Boton->GetComponentLocation()).Z;
        // 		//UE_LOG(LogClass, Log, TEXT("Tocando boton, DC: %f"), DistanciaColision);
        // 		/*if (ColisionController->GetName() == "ColisionControllerRight") {//podria ser util la diferencia
        //         }
        //         else if (ColisionController->GetName() == "ColisionControllerLeft") {
        //         }*/
        // 	}
        // }
    }
}

void APistola::OnEndOverlapPistola(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex)
{
}

void APistola::AccionPrincipal()
{
    if (GEngine) //no hacer esta verificaci�n provocaba error al iniciar el editor
        GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT("Accion Principal"));
    // if (bActivado) {
    //     bActivado = false;
    //     bAnimando = true;
    // }
    // else {
    //     bActivado = true;
    //     bAnimando = true;
    //     Pistola->SetVisibility(true);
    //     PistolaExtremo->SetVisibility(true);
    //     //debo iniciar animacion
    // }
}

void APistola::AccionSecundaria()
{
        if (GEngine) //no hacer esta verificaci�n provocaba error al iniciar el editor
        GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT("Accion Secundaria"));
}

// void APistola::Sujetar(UMotionControllerComponent *Controller)
void APistola::Sujetar()
{
    if (GEngine) //no hacer esta verificaci�n provocaba error al iniciar el editor
        GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT("Sugetando pistola"));
    MeshPistola->SetSimulatePhysics(false);
    // AttachToComponent(Controller, FAttachmentTransformRules::KeepRelativeTransform);

    // SetActorRelativeLocation(FVector(0.0, 0.0, -2.0f));
    // SetActorRelativeRotation(FRotator(0.0f, 270.0f, 0.0f));
    // AProyectil *const Proyectil = Cast<AProyectil>(Controller);
    // Proyectil->Lanzar();
}

void APistola::Soltar()
{
    MeshPistola->SetSimulatePhysics(true);
}
