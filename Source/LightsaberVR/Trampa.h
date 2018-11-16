// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Materials/Material.h"
#include "Trampa.generated.h"


UCLASS()
class LIGHTSABERVR_API ATrampa : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATrampa();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "LightsaberVR")
		UStaticMeshComponent * MeshTrampa;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "LightsaberVR")
		USphereComponent * ColisionTrampa;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LightsaberVR")
		bool bActivado;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LightsaberVR")
		bool bAnimando;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LightsaberVR")
		float VelocidadActivacion;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LightsaberVR")
		float EscalaActual;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LightsaberVR")
		float Poder;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "VRPawn")
		UParticleSystemComponent * EfectoImpacto;

	
};
