// Fill out your copyright notice in the Description page of Project Settings.

#include "STrackerBot.h"

#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "AI/Navigation/NavigationSystem.h"
#include "GameFramework/Character.h"
#include "AI/Navigation/NavigationPath.h"
#include "DrawDebugHelpers.h"
#include "SHealthComponent.h"
#include "SCharacter.h"
#include "Components/SphereComponent.h"
#include "Sound/SoundCue.h"
#include "Engine/Engine.h"

static int32 DebugTrackerBotDrawing = 1;
FAutoConsoleVariableRef CVARDebugTrackerBotDrawing(
	TEXT("COOP.DebugTrackerBot"),
	DebugTrackerBotDrawing,
	TEXT("Draw Debug Lines for TrackerBot"),
	ECVF_Cheat);

// Sets default values
ASTrackerBot::ASTrackerBot()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetCanEverAffectNavigation(false);
	MeshComp->SetSimulatePhysics(true);
	RootComponent = MeshComp;

	HealthComp = CreateDefaultSubobject<USHealthComponent>(TEXT("HealthComp"));
	HealthComp->OnHealthChanged.AddDynamic(this, &ASTrackerBot::HandleTakeDamage);

	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	SphereComp->SetSphereRadius(200);
	SphereComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	SphereComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	SphereComp->SetupAttachment(RootComponent);

	bUseVelocityChange = false;
	bStartedSelfDestruction=false;
	MovementForce = 1000;
	RequiredDistanceToTarget = 50;

	ExplosionDamage = 60;
	ExplosionRadius = 350;

	SelfDamageInterval = 0.25f;
}

FVector ASTrackerBot::GetNextPathPoint()
{
	AActor *BestTarget = nullptr;
	float NearestTargetDistance = FLT_MAX;

	for (FConstPawnIterator It = GetWorld()->GetPawnIterator(); It; ++It)
	{
		APawn *TestPawn = It->Get();
		// if (TestPawn == nullptr || USHealthComponent::IsFriendly(TestPawn, this))
		// {
		// 	continue;
		// }

		// USHealthComponent *TestPawnHealthComp = Cast<USHealthComponent>(TestPawn->GetComponentByClass(USHealthComponent::StaticClass()));
		// if (TestPawnHealthComp && TestPawnHealthComp->GetHealth() > 0.0f)
		// {
		// 	float Distance = (TestPawn->GetActorLocation() - GetActorLocation()).Size();

		// 	if (Distance < NearestTargetDistance)
		// 	{
		// 		BestTarget = TestPawn;
		// 		NearestTargetDistance = Distance;
		// 	}
		// }
	}

	// if (BestTarget)
	// {

	ACharacter *PlayerPawn = UGameplayStatics::GetPlayerCharacter(this, 0);
	UNavigationPath *NavPath = UNavigationSystem::FindPathToActorSynchronously(this, GetActorLocation(), PlayerPawn);

	// 	GetWorldTimerManager().ClearTimer(TimerHandle_RefreshPath);
	// 	GetWorldTimerManager().SetTimer(TimerHandle_RefreshPath, this, &ASTrackerBot::RefreshPath, 5.0f, false);

	if (NavPath && NavPath->PathPoints.Num() > 1)
	{
		if (GEngine) //no hacer esta verificaci�n provocaba error al iniciar el editor
			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT("oVERLAPsIPISTLA"));
		// Return next point in the path
		return NavPath->PathPoints[1];
	}
	// }

	// Failed to find path
	return GetActorLocation();
}

// Called when the game starts or when spawned
void ASTrackerBot::BeginPlay()
{
	Super::BeginPlay();
	// Find initial move-to
	NextPathPoint = GetNextPathPoint();
	// OnActorBeginOverlap.AddDynamic(this, &ASTrackerBot::HandleTakeDamage);
}

void ASTrackerBot::HandleTakeDamage(USHealthComponent *OwningHealthComp, float Health, float HealthDelta, const class UDamageType *DamageType, class AController *InstigatedBy, AActor *DamageCauser)
{
	if (MatInst == nullptr)
	{
		MatInst = MeshComp->CreateAndSetMaterialInstanceDynamicFromMaterial(0, MeshComp->GetMaterial(0));
	}

	if (MatInst)
	{
		MatInst->SetScalarParameterValue("LastTimeDamageTaken", GetWorld()->TimeSeconds);
	}

	// Explode on hitpoints == 0
	if (Health <= 0.0f)
	{
		SelfDestruct();
	}
}

