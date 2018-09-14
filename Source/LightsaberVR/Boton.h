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

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Transformation")
    UStaticMeshComponent * Boton;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Transformation")
	UMaterial * MaterialNormal;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Transformation")
	UMaterial * MaterialPresionado;
	
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Transformation")
    bool bPressed;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Transformation")
    bool bPressing;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Transformation")
    bool bPosicionNormal;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Transformation")
    bool bPosicionPresionado;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Transformation")
    bool bPosicionContacto;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Transformation")
    bool bPosicionFondo;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Transformation")
    float AlturaNormal;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Transformation")
    float AlturaPresionado;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Transformation")
    float AlturaContacto;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Transformation")
    float AlturaFondo;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Transformation")
    float VelocidadNormal;

    UFUNCTION(BlueprintCallable, Category = "Transformation")
    void SendSignalPressed();

    UFUNCTION(BlueprintCallable, Category = "Transformation")
    void SendSignalReleased();

    UFUNCTION(BlueprintCallable, Category = "Transformation")
    void Presionado();

    UFUNCTION(BlueprintCallable, Category = "Transformation")
    void NoPresionado();
	
	
};
