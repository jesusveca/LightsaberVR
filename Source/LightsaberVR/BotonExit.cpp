// Fill out your copyright notice in the Description page of Project Settings.

#include "BotonExit.h"
#include "Components/StaticMeshComponent.h"
#include "Public/UObject/ConstructorHelpers.h"
#include "Materials/Material.h"
#include "Kismet/GameplayStatics.h"
#include "VRPawn.h"
#include "Engine/Engine.h"
#include "Engine/StaticMesh.h"
#include "LightsaberVRGameModeBase.h"

ABotonExit::ABotonExit() {
	PrimaryActorTick.bCanEverTick = true;

    FVector EscalaBotones = FVector(0.5f);
    
	Borde = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Borde"));
    RootComponent = Borde;
    //Borde->SetupAttachment(RootComponent);
	Borde->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	Borde->SetWorldScale3D(EscalaBotones);

    static ConstructorHelpers::FObjectFinder<UStaticMesh> BordeAsset(TEXT("StaticMesh'/Game/LightsaberVR/Meshes/Botones/BotonS_BordeBoton.BotonS_BordeBoton'"));//de usar este creo que debo crear un obtener un  material y ponerselo, este tiene el pivot en el centro de la esfera
    if (BordeAsset.Succeeded()) {
        Borde->SetStaticMesh(BordeAsset.Object);
        static ConstructorHelpers::FObjectFinder<UMaterial> BordeMaterialAsset(TEXT("Material'/Game/LightsaberVR/Materials/Botones/BotonBordeNormal.BotonBordeNormal'"));//de usar este creo que debo crear un obtener un  material y ponerselo, este tiene el pivot en el centro de la esfera
        if (BordeMaterialAsset.Succeeded()) {
            Borde->SetMaterial(0, BordeMaterialAsset.Object);
        }
    }

	Boton = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Boton"));
    Boton->SetupAttachment(RootComponent);
	Boton->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	Boton->SetWorldScale3D(EscalaBotones);

    static ConstructorHelpers::FObjectFinder<UStaticMesh> BotonAsset(TEXT("StaticMesh'/Game/LightsaberVR/Meshes/Botones/BotonS_Boton.BotonS_Boton'"));//de usar este creo que debo crear un obtener un  material y ponerselo, este tiene el pivot en el centro de la esfera
    if (BotonAsset.Succeeded()) {
        Boton->SetStaticMesh(BotonAsset.Object);
        //static ConstructorHelpers::FObjectFinder<UMaterial> BotonMaterialAsset(TEXT("Material'/Game/Trasnformation/Assets/Meshes/Botones/BotonMaterial_5.BotonMaterial_5'"));//de usar este creo que debo crear un obtener un  material y ponerselo, este tiene el pivot en el centro de la esfera
        static ConstructorHelpers::FObjectFinder<UMaterial> BotonMaterialAsset(TEXT("Material'/Game/LightsaberVR/Materials/Botones/BotonExitNormal.BotonExitNormal'"));//de usar este creo que debo crear un obtener un  material y ponerselo, este tiene el pivot en el centro de la esfera
        if (BotonMaterialAsset.Succeeded()) {
            MaterialNormal = BotonMaterialAsset.Object;
            MaterialPresionado = BotonMaterialAsset.Object;
            Boton->SetMaterial(0, BotonMaterialAsset.Object);
        }
    }

    /*static ConstructorHelpers::FObjectFinder<UMaterial> BotonMaterialPAsset(TEXT("Material'/Game/Trasnformation/Assets/Meshes/Botones/MaterialBotonC_2.MaterialBotonC_2'"));//de usar este creo que debo crear un obtener un  material y ponerselo, este tiene el pivot en el centro de la esfera
    if (BotonMaterialPAsset.Succeeded()) {
        MaterialPresionado = BotonMaterialPAsset.Object;
    }*/

    Boton->OnComponentBeginOverlap.AddDynamic(this, &ABotonExit::OnBeginOverlapBoton);
    Boton->OnComponentEndOverlap.AddDynamic(this, &ABotonExit::OnEndOverlapBoton);

    VelocidadNormal = 6.0f;
    AlturaContacto = -3.0f;
    AlturaFondo = -4.0f;
    AlturaNormal = 0.0f;
    AlturaPresionado = -2.0f;
}

void ABotonExit::BeginPlay() {
    Super::BeginPlay();
    //Boton->SetRelativeLocation(FVector(0.0f, 0.0f, -10.0f));
}

