// Fill out your copyright notice in the Description page of Project Settings.

#include "Sable.h"
#include "Public/UObject/ConstructorHelpers.h"
#include "Engine/StaticMesh.h"
#include "Materials/Material.h"
#include "ProyectilEnemigo.h"
#include "Components/SphereComponent.h"

ASable::ASable() {
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    SableMango = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SableMango"));
    RootComponent = SableMango;

    static ConstructorHelpers::FObjectFinder<UStaticMesh> MangoAsset(TEXT("StaticMesh'/Game/LightsaberVR/Meshes/Lightsaber/SableMango.SableMango'"));
    static ConstructorHelpers::FObjectFinder<UMaterial> MangoMaterial(TEXT("Material'/Game/LightsaberVR/Materials/HandleSaberMaterial.HandleSaberMaterial'"));

    SableMango->SetWorldScale3D(FVector(0.8f, 0.8f, 1.0f));
    if (MangoAsset.Succeeded()) {
        SableMango->SetStaticMesh(MangoAsset.Object);
        if (MangoMaterial.Succeeded()) {
            SableMango->SetMaterial(0, MangoMaterial.Object);
        }
    }
    SableMango->SetCollisionProfileName(TEXT("Arma"));
    SableMango->SetSimulatePhysics(true);

    Laser = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Laser"));
    Laser->SetupAttachment(SableMango);

    static ConstructorHelpers::FObjectFinder<UStaticMesh> LaserAsset(TEXT("StaticMesh'/Game/LightsaberVR/Meshes/Lightsaber/SableLaser.SableLaser'"));
    static ConstructorHelpers::FObjectFinder<UStaticMesh> LaserExtremoAsset(TEXT("StaticMesh'/Game/LightsaberVR/Meshes/Lightsaber/SableLaserExtremo.SableLaserExtremo'"));
    static ConstructorHelpers::FObjectFinder<UMaterial> LaserMaterial(TEXT("Material'/Game/LightsaberVR/Materials/BlueSaberMaterial.BlueSaberMaterial'"));

    Laser->SetWorldScale3D(FVector(0.7f, 0.7f, 1.0f));
    Laser->SetRelativeLocation(FVector(0.0f, 0.0f, 10.0f));
    if (LaserAsset.Succeeded()) {
        Laser->SetStaticMesh(LaserAsset.Object);
        if (LaserMaterial.Succeeded()) {
            Laser->SetMaterial(0, LaserMaterial.Object);
        }
    }

    LaserExtremo = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LaserExtremo"));
    LaserExtremo->SetupAttachment(Laser);

    LaserExtremo->SetWorldScale3D(FVector(0.7f, 0.7f, 1.0f));
    LaserExtremo->SetRelativeLocation(FVector(0.0f, 0.0f, 100.0f));

    if (LaserExtremoAsset.Succeeded()) {
        LaserExtremo->SetStaticMesh(LaserExtremoAsset.Object);
        if (LaserMaterial.Succeeded()) {
            LaserExtremo->SetMaterial(0, LaserMaterial.Object);
        }
    }

    ColisionLaser = CreateDefaultSubobject<UCapsuleComponent>(TEXT("ColisionLaser"));
    ColisionLaser->SetupAttachment(RootComponent);
    ColisionLaser->SetRelativeLocation(FVector(0.0f, 0.0f, 61.0f));
    ColisionLaser->InitCapsuleSize(1.5f, 51.0f);
    ColisionLaser->SetCollisionProfileName(TEXT("Proyectil"));
    ColisionLaser->OnComponentBeginOverlap.AddDynamic(this, &ASable::OnBeginOverlapLaser);
    ColisionLaser->OnComponentEndOverlap.AddDynamic(this, &ASable::OnEndOverlapLaser);

    VelocidadActivacion = 3.0f;//escala 1 por segundo
    bAnimando = false;
    //bActivado = true;

    bActivado = false;
    Laser->SetVisibility(false);
    LaserExtremo->SetVisibility(false);
    Laser->SetRelativeScale3D(FVector(0.7f, 0.7f, 0.0f));

}

void ASable::BeginPlay() {
    Super::BeginPlay();
}

void ASable::Tick(float DeltaTime) {
    Super::Tick(DeltaTime);
    if (bAnimando) {
        if (bActivado) {//he activado, y esto animando, osea sale la espada hasta escala 1
            FVector Escala = Laser->GetRelativeTransform().GetScale3D();
            Escala += FVector(0.0f, 0.0f, VelocidadActivacion*DeltaTime);
            if (Escala.Z >= 1.0f) {
                Escala.Z = 1.0f;
                bAnimando = false;
            }
            Laser->SetRelativeScale3D(Escala);
        }
        else {//he activado, y esto animando, osea sale la espada hasta escala 1
            FVector Escala = Laser->GetRelativeTransform().GetScale3D();
            Escala += FVector(0.0f, 0.0f, -VelocidadActivacion*DeltaTime);
            if (Escala.Z <= 0.0f) {
                Escala.Z = 0.0f;
                bAnimando = false;
                Laser->SetVisibility(false);
                LaserExtremo->SetVisibility(false);
            }
            Laser->SetRelativeScale3D(Escala);
        }
    }
}

void ASable::AccionPrincipal() {
    if (bActivado) {
        bActivado = false;
        bAnimando = true;
    }
    else {
        bActivado = true;
        bAnimando = true;
        Laser->SetVisibility(true);
        LaserExtremo->SetVisibility(true);
        //debo iniciar animacion
    }
}

void ASable::AccionSecundaria() {
}

void ASable::Sujetar(UMotionControllerComponent * Controller) {
    SableMango->SetSimulatePhysics(false);
    AttachToComponent(Controller, FAttachmentTransformRules::KeepRelativeTransform);
    SetActorRelativeLocation(FVector(0.0, 0.0, -2.0f));
    SetActorRelativeRotation(FRotator(270.0f, 0.0f, 0.0f));
}

void ASable::Soltar() {
    SableMango->SetSimulatePhysics(true);
}

void ASable::OnBeginOverlapLaser(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult) {
    if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr) && (OtherActor != GetOwner())) { //no es necesario el ultimo, solo para este caso particular en el que no quiero que el propio conejo active esta funconalidad
        AProyectilEnemigo * const Proyectil = Cast<AProyectilEnemigo>(OtherActor);
        if (Proyectil && !Proyectil->IsPendingKill()) {
            USphereComponent * const ColisionProyectil= Cast<USphereComponent>(OtherComp);//para la casa no necesito verificar que haya tocado su staticmesh
            if (ColisionProyectil) {
                Proyectil->RecibirGolpe();
                    //ColisionController->GetComponentLocation() - Boton->GetComponentLocation()).Z;
                //UE_LOG(LogClass, Log, TEXT("Tocando boton, DC: %f"), DistanciaColision);
                /*if (ColisionController->GetName() == "ColisionControllerRight") {//podria ser util la diferencia
                }
                else if (ColisionController->GetName() == "ColisionControllerLeft") {
                }*/
            }
        }
    }
}

void ASable::OnEndOverlapLaser(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex) {
}
