// Fill out your copyright notice in the Description page of Project Settings.

#include "VRPawn.h"
#include "MotionControllerComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "Public/UObject/ConstructorHelpers.h"
#include "Engine/Engine.h"
#include "Engine/StaticMesh.h"
#include "Materials/Material.h"
#include "Kismet/GameplayStatics.h"
#include "Public/HeadMountedDisplayFunctionLibrary.h"
#include <limits>


// Sets default values
AVRPawn::AVRPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    SpawnCollisionHandlingMethod = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

    DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
    RootComponent = DefaultSceneRoot;

    VRCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("VRCamera"));
    VRCamera->SetupAttachment(RootComponent);

    ColisionHead = CreateDefaultSubobject<UCapsuleComponent>(TEXT("ColisionHead"));
    ColisionHead->SetupAttachment(VRCamera);
    ColisionHead->SetRelativeLocation(FVector(0.0f, 0.0f, -100.0f));
    //ColisionHead->InitSphereRadius(20.0f);
    ColisionHead->InitCapsuleSize(35.0f, 140.0f);

    /*Capture = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("Capture"));
    Capture->SetupAttachment(VRCamera);
    Render = CreateDefaultSubobject<UTextureRenderTarget2D>(TEXT("Render"));
    static ConstructorHelpers::FObjectFinder<UTextureRenderTarget2D> RenderAsset(TEXT("TextureRenderTarget2D'/Game/Trasnformation/VRCapture.VRCapture'"));//de usar este creo que debo crear un obtener un  material y ponerselo, este tiene el pivot en el centro de la esfera
    if (RenderAsset.Succeeded()) {
        Render = RenderAsset.Object;
        Capture->TextureTarget = Render;
        Capture->CaptureSource = ESceneCaptureSource::SCS_FinalColorLDR;
    }*/

    MotionControllerLeft = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("MotionControllerLeft"));
    MotionControllerLeft->SetupAttachment(RootComponent);
    MotionControllerLeft->SetRelativeLocation(FVector(-50.0f, -40.0f, -20.0f));
    MotionControllerLeft->Hand = EControllerHand::Left;

    MotionControllerRight = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("MotionControllerRight"));
    MotionControllerRight->SetupAttachment(RootComponent);
    MotionControllerRight->SetRelativeLocation(FVector(50.0f, 40.0f, 0.0f));
    MotionControllerRight->Hand = EControllerHand::Right;

    ViveControllerLeft = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ViveControllerLeft"));
    ViveControllerLeft->SetupAttachment(MotionControllerLeft);
    ViveControllerLeft->SetRelativeRotation(FRotator(0.0f, 90.0f, 90.0f));//ver cual es el yaw y el roll
    ViveControllerLeft->SetCollisionProfileName(TEXT("OverlapAllDynamic"));

    ViveControllerRight = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ViveControllerRight"));
    ViveControllerRight->SetupAttachment(MotionControllerRight);
    ViveControllerRight->SetRelativeRotation(FRotator(0.0f, 90.0f, 90.0f));
    ViveControllerRight->SetCollisionProfileName(TEXT("OverlapAllDynamic"));


    static ConstructorHelpers::FObjectFinder<UStaticMesh> ViveControllerMeshAsset(TEXT("StaticMesh'/Game/ControllerSetup/vr_controller_vive_1_5.vr_controller_vive_1_5'"));//de usar este creo que debo crear un obtener un  material y ponerselo, este tiene el pivot en el centro de la esfera
    if (ViveControllerMeshAsset.Succeeded()) {
        ViveControllerLeft->SetStaticMesh(ViveControllerMeshAsset.Object);
        ViveControllerRight->SetStaticMesh(ViveControllerMeshAsset.Object);
        static ConstructorHelpers::FObjectFinder<UMaterial> ViveControllerMaterialAsset(TEXT("Material'/Game/ControllerSetup/ControlMaterial.ControlMaterial'"));//de usar este creo que debo crear un obtener un  material y ponerselo, este tiene el pivot en el centro de la esfera
        if (ViveControllerMaterialAsset.Succeeded()) {
            ViveControllerLeft->SetMaterial(0, ViveControllerMaterialAsset.Object);
            ViveControllerRight->SetMaterial(0, ViveControllerMaterialAsset.Object);
        }
    }

	ColisionControllerLeft = CreateDefaultSubobject<UCapsuleComponent>(TEXT("ColisionControllerLeft"));
	ColisionControllerLeft->SetupAttachment(MotionControllerLeft);
	ColisionControllerLeft->InitCapsuleSize(5.0f, 5.0f);
	ColisionControllerLeft->SetRelativeLocation(FVector(0.0f, 0.0f, -4.0f));
	ColisionControllerLeft->SetRelativeRotation(FRotator(0.0f, 0.0f, 90.0f));
    ColisionControllerLeft->OnComponentBeginOverlap.AddDynamic(this, &AVRPawn::OnBeginOverlapControllerLeft);
    ColisionControllerLeft->OnComponentEndOverlap.AddDynamic(this, &AVRPawn::OnEndOverlapControllerLeft);

	ColisionControllerRight = CreateDefaultSubobject<UCapsuleComponent>(TEXT("ColisionControllerRight"));
	ColisionControllerRight->SetupAttachment(MotionControllerRight);
	ColisionControllerRight->InitCapsuleSize(5.0f, 5.0f);
	ColisionControllerRight->SetRelativeLocation(FVector(0.0f, 0.0f, -4.0f));
	ColisionControllerRight->SetRelativeRotation(FRotator(0.0f, 0.0f, 90.0f));
    ColisionControllerRight->OnComponentBeginOverlap.AddDynamic(this, &AVRPawn::OnBeginOverlapControllerRight);
    ColisionControllerRight->OnComponentEndOverlap.AddDynamic(this, &AVRPawn::OnEndOverlapControllerRight);


    Interaction = CreateDefaultSubobject<UWidgetInteractionComponent>(TEXT("Interaction"));
    Interaction->SetupAttachment(MotionControllerRight);
    //Interaction->bShowDebug = true;

    Movimiento = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Movimiento"));

    bBuscarArmaRight = true;
    bBuscarArmaLeft= true;
    Velocidad = 200.0f;
    VelocidadDash = 1000.0f;
    DistanciaDash = 1000.0f;

}