void ASTrackerBot::SelfDestruct()
{
	if (bExploded)
	{
		return;
	}

	bExploded = true;

	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionEffect, GetActorLocation());

	UGameplayStatics::PlaySoundAtLocation(this, ExplodeSound, GetActorLocation());

	// MeshComp->SetVisibility(false, true);
	// MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	TArray<AActor *> IgnoredActors;
	IgnoredActors.Add(this);

	// // Increase damage based on the power level (challenge code)
	// float ActualDamage = ExplosionDamage + (ExplosionDamage * PowerLevel);

	// Apply Damage!
	// UGameplayStatics::ApplyRadialDamage(this, ActualDamage, GetActorLocation(), ExplosionRadius, nullptr, IgnoredActors, this, GetInstigatorController(), true);

	// if (DebugTrackerBotDrawing)
	// {
	DrawDebugSphere(GetWorld(), GetActorLocation(), ExplosionRadius, 12, FColor::Red, false, 2.0f, 0, 1.0f);
	// }
	// SetLifeSpan(2.0f);

	Destroy();
}
void ASTrackerBot::NotifyActorBeginOverlap(AActor *OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	if (GEngine) //no hacer esta verificaci�n provocaba error al iniciar el editor
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("overlap"));

	if (!bStartedSelfDestruction /*&& !bExploded*/)
	{
		if (GEngine) //no hacer esta verificaci�n provocaba error al iniciar el editor
			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT("SELFDESTRUCTION"));
		ASCharacter *PlayerPawn = Cast<ASCharacter>(OtherActor);

		if (PlayerPawn)
		{

			bStartedSelfDestruction = true;
			GetWorldTimerManager().SetTimer(TimerHandle_SelfDamage, this, &ASTrackerBot::DamageSelf, SelfDamageInterval, true, 0.0f);

			UGameplayStatics::SpawnSoundAttached(SelfDestructSound, RootComponent);
		}
	}
}

void ASTrackerBot::DamageSelf()
{
	if (GEngine) //no hacer esta verificaci�n provocaba error al iniciar el editor
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT("autodamage enemy"));
	UGameplayStatics::ApplyDamage(this, 20, GetInstigatorController(), this, nullptr);
}

// Called every frame
void ASTrackerBot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// if (GEngine) //no hacer esta verificaci�n provocaba error al iniciar el editor
	//         GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT("mitick"));
	// if (Role == ROLE_Authority && !bExploded)
	// {
	float DistanceToTarget = (GetActorLocation() - NextPathPoint).Size();

	// if (GEngine) //no hacer esta verificaci�n provocaba error al iniciar el editor
	// {FString TheFloatStr = FString::SanitizeFloat(DistanceToTarget);
	// 	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, DistanceToTarget);
	// }
	// if (GEngine) //no hacer esta verificaci�n provocaba error al iniciar el editor
	// 	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow,TEXT(RequiredDistanceToTarget));
	if (DistanceToTarget <= RequiredDistanceToTarget)
	{

		NextPathPoint = GetNextPathPoint();

		if (DebugTrackerBotDrawing)
		{
			DrawDebugString(GetWorld(), GetActorLocation(), "Target Reached!");
		}
	}
	else
	{

		// Keep moving towards next target
		FVector ForceDirection = NextPathPoint - GetActorLocation();
		ForceDirection.Normalize();

		ForceDirection *= MovementForce;

		MeshComp->AddForce(ForceDirection, NAME_None, bUseVelocityChange);

		if (DebugTrackerBotDrawing)
		{
			DrawDebugDirectionalArrow(GetWorld(), GetActorLocation(), GetActorLocation() + ForceDirection, 32, FColor::Yellow, false, 0.0f, 0, 1.0f);
		}
	}

	if (DebugTrackerBotDrawing)
	{
		DrawDebugSphere(GetWorld(), NextPathPoint, 20, 12, FColor::Yellow, false, 0.0f, 1.0f);
	}
	// }
}

// Called to bind functionality to input
void ASTrackerBot::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ASTrackerBot::RefreshPath()
{
	NextPathPoint = GetNextPathPoint();
}
