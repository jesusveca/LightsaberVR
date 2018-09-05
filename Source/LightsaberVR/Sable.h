// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Arma.h"
#include "Components/CapsuleComponent.h"
#include "Sable.generated.h"

/**
 * 
 */
UCLASS()
class LIGHTSABERVR_API ASable : public AArma
{
	GENERATED_BODY()
	
	
public:	
	// Sets default values for this actor's properties
	ASable();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "LightsaberVR")
    UStaticMeshComponent * Laser;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "LightsaberVR")
    UStaticMeshComponent * LaserExtremo;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "LightsaberVR")
    UStaticMeshComponent * SableMango;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "LightsaberVR")
    UCapsuleComponent * ColisionLaser;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LightsaberVR")
    bool bActivado;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LightsaberVR")
    bool bAnimando;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LightsaberVR")
    float VelocidadActivacion;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LightsaberVR")
    float EscalaActual;

    UFUNCTION(BlueprintCallable, Category = "LightsaberVR")
    virtual void AccionPrincipal() override;
	
};
