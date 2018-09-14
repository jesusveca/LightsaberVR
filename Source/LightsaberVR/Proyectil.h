// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

// #include "Components/SkeletalMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Proyectil.generated.h"

UCLASS()
class LIGHTSABERVR_API AProyectil : public AActor
{
	GENERATED_BODY()

  public:
	// Sets default values for this actor's properties
	AProyectil();

  protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

  public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "LightSaberVR")
	bool bLanzado;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "LightSaberVR")
	float Velocidad;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "LightSaberVR")
	float Poder;

	UFUNCTION(BlueprintCallable, Category = "LightSaberVR")
	virtual void Lanzar();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "LightSaberVR")
	USphereComponent *Colision;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "LightSaberVR")
	UStaticMeshComponent *MeshProyectil;
	// UPROPERTY(VisibleAnywhere, BlueprintReadOnly, category = "LightSaberVR")
	// USkeletalMeshComponent *MeshComp;

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);
};
