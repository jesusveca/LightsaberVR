// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Materials/Material.h"
#include "Boton.generated.h"

UCLASS()
class LIGHTSABERVR_API ABoton : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABoton();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "LightsaberVR")
    UStaticMeshComponent * Boton;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "LightsaberVR")
	UMaterial * MaterialNormal;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "LightsaberVR")
	UMaterial * MaterialPresionado;
	
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LightsaberVR")
    bool bPressed;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LightsaberVR")
    bool bPressing;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LightsaberVR")
    bool bPosicionNormal;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LightsaberVR")
    bool bPosicionPresionado;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LightsaberVR")
    bool bPosicionContacto;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LightsaberVR")
    bool bPosicionFondo;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LightsaberVR")
    float AlturaNormal;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LightsaberVR")
    float AlturaPresionado;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LightsaberVR")
    float AlturaContacto;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LightsaberVR")
    float AlturaFondo;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LightsaberVR")
    float VelocidadNormal;

    UFUNCTION(BlueprintCallable, Category = "LightsaberVR")
    virtual void SendSignalPressed();

    UFUNCTION(BlueprintCallable, Category = "LightsaberVR")
    virtual void SendSignalReleased();

    UFUNCTION(BlueprintCallable, Category = "LightsaberVR")
    void Presionado();

    UFUNCTION(BlueprintCallable, Category = "LightsaberVR")
    void NoPresionado();
	
	
};
