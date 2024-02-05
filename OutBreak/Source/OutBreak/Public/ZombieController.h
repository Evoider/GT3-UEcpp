// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionComponent.h"
#include "ZombieController.generated.h"

class AZombie;
class AHero;
class UAISenseConfig_Sight;
/**
 * 
 */
UCLASS()
class OUTBREAK_API AZombieController : public AAIController
{
	GENERATED_BODY()
public:
	AZombieController();
	void OnPossess(APawn* InPawn) override;
	void OnUnPossess() override;
	void Attack();
	void Chase();
	UFUNCTION()
	void OnPerceptionUpdated(const TArray<AActor*>& Actors);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
	UAIPerceptionComponent* PerceptionComp;

	UAISenseConfig_Sight* SightConfig;

	AZombie* possessedUnit;
	AHero* Hero;

	FTimerHandle ChaseTimerHandle;
	FTimerHandle AttackTimerHandle;
protected:
	bool CanSenseHero(AActor* Actor , FActorPerceptionBlueprintInfo& Info);



};
