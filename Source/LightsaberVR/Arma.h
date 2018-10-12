// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MotionControllerComponent.h"
#include "Arma.generated.h"

UCLASS()
class LIGHTSABERVR_API AArma : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AArma();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called when the game starts or when spawned
    UFUNCTION(BlueprintCallable, Category = "LightsaberVR")
	virtual void AccionPrincipal();

	// Called when the game starts or when spawned
    UFUNCTION(BlueprintCallable, Category = "LightsaberVR")
	virtual void AccionSecundaria();

    UFUNCTION(BlueprintCallable, Category = "LightsaberVR")
	virtual void Sujetar(UMotionControllerComponent * Controller);

    UFUNCTION(BlueprintCallable, Category = "LightsaberVR")
	virtual void Soltar();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LightsaberVR")
    UMotionControllerComponent * Holder;
	
};
