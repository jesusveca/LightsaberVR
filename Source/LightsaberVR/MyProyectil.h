// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Proyectil.h"

#include "Kismet/GameplayStatics.h" //para el damage
#include "Components/SphereComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "MyProyectil.generated.h"

/**
 * 
 */
UCLASS()
class LIGHTSABERVR_API AMyProyectil : public AProyectil
{
	GENERATED_BODY()
	
	
/*public:	
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
	
	UFUNCTION()
		void OnBeginOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "LightSaberVR")
		TSubclassOf<UDamageType> DamageType;*/
};
