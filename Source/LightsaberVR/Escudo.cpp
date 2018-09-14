// Fill out your copyright notice in the Description page of Project Settings.

#include "Escudo.h"
#include "Public/UObject/ConstructorHelpers.h"
#include "Engine/StaticMesh.h"
#include "Materials/Material.h"
#include "ProyectilEnemigo.h"
#include "Components/CapsuleComponent.h"


AEscudo::AEscudo() {
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	EscudoMango = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("EscudoMango"));
	RootComponent = EscudoMango;
	

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MangoAsset(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	static ConstructorHelpers::FObjectFinder<UMaterial> MangoMaterial(TEXT("Material'/Game/LightsaberVR/Materials/HandleSaberMaterial.HandleSaberMaterial'"));
	

	EscudoMango->SetWorldScale3D(FVector(0.1f, 0.1f, 0.1f));
	if (MangoAsset.Succeeded()) {
		EscudoMango->SetStaticMesh(MangoAsset.Object);
		if (MangoMaterial.Succeeded()) {
			EscudoMango->SetMaterial(0, MangoMaterial.Object);
		}
	}
	EscudoMango->SetCollisionProfileName(TEXT("Arma"));
	EscudoMango->SetSimulatePhysics(true);

	Escudo = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Escudo"));
	Escudo->SetupAttachment(EscudoMango);

	

	//static ConstructorHelpers::FObjectFinder<UStaticMesh> EscudoAsset(TEXT("StaticMesh'/Game/LightsaberVR/Meshes/Lightsaber/EscudoLaser.EscudoLaser'"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> EscudoAsset(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));

	//static ConstructorHelpers::FObjectFinder<UStaticMesh> LaserExtremoAsset(TEXT("StaticMesh'/Game/LightsaberVR/Meshes/Lightsaber/SableLaserExtremo.SableLaserExtremo'"));
	static ConstructorHelpers::FObjectFinder<UMaterial> EscudoMaterial(TEXT("Material'/Game/LightsaberVR/Materials/HandleSaberMaterial.HandleSaberMaterial'"));

	Escudo->SetWorldScale3D(FVector(0.7f, 0.7f, 1.0f));
	Escudo->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	if (EscudoAsset.Succeeded()) {
		Escudo->SetStaticMesh(EscudoAsset.Object);
		if (EscudoMaterial.Succeeded()) {
			Escudo->SetMaterial(0, EscudoMaterial.Object);
		}
	}
	/*
	LaserExtremo = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LaserExtremo"));
	LaserExtremo->SetupAttachment(Escudo);

	LaserExtremo->SetWorldScale3D(FVector(0.7f, 0.7f, 1.0f));
	LaserExtremo->SetRelativeLocation(FVector(0.0f, 0.0f, 100.0f));
	*/

	/*
	if (LaserExtremoAsset.Succeeded()) {
		LaserExtremo->SetStaticMesh(LaserExtremoAsset.Object);
		if (LaserMaterial.Succeeded()) {
			LaserExtremo->SetMaterial(0, LaserMaterial.Object);
		}
	}
	*/
	ColisionEscudo = CreateDefaultSubobject<UBoxComponent>(TEXT("ColisionEscudo"));
	//ColisionEscudo = CreateDefaultSubobject<UCapsuleComponent>(TEXT("ColisionEscudo"));
	ColisionEscudo->SetupAttachment(RootComponent);
	ColisionEscudo->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	//ColisionEscudo->InitCapsuleSize(600.0f, 600.0f);
	ColisionEscudo->SetBoxExtent(FVector(10.0f, 10.0f, 10.0f));
	//ColisionEscudo->InitBoxExtent(FVector(10.0f, 10.0f, 10.0f));
	ColisionEscudo->OnComponentBeginOverlap.AddDynamic(this, &AEscudo::OnBeginOverlapEscudo);
	ColisionEscudo->OnComponentEndOverlap.AddDynamic(this, &AEscudo::OnEndOverlapEscudo);

	VelocidadActivacion = 3.0f;//escala 1 por segundo
	bAnimando = false;
	//bActivado = true;

	bActivado = false;
	Escudo->SetVisibility(false);

	//Escudo->SetRelativeScale3D(FVector(0.1f, 5.1f, 5.1f));  // girar la mano y mango
	Escudo->SetRelativeScale3D(FVector(0.1f, 5.1f, 5.1f));

}


void AEscudo::BeginPlay() {
	Super::BeginPlay();
}

void AEscudo::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	if (bAnimando) {
		if (bActivado) {//he activado, y esto animando, osea sale la espada hasta escala 1
			FVector Escala = Escudo->GetRelativeTransform().GetScale3D();
			Escala += FVector(0.0f,  0.0f, VelocidadActivacion*DeltaTime);
			if (Escala.Z >= 4.0f) {
				Escala.Z = 4.0f;
				bAnimando = false;
			}

			Escudo->SetRelativeScale3D(Escala);
		}
		else {//he activado, y esto animando, osea sale la espada hasta escala 1
			FVector Escala = Escudo->GetRelativeTransform().GetScale3D();
			Escala += FVector(-0.0f, 0.0f, -VelocidadActivacion * DeltaTime);
			if (Escala.Z <= 0.0f) {
				Escala.Z = 0.0f;
				bAnimando = false;
				Escudo->SetVisibility(false);
			}
			Escudo->SetRelativeScale3D(Escala);
		}
	}
}

void AEscudo::AccionPrincipal() {
	if (bActivado) {
		bActivado = false;
		bAnimando = true;
	}
	else {
		bActivado = true;
		bAnimando = true;
		Escudo->SetVisibility(true);
		//LaserExtremo->SetVisibility(true);
		//debo iniciar animacion
	}
}

void AEscudo::AccionSecundaria() {
}

void AEscudo::Sujetar(UMotionControllerComponent * Controller) {
	EscudoMango->SetSimulatePhysics(false);
	AttachToComponent(Controller, FAttachmentTransformRules::KeepRelativeTransform);
	SetActorRelativeLocation(FVector(0.0, 0.0, -2.0f));
	SetActorRelativeRotation(FRotator(270.0f, 0.0f, 0.0f));
}

void AEscudo::Soltar() {
	EscudoMango->SetSimulatePhysics(true);
}


void AEscudo::OnBeginOverlapEscudo(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult) {
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr) && (OtherActor != GetOwner())) { //no es necesario el ultimo, solo para este caso particular en el que no quiero que el propio conejo active esta funconalidad
		AProyectilEnemigo * const Proyectil = Cast<AProyectilEnemigo>(OtherActor);
		if (Proyectil && !Proyectil->IsPendingKill()) {
			USphereComponent * const ColisionProyectil = Cast<USphereComponent>(OtherComp);//para la casa no necesito verificar que haya tocado su staticmesh
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

void AEscudo::OnEndOverlapEscudo(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex) {
}
