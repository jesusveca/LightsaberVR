// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Arma.h"
#include "Components/CapsuleComponent.h"
#include "Components/BoxComponent.h"
#include "Escudo.generated.h"

/**
 *
 */
UCLASS()
class LIGHTSABERVR_API AEscudo : public AArma
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AEscudo();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "LightsaberVR")
		UStaticMeshComponent * Escudo;

	//UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "LightsaberVR")
	//UStaticMeshComponent * LaserExtremo;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "LightsaberVR")
		UStaticMeshComponent * EscudoMango;


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "LightsaberVR")
		//UCapsuleComponent * ColisionEscudo;
		UBoxComponent * ColisionEscudo;



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

	UFUNCTION(BlueprintCallable, Category = "LightsaberVR")
		virtual void AccionSecundaria() override;

	UFUNCTION(BlueprintCallable, Category = "LightsaberVR")
		virtual void Sujetar(UMotionControllerComponent * Controller) override;

	UFUNCTION(BlueprintCallable, Category = "LightsaberVR")
		virtual void Soltar() override;

	UFUNCTION()
		void OnBeginOverlapEscudo(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION()
		void OnEndOverlapEscudo(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex);



};
