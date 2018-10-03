// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "EngineGlobals.h"
#include "Runtime/Engine/Classes/Engine/Engine.h"
#include "./Components/SHealthComponent.h"

#include "SCharacter.generated.h"


class AWeapon;
UCLASS()
class LIGHTSABERVR_API ASCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//luis
	void MoveForward(float value);
	void MoveRight(float value);
	void BeginCrouch();
	void EndCrouch();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		UCameraComponent *CameraComp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
		USpringArmComponent *SpringArmComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		USHealthComponent *HealthComp;

	bool bWantsToZoom;

	UPROPERTY(EditDefaultsOnly, Category = "Player")
		float ZoomedFOV;

	UPROPERTY(EditDefaultsOnly, Category = "Player", meta = (ClampMin = 0.1, ClampMax = 100))
		float ZoomInterpSpeed;

	/* Default FOV set during begin play */
	float DefaultFOV;

	void BeginZoom();

	void EndZoom();

	// UPROPERTY(Replicated)
	// UPROPERTY(BlueprintReadOnly, Category = "Player")
	AWeapon* CurrentWeapon;

	UPROPERTY(EditDefaultsOnly, Category = "Player")
		TSubclassOf<AWeapon> StarterWeaponClass;

	UPROPERTY(VisibleDefaultsOnly, Category = "Player")
		FName WeaponAttachSocketName;


	UFUNCTION()
		void OnHealthChanged(USHealthComponent *OwningHealthComp, float Health, float HealthDelta, const class UDamageType *DamageType, class AController *InstigatedBy, AActor *DamageCauser);

	/* Pawn died previously */
	UPROPERTY(BlueprintReadOnly, Category = "Player")
		bool bDied;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent *PlayerInputComponent) override;

	//sobreescribiendo para ajustar el disparo desde la camara
	virtual FVector GetPawnViewLocation() const override;

	UFUNCTION(BlueprintCallable, Category = "Player")
		void StartFire();

	UFUNCTION(BlueprintCallable, Category = "Player")
		void StopFire();
};
