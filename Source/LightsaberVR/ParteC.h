// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Arma.h"
#include "Components/BoxComponent.h"
#include "ParteC.generated.h"

/**
 * 
 */
UCLASS()
class LIGHTSABERVR_API AParteC : public AArma
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AParteC();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "LightsaberVR")
    UStaticMeshComponent * Part;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "LightsaberVR")
    UBoxComponent * Colision;
	
    UFUNCTION(BlueprintCallable, Category = "LightsaberVR")
    virtual void AccionPrincipal() override;

    UFUNCTION(BlueprintCallable, Category = "LightsaberVR")
    virtual void AccionSecundaria() override;

    UFUNCTION(BlueprintCallable, Category = "LightsaberVR")
    virtual void Sujetar(UMotionControllerComponent * Controller) override;

    UFUNCTION(BlueprintCallable, Category = "LightsaberVR")
    virtual void Soltar() override;
	
	
	
};
