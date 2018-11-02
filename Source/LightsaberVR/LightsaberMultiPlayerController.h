// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "LightsaberMultiPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class LIGHTSABERVR_API ALightsaberMultiPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	/* Constructor */
	ALightsaberMultiPlayerController(const FObjectInitializer& ObjectInitializer);
 
	FORCEINLINE UClass* GetPlayerPawnClass() { return MyPawnClass; }
 
protected:
	/* Return The Correct Pawn Class Client-Side */
	UFUNCTION(Reliable, Client)
	void DeterminePawnClass();
    virtual void DeterminePawnClass_Implementation();
 
	/* Use BeginPlay to start the functionality */
	virtual void BeginPlay() override;

	/* Set Pawn Class On Server For This Controller */
	UFUNCTION(Reliable, Server, WithValidation)
	virtual void ServerSetPawn(TSubclassOf<APawn> InPawnClass);
    virtual void ServerSetPawn_Implementation(TSubclassOf<APawn> InPawnClass);
	virtual bool ServerSetPawn_Validate(TSubclassOf<APawn> InPawnClass);

    void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;
	/* Actual Pawn class we want to use */
	UPROPERTY(Replicated)
	TSubclassOf<APawn> MyPawnClass;
 
	/* First Pawn Type To Use */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "LightsaberVR")
	TSubclassOf<APawn> PawnToUseA;
 
	/* Second Pawn Type To Use */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "LightsaberVR")
	TSubclassOf<APawn> PawnToUseB;
	
	
	
};
