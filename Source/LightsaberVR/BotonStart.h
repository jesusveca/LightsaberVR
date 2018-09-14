// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Boton.h"
#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "BotonStart.generated.h"

/**
 * 
 */
UCLASS()
class LIGHTSABERVR_API ABotonStart : public ABoton
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABotonStart();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Transformation")
    UStaticMeshComponent * Borde;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Transformation")
    UCapsuleComponent * ColisionControl;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Transformation")
    float DistanciaColision;
	
    UFUNCTION()
    void OnBeginOverlapBoton(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

    UFUNCTION()
	void OnEndOverlapBoton(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex);
	
	
	
};
