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

    ColisionHead = CreateDefaultSubobject<USphereComponent>(TEXT("ColisionHead"));
    ColisionHead->SetupAttachment(VRCamera);
    ColisionHead->SetRelativeLocation(FVector::ZeroVector);
    ColisionHead->InitSphereRadius(20.0f);

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

    ViveControllerRight = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ViveControllerRight"));
    ViveControllerRight->SetupAttachment(MotionControllerRight);
    ViveControllerRight->SetRelativeRotation(FRotator(0.0f, 90.0f, 90.0f));


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

    Velocidad = 200.0f;

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

}

// Called to bind functionality to input
void AVRPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AVRPawn::OnBeginOverlapControllerRight(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
}

void AVRPawn::OnBeginOverlapControllerLeft(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
}

void AVRPawn::OnEndOverlapControllerRight(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
}

void AVRPawn::OnEndOverlapControllerLeft(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
}

