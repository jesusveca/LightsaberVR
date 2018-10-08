// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "HeadMountedDisplay.h"
#include "WidgetComponent.h"
#include "WidgetInteractionComponent.h"
#include "MotionControllerComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "Camera/CameraComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Arma.h"
#include "VRPawn.generated.h"

UCLASS()
class LIGHTSABERVR_API AVRPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AVRPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    //Root component
    UPROPERTY(VisibleAnywhere, Category = "VRPawn")
    USceneComponent * DefaultSceneRoot;
    //Camara del HMD
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "VRPawn")
    UCameraComponent * VRCamera;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "VRPawn")
    UCapsuleComponent * ColisionHead;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "VRPawn")
    class UMotionControllerComponent * MotionControllerLeft;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "VRPawn")
    class UMotionControllerComponent * MotionControllerRight;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "VRPawn")
    UStaticMeshComponent * ViveControllerLeft;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "VRPawn")
    UStaticMeshComponent * ViveControllerRight;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "VRPawn")
	UCapsuleComponent * ColisionControllerLeft;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "VRPawn")
	UCapsuleComponent * ColisionControllerRight;
	
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "VRPawn")
    UWidgetInteractionComponent * Interaction;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "VRPawn")
    UParticleSystemComponent * Laser;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "VRPawn")
    UParticleSystemComponent * EfectoImpacto;
	
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "VRPawn")
    UFloatingPawnMovement * Movimiento;
	
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VRPawn")
    float Velocidad;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VRPawn")
    float VelocidadDash;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VRPawn")
    float DistanciaDash;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VRPawn")
    bool bGrabRightArma;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VRPawn")
    bool bGrabLeftArma;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VRPawn")
	bool bBuscarArmaLeft;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VRPawn")
	bool bBuscarArmaRight;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VRPawn")
    AArma * ArmaLeft;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VRPawn")
    AArma * ArmaRight;

	//parte sobrepuesta mas cercana al centro del control derecho
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VRPawn")
	AArma * OverlapedRightArma;

	//parte sobrepuesta mas cercana al centro del control derecho
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VRPawn")
	AArma * OverlapedLeftArma;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "VRPawn")
    TArray<AArma *> OverlapedLeftArmas;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "VRPawn")
    TArray<AArma *> OverlapedRightArmas;

    UFUNCTION()
    void OnBeginOverlapControllerRight(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

    UFUNCTION()
    void OnBeginOverlapControllerLeft(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

    UFUNCTION()
	void OnEndOverlapControllerRight(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex);

    UFUNCTION()
	void OnEndOverlapControllerLeft(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex);

    UFUNCTION(BlueprintCallable, Category = "VRPawn")
    void GrabRightPressed();

    UFUNCTION(BlueprintCallable, Category = "VRPawn")
    void GrabRightTick();

    UFUNCTION(BlueprintCallable, Category = "VRPawn")
    void GrabRightReleased();

    UFUNCTION(BlueprintCallable, Category = "VRPawn")
    void GrabLeftPressed();

    UFUNCTION(BlueprintCallable, Category = "VRPawn")
    void GrabLeftTick();

    UFUNCTION(BlueprintCallable, Category = "VRPawn")
    void GrabLeftReleased();

    UFUNCTION(BlueprintCallable, Category = "VRPawn")
    void FirstActionRightPressed();

    UFUNCTION(BlueprintCallable, Category = "VRPawn")
    void FirstActionRightReleased();

    UFUNCTION(BlueprintCallable, Category = "VRPawn")
    void FirstActionLeftPressed();

    UFUNCTION(BlueprintCallable, Category = "VRPawn")
    void FirstActionLeftReleased();

    UFUNCTION(BlueprintCallable, Category = "VRPawn")
    void SecondActionRightPressed();

    UFUNCTION(BlueprintCallable, Category = "VRPawn")
    void SecondActionRightReleased();

    UFUNCTION(BlueprintCallable, Category = "VRPawn")
    void SecondActionLeftPressed();

    UFUNCTION(BlueprintCallable, Category = "VRPawn")
    void SecondActionLeftReleased();
};
