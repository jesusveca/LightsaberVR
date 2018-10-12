// Fill out your copyright notice in the Description page of Project Settings.

#include "Weapon.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"
#include "Components/SkeletalMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "PhysicalMaterials/PhysicalMaterial.h"

#include "LightsaberVR.h"
#include "TimerManager.h"

static int32 DebugWeaponDrawing = 1;
FAutoConsoleVariableRef CVARDebugWeaponDrawing(
	TEXT("COOP.DebugWeapons"),
	DebugWeaponDrawing,
	TEXT("Draw Debug Lines for Weapons"),
	ECVF_Cheat);
// Sets default values
AWeapon::AWeapon()
{
	// // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	// PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MeshComp"));
	RootComponent = MeshComp;
	MuzzleSocketName = "MuzzleSocket";
	TracerTargetName = "Target";

	BaseDamage = 20.0f;
	BulletSpread = 2.0f;
	RateOfFire = 600;

	// Log a debug message
	//UE_LOG(LogClass, Log, TEXT("Primer log %s"));
}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	TimeBetweenShots = 60 / RateOfFire;
}

void AWeapon::Fire()
{
	// Trace the world, from pawn eyes to crosshair location

	// if (Role < ROLE_Authority)
	// {
	// 	ServerFire();
	// }
	 	if (GEngine) //no hacer esta verificaci�n provocaba error al iniciar el editor
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("FIRE"));
	AActor *MyOwner = GetOwner();
	if (MyOwner)
	{
		if (GEngine) //no hacer esta verificaci�n provocaba error al iniciar el editor
			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("FIRE dentro"));
		FVector EyeLocation;
		FRotator EyeRotation;
		MyOwner->GetActorEyesViewPoint(EyeLocation, EyeRotation);

		FVector ShotDirection = EyeRotation.Vector();

		// Bullet Spread
		float HalfRad = FMath::DegreesToRadians(BulletSpread);
		ShotDirection = FMath::VRandCone(ShotDirection, HalfRad, HalfRad);

		FVector TraceEnd = EyeLocation + (ShotDirection * 10000);

		FCollisionQueryParams QueryParams;
		QueryParams.AddIgnoredActor(MyOwner);
		QueryParams.AddIgnoredActor(this);
		QueryParams.bTraceComplex = true;
		QueryParams.bReturnPhysicalMaterial = true;

		// Particle "Target" parameter
		FVector TracerEndPoint = TraceEnd;

		EPhysicalSurface SurfaceType = SurfaceType_Default;
		//COLLISION_WEAPON
		FHitResult Hit;
		if (GetWorld()->LineTraceSingleByChannel(Hit, EyeLocation, TraceEnd, ECC_Visibility, QueryParams))
		{
			if (GEngine) //no hacer esta verificaci�n provocaba error al iniciar el editor
				GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("COLISION dentro"));
			// Blocking hit! Process damage
			AActor *HitActor = Hit.GetActor();

			SurfaceType = UPhysicalMaterial::DetermineSurfaceType(Hit.PhysMaterial.Get());

			float ActualDamage = BaseDamage;
			if (SurfaceType == SURFACE_FLESHVULNERABLE)
			{
				ActualDamage *= 4.0f;
			}

			UGameplayStatics::ApplyPointDamage(HitActor, ActualDamage, ShotDirection, Hit, MyOwner->GetInstigatorController(), MyOwner, DamageType);

			PlayImpactEffects(SurfaceType, Hit.ImpactPoint);

			TracerEndPoint = Hit.ImpactPoint;
		}

		if (DebugWeaponDrawing > 0)
		{
			DrawDebugLine(GetWorld(), EyeLocation, TraceEnd, FColor::White, false, 1.0f, 0, 1.0f);
		}

		PlayFireEffects(TracerEndPoint);

		// if (Role == ROLE_Authority)
		// {
		// 	HitScanTrace.TraceTo = TracerEndPoint;
		// 	HitScanTrace.SurfaceType = SurfaceType;
		// }

		LastFireTime = GetWorld()->TimeSeconds;
	}
}

//luis
// void AWeapon::Fire()
// {
// 	if (GEngine) //no hacer esta verificaci�n provocaba error al iniciar el editor
// 		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("FIRE"));

// 	//Trace the world, from pawn eyes to crosshair location
// 	AActor *MyOwner = GetOwner();
// 	// 	// Log a debug message
// 	// UE_LOG(LogClass, Log, TEXT("Primer log %s"));
// 	if (MyOwner)
// 	{
// 		FVector EyeLocation;
// 		FRotator EyeRotation;

// 		MyOwner->GetActorEyesViewPoint(EyeLocation, EyeRotation);

// 		FVector ShotDirection = EyeRotation.Vector();

