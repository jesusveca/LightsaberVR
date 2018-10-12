// Fill out your copyright notice in the Description page of Project Settings.

#include "Pistola.h"
#include "Public/UObject/ConstructorHelpers.h"
#include "Engine/StaticMesh.h"
#include "Engine/Engine.h"
#include "Materials/Material.h"

#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/InputSettings.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "MotionControllerComponent.h"
#include "MyProyectil.h"

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
    MeshPistola->SetRelativeLocation(FVector(90.0f, 0.0f, 0.0f));

    PuntoDisparo = CreateDefaultSubobject<USceneComponent>(TEXT("MuzzleLocation"));
    PuntoDisparo->SetupAttachment(MeshPistola);
    PuntoDisparo->SetRelativeLocation(FVector(0.0f, 0.0f, -10.0f));
    // PuntoDisparo->SetRelativeRotation(FRotator(0.0f,270.0f, 270.0f));

    // Default offset from the character location for projectiles to spawn
    GunOffset = FVector(0.0f, 0.0f, 10.0f);

    ColisionPistola = CreateDefaultSubobject<UCapsuleComponent>(TEXT("ColisionPistola"));
    ColisionPistola->SetupAttachment(RootComponent);
    ColisionPistola->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
    ColisionPistola->InitCapsuleSize(1.5f, 51.0f);
    ColisionPistola->OnComponentBeginOverlap.AddDynamic(this, &APistola::OnBeginOverlapPistola);
    ColisionPistola->OnComponentEndOverlap.AddDynamic(this, &APistola::OnEndOverlapPistola);

    ColisionPistola->Activate(false);
}

void APistola::BeginPlay()
{
    Super::BeginPlay();
}

void APistola::OnBeginOverlapPistola(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
    if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr) && (OtherActor != GetOwner()))
    {
        //if (GEngine) //no hacer esta verificaci�n provocaba error al iniciar el editor
            //GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT("oVERLAPsIPISTLA"));

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
    /*if (GEngine) //no hacer esta verificaci�n provocaba error al iniciar el editor
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

    // try and fire a projectile
    if (ProjectileClass != NULL)
    {
		if (GEngine) //no hacer esta verificaci�n provocaba error al iniciar el editor
			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("HIT"));
		FHitResult Hit;
        UWorld *const World = GetWorld();
		AActor *MyOwner = GetOwner();
		if (MyOwner)
			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("TENGO DUEÑO"));
		else 
			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("NO TENGO DUEÑO"));
        if (World != NULL)
        {
            if (bUsingMotionControllers)
            {

                if (GEngine) //no hacer esta verificaci�n provocaba error al iniciar el editor
                    GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT("bUsingMotionControllers"));
                UE_LOG(LogClass, Log, TEXT("PRIMER PASO"));
                const FRotator SpawnRotation = VR_MuzzleLocation->GetComponentRotation();
                UE_LOG(LogClass, Log, TEXT("SEGUNDO PASO"));
                const FVector SpawnLocation = VR_MuzzleLocation->GetComponentLocation();
                UE_LOG(LogClass, Log, TEXT("TERCERO PASO"));
                World->SpawnActor<AProyectil>(ProjectileClass, SpawnLocation, SpawnRotation);
                // World->SpawnActor<AProyectil>(ProjectileClass, SpawnLocation, SpawnRotation);
                // World->SpawnActor<AProyectilEnemigo>(ProjectileClass, SpawnLocation, SpawnRotation);
                UE_LOG(LogClass, Log, TEXT("TERMINE"));
            }
            else
            {


                if (GEngine) //no hacer esta verificaci�n provocaba error al iniciar el editor
                    GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT("no bUsingMotionControllers"));
                UE_LOG(LogClass, Log, TEXT("N PRIMER PASO"));
                const FRotator SpawnRotation = PuntoDisparo->GetComponentRotation();//GetActorRotation(); //MeshPistola->GetOwner()->GetActorRotation();//GetActorRotation(); //GetOwner()->GetActorRotation();//GetControlRotation();
                UE_LOG(LogClass, Log, TEXT("N SEGUNDO PASO "));

                // MuzzleOffset is in camera space, so transform it to world space before offsetting from the character location to find the final muzzle position
                const FVector SpawnLocation = ((PuntoDisparo != nullptr) ? PuntoDisparo->GetComponentLocation() : GetActorLocation());// + SpawnRotation.RotateVector(GunOffset);
                UE_LOG(LogClass, Log, TEXT("N TERCER PASO"));
                //Set Spawn Collision Handling Override
                FActorSpawnParameters ActorSpawnParams;
                UE_LOG(LogClass, Log, TEXT("N CUARTO PASO"));
                ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;//AdjustIfPossibleButDontSpawnIfColliding;
                ActorSpawnParams.Instigator=Instigator;
                ActorSpawnParams.Owner=this;
                UE_LOG(LogClass, Log, TEXT("N QUINTO PASO"));
                // spawn the projectile at the muzzle
                // AProyectil *const Proyectil = Cast<AProyectil>(ProjectileClass);
                // Proyectil->Lanzar();
                // World->SpawnActor<AProyectil>(ProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);
                

                //IF GETACERTADOS()==5
                //PROYECTIL CARGADO
                //ELSE
                //OTRO
                
                AProyectil * bala = World->SpawnActor<AProyectil>(ProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);
                if(bala)
                bala->Lanzar();
                // World->SpawnActor<AProyectilEnemigo>(ProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);
                UE_LOG(LogClass, Log, TEXT("FIN"));
            }
        }
    }*/

    UWorld * const World = GetWorld();
    if (World) {
        FActorSpawnParameters SpawnParams;
        SpawnParams.Owner = this;
        SpawnParams.Instigator = Instigator;
        SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
        FVector SpawnLocation = PuntoDisparo->GetComponentLocation();
        FRotator SpawnRotator = PuntoDisparo->GetComponentRotation();
        AProyectil* Proyectil = World->SpawnActor<AProyectil>(ProjectileClass, SpawnLocation, SpawnRotator, SpawnParams);//recibe el punto pero del mundo, no el local, lo podemos ver como vector
        if(Proyectil)
            Proyectil->Lanzar();
    }
    // try and play the sound if specified
    if (FireSound != NULL)
    {
        UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
    }
}

void APistola::AccionSecundaria()
{
    if (GEngine) //no hacer esta verificaci�n provocaba error al iniciar el editor
        GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT("Accion Secundaria"));
}

void APistola::Sujetar(UMotionControllerComponent *Controller)
{
    if (GEngine) //no hacer esta verificaci�n provocaba error al iniciar el editor
        GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT("Sugetando pistola"));
    MeshPistola->SetSimulatePhysics(false);
    AttachToComponent(Controller, FAttachmentTransformRules::KeepRelativeTransform);

    SetActorRelativeLocation(FVector(0.0, 0.0, -2.0f));
    // SetActorRelativeRotation(FRotator(270.0f,0.0f, 0.0f));
    SetActorRelativeRotation(FRotator(210.0f,0.0f, 0.0f));
}

void APistola::Soltar()
{
    MeshPistola->SetSimulatePhysics(true);
}