void ABotonExit::Tick(float DeltaTime) {
    Super::Tick(DeltaTime);
    if (bPressing) {//osea hay un elemento entrando en contacto con el boton
        if (!bPressed) {
            bPosicionNormal = false;
            bPosicionPresionado = false;
            float h = GetTransform().InverseTransformPosition(ColisionControl->GetComponentLocation()).Z;
            //UE_LOG(LogClass, Log, TEXT("h: %f"), h);
            //UE_LOG(LogClass, Log, TEXT("h - DistanciaColision: %f"), h - DistanciaColision);
            float zPosicion = FMath::Clamp(h - DistanciaColision, -4.0f, 0.0f);
            //UE_LOG(LogClass, Log, TEXT("zPosicion: %f"), zPosicion);
            FVector NewBotonPosition = FVector(0.0f, 0.0f, zPosicion);
            //UE_LOG(LogClass, Log, TEXT("Tocando boton"));
            Boton->SetRelativeLocation(NewBotonPosition);
        }
    }
    else {
        if (!bPosicionNormal && !bPressed) {//si no estoy en la posicion normal y no he sidopresionado , regreso a la posicion normal
            Boton->SetRelativeLocation(FMath::Lerp(Boton->GetRelativeTransform().GetLocation(), FVector(0.0f, 0.0f, AlturaNormal), DeltaTime * VelocidadNormal));
            if (Boton->GetRelativeTransform().GetLocation() == FVector(0.0f, 0.0f, AlturaNormal)) {
                bPosicionNormal = true;
            }
        }
        if (!bPosicionPresionado && bPressed) {//si no estoy en la posicion normal y no he sidopresionado , regreso a la posicion normal
            Boton->SetRelativeLocation(FMath::Lerp(Boton->GetRelativeTransform().GetLocation(), FVector(0.0f, 0.0f, AlturaPresionado), DeltaTime * VelocidadNormal));
            if (Boton->GetRelativeTransform().GetLocation() == FVector(0.0f, 0.0f, AlturaPresionado)) {
                bPosicionPresionado = true;
            }
        }
    }

  
}

void ABotonExit::SendSignalPressed() {
    Super::SendSignalPressed();
    AGameModeBase * GameMode = UGameplayStatics::GetGameMode(GetWorld());
    ALightsaberVRGameModeBase * LightGameMode = Cast<ALightsaberVRGameModeBase>(GameMode);
    if (LightGameMode) {
        //LightGameMode->QuitGame();

    }
}

void ABotonExit::SendSignalReleased() {
    UE_LOG(LogClass, Log, TEXT("Send Signal Released"));
}

void ABotonExit::OnBeginOverlapBoton(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult) {
    if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr) && (OtherActor != GetOwner())) { //no es necesario el ultimo, solo para este caso particular en el que no quiero que el propio conejo active esta funconalidad
        AVRPawn * const VRPawn = Cast<AVRPawn>(OtherActor);
        if (VRPawn && !VRPawn->IsPendingKill()) {
            UCapsuleComponent * const ColisionController = Cast<UCapsuleComponent>(OtherComp);//para la casa no necesito verificar que haya tocado su staticmesh
            if (ColisionController) {
                ColisionControl = ColisionController;
                bPressing = true;
                DistanciaColision = (GetTransform().InverseTransformPosition(ColisionController->GetComponentLocation()) - Boton->GetRelativeTransform().GetLocation()).Z;
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

void ABotonExit::OnEndOverlapBoton(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex) {
    if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr) && (OtherActor != GetOwner())) { //no es necesario el ultimo, solo para este caso particular en el que no quiero que el propio conejo active esta funconalidad
        AVRPawn * const VRPawn = Cast<AVRPawn>(OtherActor);
        if (VRPawn && !VRPawn->IsPendingKill()) {
            UCapsuleComponent * const ColisionController = Cast<UCapsuleComponent>(OtherComp);//para la casa no necesito verificar que haya tocado su staticmesh
            if (ColisionController == ColisionControl) {
                ColisionControl = nullptr;
                bPressing = false;
                //UE_LOG(LogClass, Log, TEXT("Soltando boton"));
                /*if (ColisionController->GetName() == "ColisionControllerRight") {//podria ser util la diferencia
                }
                else if (ColisionController->GetName() == "ColisionControllerLeft") {
                }*/
            }
        }
    }
}

//necesito agregar la colision para el boton, con el cual ira manteniendo la distancia con el control, hasta que no pase de los limites, es decir posicino de descanso y posicion fondo
//
//no debo exceder esos limitas asi podre hacer que salga de la colision
//igula si el control baja en exceso








