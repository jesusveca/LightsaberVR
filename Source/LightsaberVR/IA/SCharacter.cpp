// Fill out your copyright notice in the Description page of Project Settings.

#include "SCharacter.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "LightsaberVR.h"
#include "./Components/SHealthComponent.h"
#include "Public/UObject/ConstructorHelpers.h"
#include "TimerManager.h"
#include "Weapon.h"
#include "Net/UnrealNetwork.h"

// Sets default values
ASCharacter::ASCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComp->bUsePawnControlRotation = true;
	SpringArmComp->SetupAttachment(RootComponent);

	//habilitar soporte para crouch
	GetMovementComponent()->GetNavAgentPropertiesRef().bCanCrouch = true;

	GetCapsuleComponent()->SetCollisionResponseToChannel(COLLISION_WEAPON, ECR_Ignore);
	HealthComp = CreateDefaultSubobject<USHealthComponent>(TEXT("HealthComp"));
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComp->SetupAttachment(SpringArmComp);
	// CameraComp->bUsePawnControlRotation = true;

	ZoomedFOV = 65.0f;
	ZoomInterpSpeed = 20;

	WeaponAttachSocketName = "WeaponSocket";

    PuntoDisparo = CreateDefaultSubobject<USceneComponent>(TEXT("PuntoDisparo"));
    PuntoDisparo->SetupAttachment(RootComponent);
    PuntoDisparo->SetRelativeLocation(FVector(0.0f, 0.0f, 80.0f));

    static ConstructorHelpers::FClassFinder<AProyectilEnemigo> ProyectilClass(TEXT("Class'/Script/LightsaberVR.ProyectilEnemigo'"));
    if (ProyectilClass.Succeeded()) {
        TipoProyectil = ProyectilClass.Class;
    }
}

// Called when the game starts or when spawned
void ASCharacter::BeginPlay()
{
	Super::BeginPlay();
	DefaultFOV = CameraComp->FieldOfView;
	HealthComp->OnHealthChanged.AddDynamic(this, &ASCharacter::OnHealthChanged);

	// Spawn a default weapon
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	CurrentWeapon = GetWorld()->SpawnActor<AWeapon>(StarterWeaponClass, FVector::ZeroVector, FRotator::ZeroRotator, SpawnParams);
	if (CurrentWeapon)
	{
		CurrentWeapon->SetOwner(this);
		CurrentWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, WeaponAttachSocketName);
	}
}

// luis
void ASCharacter::MoveForward(float value)
{
	AddMovementInput(GetActorForwardVector() * value);
}

// luis
void ASCharacter::MoveRight(float value)
{
	AddMovementInput(GetActorRightVector() * value);
}

void ASCharacter::BeginCrouch()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Crouch!"));

	Crouch();
}

void ASCharacter::EndCrouch()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("End Crouch!"));
	UnCrouch();
}

void ASCharacter::BeginZoom()
{
	bWantsToZoom = true;
}

void ASCharacter::EndZoom()
{
	bWantsToZoom = false;
}

void ASCharacter::StartFire()
{
	if (CurrentWeapon)
	{
		CurrentWeapon->StartFire();
	}
}

void ASCharacter::StopFire()
{
	if (CurrentWeapon)
	{
		CurrentWeapon->StopFire();
	}
}

void ASCharacter::Disparar() {
    UWorld * const World = GetWorld();
    if (World) {
        FActorSpawnParameters SpawnParams;
        SpawnParams.Owner = this;
        SpawnParams.Instigator = Instigator;
        SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
        FVector SpawnLocation = PuntoDisparo->GetComponentLocation();
        FRotator SpawnRotator = PuntoDisparo->GetComponentRotation();
        AProyectilEnemigo * Proyectil = World->SpawnActor<AProyectilEnemigo>(TipoProyectil, SpawnLocation, SpawnRotator, SpawnParams);//recibe el punto pero del mundo, no el local, lo podemos ver como vector
        //ABolaChocolate * BolaChocolate = World->SpawnActor<ABolaChocolate>(TipoBolaChocolate, GetActorLocation() + PuntoLanzamiento, GetActorRotation(), SpawnParams);//recibe el punto pero del mundo, no el local, lo podemos ver como vector
        //ABolaChocolate * BolaChocolate = World->SpawnActor<ABolaChocolate>(TipoBolaChocolate, GetActorLocation() + GetTransform().InverseTransformPostion(PuntoLanzamiento), GetActorRotation(), SpawnParams);//recibe el punto pero del mundo, no el local, lo podemos ver como vector
        if(Proyectil)
            Proyectil->Lanzar();
    }
}

void ASCharacter::IniciarDisparos() {
    GetWorldTimerManager().SetTimer(TimerDisparo, this, &ASCharacter::Disparar, 0.25f, true);//esto hace que llame a advance timer cada segundo que pasa
}

void ASCharacter::DetenerDisparos() {
    GetWorldTimerManager().ClearTimer(TimerDisparo);
}

void ASCharacter::OnHealthChanged(USHealthComponent *OwningHealthComp, float Health, float HealthDelta, const class UDamageType *DamageType,
	class AController *InstigatedBy, AActor *DamageCauser)
{
	if (Health <= 0.0f && !bDied)
	{
		// Die!
		bDied = true;

		GetMovementComponent()->StopMovementImmediately();
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

		// DetachFromControllerPendingDestroy();

		// SetLifeSpan(10.0f);
	}
}

// Called every frame
void ASCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	float TargetFOV = bWantsToZoom ? ZoomedFOV : DefaultFOV;
	float NewFOV = FMath::FInterpTo(CameraComp->FieldOfView, TargetFOV, DeltaTime, ZoomInterpSpeed);

	CameraComp->SetFieldOfView(NewFOV);
}

//luis input
// Called to bind functionality to input
void ASCharacter::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ASCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASCharacter::MoveRight);
	PlayerInputComponent->BindAxis("LookUp", this, &ASCharacter::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("Turn", this, &ASCharacter::AddControllerYawInput);

	PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &ASCharacter::BeginCrouch);
	PlayerInputComponent->BindAction("Crouch", IE_Released, this, &ASCharacter::EndCrouch);

	PlayerInputComponent->BindAction("Zoom", IE_Pressed, this, &ASCharacter::BeginZoom);
	PlayerInputComponent->BindAction("Zoom", IE_Released, this, &ASCharacter::EndZoom);

	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ASCharacter::StartFire);
	PlayerInputComponent->BindAction("Fire", IE_Released, this, &ASCharacter::StopFire);
}

FVector ASCharacter::GetPawnViewLocation() const
{
	//retorno la locacion de la camara si existe
	if (CameraComp)
	{
		return CameraComp->GetComponentLocation();
	}
	return Super::GetPawnViewLocation();
}