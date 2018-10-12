// Fill out your copyright notice in the Description page of Project Settings.

#include "MyProyectil.h"
#include "Public/UObject/ConstructorHelpers.h"
#include "Engine/Engine.h"
#include "Engine/StaticMesh.h"
#include "Materials/Material.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/SpringArmComponent.h"


/*#include "VRPawn.h"
#include "./IA/SCharacter.h"
// Sets default values
AMyProyectil::AMyProyectil()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
    Velocidad = 1000.0f;
    Poder = 30.0f;
    bLanzado = false;


	Colision = CreateDefaultSubobject<USphereComponent>(TEXT("Colision"));
	Colision->SetupAttachment(RootComponent);
	Colision->InitSphereRadius(12.5f);
	Colision->SetCollisionProfileName(TEXT("MyProyectil"));
	Colision->OnComponentBeginOverlap.AddDynamic(this, &AMyProyectil::OnBeginOverlap);
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
        GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, TEXT("lanzando"));

        bLanzado=true;
}
void AMyProyectil::OnBeginOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & FHitResult) {
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr) && (OtherActor != GetOwner())) { //no es necesario el ultimo, solo para este caso particular en el que no quiero que el propio conejo active esta funconalidad
		if (GEngine)//no hacer esta verificación provocaba error al iniciar el editor
			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Blue, TEXT("overlap muproyuectil"));
		ASCharacter * const Player = Cast<ASCharacter>(OtherActor);
	
		if (Player && !Player->IsPendingKill()) {
			//USpringArmComponent * const CuerpoPlayer = Cast<USpringArmComponent>(OtherComp);

			//if (CuerpoPlayer) {
				if (GEngine)//no hacer esta verificación provocaba error al iniciar el editor
					GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, TEXT("CUERPO ENCONTRADO"));
				FVector EyeLocation;
				FRotator EyeRotation;
				Player->GetActorEyesViewPoint(EyeLocation, EyeRotation);

				FVector ShotDirection = EyeRotation.Vector();

				// Blocking hit! Process damage
				AActor *HitActor = FHitResult.GetActor();
				UGameplayStatics::ApplyPointDamage(HitActor, 10, ShotDirection, FHitResult, Player->GetInstigatorController(), Player, DamageType);

				//Player->RecibirAtaque(Poder, GetActorLocation());
				Destroy();
			//}
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
		}* /
	}

}*/