// Called when the game starts or when spawned
void AVRPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AVRPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    float CX = GetInputAxisValue("ControllerForward");
    float CY = GetInputAxisValue("ControllerRight");
    float CZ = GetInputAxisValue("ControllerUp");
    if (CX != 0.0f || CY != 0.0f || CZ != 0.0f) {
        FVector Desplazamiento (CX, CY, CZ);
        //MotionControllerRight->SetWorldLocation(MotionControllerRight->GetComponentLocation() + Desplazamiento.GetSafeNormal() * Velocidad/2 * DeltaTime);
        MotionControllerRight->SetRelativeLocation(MotionControllerRight->GetRelativeTransform().GetLocation() + Desplazamiento.GetSafeNormal() * Velocidad/2 * DeltaTime);
    }
    float CRoll = GetInputAxisValue("ControllerRoll");
    float CPitch = GetInputAxisValue("ControllerPitch");
    float CYaw = GetInputAxisValue("ControllerYaw");
    if (CRoll != 0.0f || CPitch != 0.0f || CYaw != 0.0f) {
        FRotator Rotacion(CPitch, CYaw, CRoll);
        MotionControllerRight->AddRelativeRotation(Rotacion);
    }

    GrabLeftTick();
    GrabRightTick();
}

// Called to bind functionality to input
void AVRPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

    InputComponent->BindAction("GrabRight", IE_Pressed, this, &AVRPawn::GrabRightPressed);
    InputComponent->BindAction("GrabRight", IE_Released, this, &AVRPawn::GrabRightReleased);
    InputComponent->BindAction("GrabLeft", IE_Pressed, this, &AVRPawn::GrabLeftPressed);
    InputComponent->BindAction("GrabLeft", IE_Released, this, &AVRPawn::GrabLeftReleased);

    InputComponent->BindAction("FirstActionRight", IE_Pressed, this, &AVRPawn::FirstActionRightPressed);
    InputComponent->BindAction("FirstActionRight", IE_Released, this, &AVRPawn::FirstActionRightReleased);
    InputComponent->BindAction("FirstActionLeft", IE_Pressed, this, &AVRPawn::FirstActionLeftPressed);
    InputComponent->BindAction("FirstActionLeft", IE_Released, this, &AVRPawn::FirstActionLeftReleased);

    InputComponent->BindAction("SecondActionRight", IE_Pressed, this, &AVRPawn::SecondActionRightPressed);
    InputComponent->BindAction("SecondActionRight", IE_Released, this, &AVRPawn::SecondActionRightReleased);
    InputComponent->BindAction("SecondActionLeft", IE_Pressed, this, &AVRPawn::SecondActionLeftPressed);
    InputComponent->BindAction("SecondActionLeft", IE_Released, this, &AVRPawn::SecondActionLeftReleased);

    //InputComponent->BindAxis("MoveForward");
    //InputComponent->BindAxis("MoveRight");
    //InputComponent->BindAxis("MoveUp");

    InputComponent->BindAxis("ControllerForward");
    InputComponent->BindAxis("ControllerRight");
    InputComponent->BindAxis("ControllerUp");

    InputComponent->BindAxis("ControllerRoll");
    InputComponent->BindAxis("ControllerPitch");
    InputComponent->BindAxis("ControllerYaw");
}

