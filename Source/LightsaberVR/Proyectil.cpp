// Fill out your copyright notice in the Description page of Project Settings.

#include "Proyectil.h"
#include "Public/UObject/ConstructorHelpers.h"
#include "Engine/Engine.h"
#include "Engine/StaticMesh.h"
#include "Materials/Material.h"
#include "Kismet/GameplayStatics.h"
#include "VRPawn.h"
// Sets default values
AProyectil::AProyectil()
{

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));
	static ConstructorHelpers::FObjectFinder<UMaterial> MeshMaterial(TEXT("Material'/Game/LightsaberVR/Materials/RedSaberMaterial.RedSaberMaterial'"));

	MeshProyectil = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshProyectil"));
	RootComponent = MeshProyectil;
	MeshProyectil->SetWorldScale3D(FVector(0.25f, 0.25f, 0.25f));
	if (MeshAsset.Succeeded())
	{
		MeshProyectil->SetStaticMesh(MeshAsset.Object);
		if (MeshMaterial.Succeeded())
		{
			MeshProyectil->SetMaterial(0, MeshMaterial.Object);
		}
	}
	//MeshProyectil->SetCollisionProfileName(TEXT("Custom"));
	//MeshProyectil->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	//MeshProyectil->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);

	Colision = CreateDefaultSubobject<USphereComponent>(TEXT("Colision"));
	Colision->SetupAttachment(RootComponent);
	Colision->InitSphereRadius(12.5f);
	Colision->SetCollisionProfileName(TEXT("ProyectilEnemigo"));
	Colision->OnComponentBeginOverlap.AddDynamic(this, &AProyectil::OnBeginOverlap);

	// EfectoImpacto = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("EfectoImpacto"));
	// EfectoImpacto->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AProyectil::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AProyectil::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AProyectil::Lanzar()
{
	bLanzado = true;
	if (GEngine) //no hacer esta verificaci�n provocaba error al iniciar el editor
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("Lanzandome"));

	SetActorLocation(GetActorLocation() + GetActorForwardVector() * Velocidad);
}

void AProyectil::OnBeginOverlap(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr) && (OtherActor != GetOwner()))
	{				 //no es necesario el ultimo, solo para este caso particular en el que no quiero que el propio conejo active esta funconalidad
		if (GEngine) //no hacer esta verificaci�n provocaba error al iniciar el editor
			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT("My Overlap"));
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
