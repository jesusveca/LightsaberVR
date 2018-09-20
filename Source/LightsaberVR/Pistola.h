// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Arma.h"

#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Proyectil.h"
#include "MyProyectil.h" 
#include "ProyectilEnemigo.h"
#include "Pistola.generated.h"

/**
 * 
 */
UCLASS()
class LIGHTSABERVR_API APistola : public AArma
{
	GENERATED_BODY()

  public:
	//luis

	APistola();

  protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "LightsaberVR")
	UCapsuleComponent *ColisionPistola;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LightsaberVR")
	// USkeletalMeshComponent * MeshPistola;
	UStaticMeshComponent *MeshPistola;



	/** Location on gun mesh where projectiles should spawn. */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USceneComponent *PuntoDisparo;

	/** Location on VR gun mesh where projectiles should spawn. */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USceneComponent *VR_MuzzleLocation;

	/** Projectile class to spawn */
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	// TSubclassOf<class AProyectil> ProjectileClass;
	// TSubclassOf<class AAdisparitosProjectile> ProjectileClass;
	// TSubclassOf<class AProyectilEnemigo> ProjectileClass;
	TSubclassOf<class AMyProyectil> ProjectileClass;

	/** Whether to use motion controller location for aiming. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	uint32 bUsingMotionControllers : 1;
	
	/** Gun muzzle's offset from the characters location */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	FVector GunOffset;

  	/** Sound to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	class USoundBase* FireSound;




	UFUNCTION(BlueprintCallable, Category = "LightsaberVR")
	virtual void AccionPrincipal() override;

	UFUNCTION(BlueprintCallable, Category = "LightsaberVR")
	virtual void AccionSecundaria() override;

	UFUNCTION(BlueprintCallable, Category = "LightsaberVR")
	virtual void Sujetar(UMotionControllerComponent *Controller) override;
	UFUNCTION(BlueprintCallable, Category = "LightsaberVR")
	virtual void Soltar() override;

	UFUNCTION()
	void OnBeginOverlapPistola(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);

	UFUNCTION()
	void OnEndOverlapPistola(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex);
};