void AVRPawn::OnBeginOverlapControllerRight(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult) {
    FeedbackContactoRight();
    if (bBuscarArmaRight) {
        if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr) && (OtherActor != GetOwner())) { //no es necesario el ultimo, solo para este caso particular en el que no quiero que el propio conejo active esta funconalidad
            //en realidad deberia haber un if afuera de cada uno de estos, verifcando que este en alguna tarea de casa o robot, si esttoy en no task de alguno de ellos no deberia estar conviriendo
            //ni comprobando
            AArma * const Arma = Cast<AArma>(OtherActor);
            if (Arma && !Arma->IsPendingKill()) {
                UStaticMeshComponent * const MeshArma = Cast<UStaticMeshComponent>(OtherComp);//para la casa no necesito verificar que haya tocado su staticmesh
                //no se si sera con el static mesh o con el componente colision para el arma
                if (MeshArma) {
                    //OverlapedRightBloque = Bloque;
                    if (GEngine)//no hacer esta verificación provocaba error al iniciar el editor
                        GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT("Overlap Arma"));
                    OverlapedRightArmas.AddUnique(Arma);
                }
            }
        }
    }
}

void AVRPawn::OnBeginOverlapControllerLeft(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult) {
    FeedbackContactoLeft();
    if (bBuscarArmaLeft&& !bGrabLeftArma) {
        AArma * const Arma = Cast<AArma>(OtherActor);
        if (Arma && !Arma->IsPendingKill()) {
            UStaticMeshComponent * const MeshArma = Cast<UStaticMeshComponent>(OtherComp);
            if(MeshArma){
                if(GEngine)//no hacer esta verificación provocaba error al iniciar el editor
                    GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT("End Overlap Arma"));
                //OverlapedRightBloque = nullptr;
                OverlapedLeftArmas.AddUnique(Arma);
            }
        }
    }
}

void AVRPawn::OnEndOverlapControllerRight(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex) {
    if (bBuscarArmaRight && !bGrabRightArma) {
        AArma * const Arma = Cast<AArma>(OtherActor);
        if (Arma && !Arma->IsPendingKill()) {
            UStaticMeshComponent * const MeshArma = Cast<UStaticMeshComponent>(OtherComp);
            if(MeshArma){
                if(GEngine)//no hacer esta verificación provocaba error al iniciar el editor
                    GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT("End Overlap Arma"));
                //OverlapedRightBloque = nullptr;
                OverlapedRightArmas.Remove(Arma);
            }
        }
    }
}

void AVRPawn::OnEndOverlapControllerLeft(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex) {
    if (bBuscarArmaLeft && !bGrabLeftArma) {
        AArma * const Arma = Cast<AArma>(OtherActor);
        if (Arma && !Arma->IsPendingKill()) {
            UStaticMeshComponent * const MeshArma = Cast<UStaticMeshComponent>(OtherComp);
            if(MeshArma){
                if(GEngine)//no hacer esta verificación provocaba error al iniciar el editor
                    GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT("End Overlap Arma"));
                //OverlapedRightBloque = nullptr;
                OverlapedLeftArmas.Remove(Arma);
            }
        }
    }
}

void AVRPawn::GrabRightPressed() {
    if (bGrabRightArma) {//podria ser solo si ArmaRight existe
        bBuscarArmaRight = true;
        bGrabRightArma = false;
        ArmaRight->Soltar();
        ArmaRight = nullptr;
    }
    else {
        if (OverlapedRightArma) {//encapsularlo en la funcion anterior para manter un orden
            bBuscarArmaRight = false;
            bGrabRightArma = true;
            //UE_LOG(LogClass, Log, TEXT("Calculando offset"));
            //PuntoReferenciaRight->SetWorldLocation(OverlapedRightBloque->GetActorLocation());
            //PuntoReferenciaRight->SetWorldRotation(OverlapedRightBloque->GetActorRotation());
            UE_LOG(LogClass, Log, TEXT("Actualizando punto referencia"));
            OverlapedRightArma->Sujetar(MotionControllerRight);
            ArmaRight = OverlapedRightArma;
            /*ArmaRight->AttachToComponent(MotionControllerRight, FAttachmentTransformRules::KeepRelativeTransform);
            ArmaRight->SetActorRelativeLocation(FVector(0.0, 0.0, -2.0f));
            ArmaRight->SetActorRelativeRotation(FRotator(270.0f, 0.0f, 0.0f));*/
            //aqui debo hacerle un attachment al motion controller y ocultar el mesh del control
            //el arma en la fucnion sujetar, debo pasarle mi componente motion controller, y la propia arma despues de quitarse las fisicas debe hacerse el attachment
            if (bGrabLeftArma && OverlapedRightArma == OverlapedLeftArma) {//debo tener cuidado de no sujetar la misma arma que mi mano izquierda
                //en este caso no deberia sujetar
            }
        }
    }
}