// 		// Bullet Spread
// 		float HalfRad = FMath::DegreesToRadians(BulletSpread);
// 		ShotDirection = FMath::VRandCone(ShotDirection, HalfRad, HalfRad);

// 		FVector TraceEnd = EyeLocation + (ShotDirection * 10000);

// 		FCollisionQueryParams QueryParams;
// 		QueryParams.AddIgnoredActor(MyOwner);
// 		QueryParams.AddIgnoredActor(this);
// 		QueryParams.bTraceComplex = true;

// 		// Particle "Target" parameter
// 		FVector TracerEndPoint = TraceEnd;

// 		EPhysicalSurface SurfaceType = SurfaceType_Default;
// 		// Log a debug message
// 		// FString PickupDebugString = GetName();
// 		// UE_LOG(LogClass, Log, TEXT("You have collected %s"), *PickupDebugString);

// 		FHitResult Hit;
// 		if (GetWorld()->LineTraceSingleByChannel(Hit, EyeLocation, TraceEnd, ECC_Visibility, QueryParams))
// 		{
// 			// Log a debug message
// 			// FString PickupDebugString = GetName();
// 			// UE_LOG(LogClass, Log, TEXT("entreeeee"), *PickupDebugString);

// 			//Blocking hit! Process Damage
// 			AActor *HitActor = Hit.GetActor();

// 			SurfaceType = UPhysicalMaterial::DetermineSurfaceType(Hit.PhysMaterial.Get());

// 			float ActualDamage = BaseDamage;
// 			if (SurfaceType == SURFACE_FLESHVULNERABLE)
// 			{
// 				ActualDamage *= 4.0f;
// 			}

// 			UGameplayStatics::ApplyPointDamage(HitActor, ActualDamage, ShotDirection, Hit, MyOwner->GetInstigatorController(), this, DamageType);

// 			PlayImpactEffects(SurfaceType, Hit.ImpactPoint);

// 			TracerEndPoint = Hit.ImpactPoint;
// 		}
// 		//Aca deberia estar el efector del disparo pero por ahora usare una linea recta amarilla
// 		UWorld *world = GetWorld();
// 		if (world)
// 			DrawDebugLine(world, EyeLocation, TraceEnd, FColor::Yellow, false, 2.0f, 0, 2.0f);
// 	}
// }
//luis

void AWeapon::PlayImpactEffects(EPhysicalSurface SurfaceType, FVector ImpactPoint)
{
	UParticleSystem *SelectedEffect = nullptr;
	switch (SurfaceType)
	{
	case SURFACE_FLESHDEFAULT:
	case SURFACE_FLESHVULNERABLE:
		SelectedEffect = FleshImpactEffect;
		break;
	default:
		SelectedEffect = DefaultImpactEffect;
		break;
	}

	if (SelectedEffect)
	{
		FVector MuzzleLocation = MeshComp->GetSocketLocation(MuzzleSocketName);

		FVector ShotDirection = ImpactPoint - MuzzleLocation;
		ShotDirection.Normalize();

		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), SelectedEffect, ImpactPoint, ShotDirection.Rotation());
	}
}

void AWeapon::StartFire()
{
	if (GEngine) //no hacer esta verificaci�n provocaba error al iniciar el editor
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("startfire"));

	float FirstDelay = FMath::Max(LastFireTime + TimeBetweenShots - GetWorld()->TimeSeconds, 0.0f);

	GetWorldTimerManager().SetTimer(TimerHandle_TimeBetweenShots, this, &AWeapon::Fire, TimeBetweenShots, true, FirstDelay);
}

void AWeapon::StopFire()
{
	GetWorldTimerManager().ClearTimer(TimerHandle_TimeBetweenShots);
}

void AWeapon::PlayFireEffects(FVector TraceEnd)
{
	if (MuzzleEffect)
	{
		UGameplayStatics::SpawnEmitterAttached(MuzzleEffect, MeshComp, MuzzleSocketName);
	}

	if (TracerEffect)
	{
		FVector MuzzleLocation = MeshComp->GetSocketLocation(MuzzleSocketName);

		UParticleSystemComponent *TracerComp = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), TracerEffect, MuzzleLocation);
		if (TracerComp)
		{
			TracerComp->SetVectorParameter(TracerTargetName, TraceEnd);
		}
	}

	APawn *MyOwner = Cast<APawn>(GetOwner());
	if (MyOwner)
	{
		APlayerController *PC = Cast<APlayerController>(MyOwner->GetController());
		if (PC)
		{
			PC->ClientPlayCameraShake(FireCamShake);
		}
	}
}

// // Called every frame
// void AWeapon::Tick(float DeltaTime)
// {
// 	Super::Tick(DeltaTime);
// }
