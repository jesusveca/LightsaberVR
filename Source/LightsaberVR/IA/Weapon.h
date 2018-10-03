// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Kismet/GameplayStatics.h" //para el damage
#include "Particles/ParticleSystem.h"
#include "Components/SkeletalMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
#include "LightsaberVR.h"
#include "Weapon.generated.h"

// Contains information of a single hitscan weapon linetrace
USTRUCT()
struct FHitScanTrace
{
	GENERATED_BODY()

public:
	UPROPERTY()
		TEnumAsByte<EPhysicalSurface> SurfaceType;

	UPROPERTY()
		FVector_NetQuantize TraceTo;
};

UCLASS()
class LIGHTSABERVR_API AWeapon : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//luis
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, category = "Components")
		USkeletalMeshComponent *MeshComp;

	void PlayFireEffects(FVector TraceEnd);

	void PlayImpactEffects(EPhysicalSurface SurfaceType, FVector ImpactPoint);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
		TSubclassOf<UDamageType> DamageType;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
		FName MuzzleSocketName;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
		FName TracerTargetName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
		UParticleSystem* MuzzleEffect;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
		UParticleSystem* DefaultImpactEffect;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
		UParticleSystem* FleshImpactEffect;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
		UParticleSystem* TracerEffect;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
		TSubclassOf<UCameraShake> FireCamShake;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
		float BaseDamage;
	// UFUNCTION(BlueprintCallable, category = "Weapon")
	// void Fire();

	FTimerHandle TimerHandle_TimeBetweenShots;

	float LastFireTime;

	/* RPM - Bullets per minute fired by weapon */
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
		float RateOfFire;

	/* Bullet Spread in Degrees */
	UPROPERTY(EditDefaultsOnly, Category = "Weapon", meta = (ClampMin = 0.0f))
		float BulletSpread;

	// Derived from RateOfFire
	float TimeBetweenShots;

	/* Bullet Spread in Degrees */

	// UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	// TSubclassOf<UDamageType> DamageType;

public:
	// Called every frame
	// virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Player")
		void StartFire();

	UFUNCTION(BlueprintCallable, Category = "Player")
		void StopFire();

	UFUNCTION(BlueprintCallable, Category = "Player")
		void Fire();
};
