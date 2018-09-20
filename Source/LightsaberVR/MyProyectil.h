// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Proyectil.h"
#include "MyProyectil.generated.h"

/**
 * 
 */
UCLASS()
class LIGHTSABERVR_API AMyProyectil : public AProyectil
{
	GENERATED_BODY()
	
	
public:	
	// Sets default values for this actor's properties
	AMyProyectil();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

    UFUNCTION(BlueprintCallable, Category = "LightSaberVR")
    virtual void Lanzar();
	
	
};