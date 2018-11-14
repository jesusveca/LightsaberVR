// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Puerta.generated.h"

UCLASS()
class LIGHTSABERVR_API APuerta : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APuerta();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "LightsaberVR")
    UStaticMeshComponent * MeshPuerta;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "LightsaberVR")
    UBoxComponent * ColisionPuerta;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LightsaberVR")
    bool bActivado;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LightsaberVR")
    bool bAnimando;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LightsaberVR")
    float VelocidadActivacion;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LightsaberVR")
    float EscalaActual;
	
	/*UFUNCTION(BlueprintCallable, Client, Unreliable, Category = "LightsaberVR")
    void ClientAbrir();

	UFUNCTION(BlueprintCallable, Client, Unreliable, Category = "LightsaberVR")
    void ClientCerrar();*/
	
};
