// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Arma.h"

#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Pistola.generated.h"

/**
 * 
 */
UCLASS()
class LIGHTSABERVR_API APistola : public AArma
{
	GENERATED_BODY()

  public:
	//luis

	APistola();

  protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "LightsaberVR")
	UCapsuleComponent *ColisionPistola;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "LightsaberVR")
	// USkeletalMeshComponent * MeshPistola;
	UStaticMeshComponent *MeshPistola;

	UFUNCTION(BlueprintCallable, Category = "LightsaberVR")
	virtual void AccionPrincipal() override;

	UFUNCTION(BlueprintCallable, Category = "LightsaberVR")
	virtual void AccionSecundaria() override;

	UFUNCTION(BlueprintCallable, Category = "LightsaberVR")
	virtual void Sujetar();
	UFUNCTION(BlueprintCallable, Category = "LightsaberVR")
	virtual void Soltar() override;

	UFUNCTION()
	void OnBeginOverlapPistola(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);

	UFUNCTION()
	void OnEndOverlapPistola(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex);
};