void AVRPawn::GrabRightTick() {
    if (bBuscarArmaRight) {
        float Distancia = 0.0f;
        float DistanciaMin = std::numeric_limits<float>::max();
        OverlapedRightArma = nullptr;
        for (int i = 0; i < OverlapedRightArmas.Num(); i++) {
            Distancia = (OverlapedRightArmas[i]->GetActorLocation() - ColisionControllerRight->GetComponentLocation()).Size();
            if (Distancia < DistanciaMin) {
                OverlapedRightArma = OverlapedRightArmas[i];
                DistanciaMin = Distancia;
                //UE_LOG(LogClass, Log, TEXT("Nuevo cercano right"));
            }
        }
    }
}

void AVRPawn::GrabRightReleased() {
    //El codigo siguiente era por si sujetar era mientras manetgo presionado el grip, pero es muy cansado para el usuario, el soltar debe ser en el presed
    /*if (OverlapedRightArma) {
        bBuscarArmaRight = true;
        bGrabRightArma = false;
        OverlapedRightArma->Soltar();
    }*/
}

void AVRPawn::GrabLeftPressed() {
    if (bGrabLeftArma) {//podria ser solo si ArmaRight existe
        bBuscarArmaLeft = true;
        bGrabLeftArma = false;
        ArmaLeft->Soltar();
        ArmaLeft = nullptr;
    }
    else {
        if (OverlapedLeftArma) {//encapsularlo en la funcion anterior para manter un orden
            bBuscarArmaLeft = false;
            bGrabLeftArma = true;
            //UE_LOG(LogClass, Log, TEXT("Calculando offset"));
            //PuntoReferenciaRight->SetWorldLocation(OverlapedRightBloque->GetActorLocation());
            //PuntoReferenciaRight->SetWorldRotation(OverlapedRightBloque->GetActorRotation());
            UE_LOG(LogClass, Log, TEXT("Actualizando punto referencia"));
            OverlapedLeftArma->Sujetar(MotionControllerLeft);
            ArmaLeft = OverlapedLeftArma;
            /*ArmaRight->AttachToComponent(MotionControllerRight, FAttachmentTransformRules::KeepRelativeTransform);
            ArmaRight->SetActorRelativeLocation(FVector(0.0, 0.0, -2.0f));
            ArmaRight->SetActorRelativeRotation(FRotator(270.0f, 0.0f, 0.0f));*/
            //aqui debo hacerle un attachment al motion controller y ocultar el mesh del control
            //el arma en la fucnion sujetar, debo pasarle mi componente motion controller, y la propia arma despues de quitarse las fisicas debe hacerse el attachment
            if (bGrabRightArma && OverlapedLeftArma == OverlapedRightArma) {//debo tener cuidado de no sujetar la misma arma que mi mano izquierda
                //en este caso no deberia sujetar
            }
        }
    }
}

void AVRPawn::GrabLeftTick() {
    if (bBuscarArmaLeft) {
        float Distancia = 0.0f;
        float DistanciaMin = std::numeric_limits<float>::max();
        OverlapedLeftArma = nullptr;
        for (int i = 0; i < OverlapedLeftArmas.Num(); i++) {
            Distancia = (OverlapedLeftArmas[i]->GetActorLocation() - ColisionControllerLeft->GetComponentLocation()).Size();
            if (Distancia < DistanciaMin) {
                OverlapedLeftArma = OverlapedLeftArmas[i];
                DistanciaMin = Distancia;
                //UE_LOG(LogClass, Log, TEXT("Nuevo cercano right"));
            }
        }
    }
}

void AVRPawn::GrabLeftReleased() {
}

void AVRPawn::FirstActionRightPressed() {
    if (ArmaRight) {
        ArmaRight->AccionPrincipal();
    }
}

void AVRPawn::FirstActionRightReleased() {
}

void AVRPawn::FirstActionLeftPressed() {
    if (ArmaLeft) {
        ArmaLeft->AccionPrincipal();
    }
}

void AVRPawn::FirstActionLeftReleased() {
}

void AVRPawn::SecondActionRightPressed() {
    if (ArmaRight) {
        ArmaRight->AccionSecundaria();
    }
}

void AVRPawn::SecondActionRightReleased() {
}

void AVRPawn::SecondActionLeftPressed() {
    if (ArmaLeft) {
        ArmaLeft->AccionSecundaria();
    }
}

void AVRPawn::SecondActionLeftReleased() {
}

void AVRPawn::FeedbackContactoRight_Implementation() {
}

void AVRPawn::FeedbackContactoLeft_Implementation() {
}

