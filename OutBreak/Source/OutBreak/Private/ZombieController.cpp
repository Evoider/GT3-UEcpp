// Fill out your copyright notice in the Description page of Project Settings.


#include "ZombieController.h"

#include "AsyncTreeDifferences.h"
#include "Hero.h"
#include "Zombie.h"
#include "Navigation/PathFollowingComponent.h"
#include "Perception/AISenseConfig_Sight.h"


AZombieController::AZombieController()
{
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));

	PerceptionComp = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("PerceptionComponent"));

	SightConfig->PeripheralVisionAngleDegrees = 360.0f;
	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
	SightConfig->SetMaxAge(2.0f);
	PerceptionComp->ConfigureSense(*SightConfig);
	PerceptionComp->SetDominantSense(SightConfig->GetSenseImplementation());
}

void AZombieController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	possessedUnit = Cast<AZombie>(InPawn);

	SightConfig->SightRadius = possessedUnit->GetSightRange();
	SightConfig->LoseSightRadius = (possessedUnit->GetSightRange() + 200.0f);

	PerceptionComp->ConfigureSense(*SightConfig);
	PerceptionComp->SetDominantSense(SightConfig->GetSenseImplementation());

	PerceptionComp->OnPerceptionUpdated.AddDynamic(this, &AZombieController::OnPerceptionUpdated);
	TArray<AActor*> Actors;
	PerceptionComp->GetCurrentlyPerceivedActors(SightConfig->GetSenseImplementation(), Actors);

	GetWorld()->GetTimerManager().SetTimer(ChaseTimerHandle, this, &AZombieController::Chase, 1.f, true);
}

void AZombieController::OnUnPossess()
{
	Super::OnUnPossess();
	GetWorld()->GetTimerManager().ClearTimer(ChaseTimerHandle);
	SightConfig = nullptr;
	PerceptionComponent = nullptr;
	possessedUnit = nullptr;
	Hero = nullptr;
}


void AZombieController::OnPerceptionUpdated(const TArray<AActor*>& Actors)
{
	for (auto Actor : Actors)
	{
		FActorPerceptionBlueprintInfo Info;
		if (CanSenseHero(Actor, Info) && !Hero)
		{
			Hero = Cast<AHero>(Actor);
			if (Hero)
			{
				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "I see you!");
				break;
			}
		}
	}
}

void AZombieController::Attack()
{
	if (possessedUnit)
	{
		possessedUnit->StartAttacking();
	}
}

void AZombieController::Chase()
{
	if (Hero)
	{
		FAIMoveRequest MoveRequest;
		MoveRequest.SetGoalActor(Hero);
		MoveRequest.SetAcceptanceRadius(80.f);
		FPathFollowingRequestResult Result = MoveTo(MoveRequest);
		if (Result.Code == EPathFollowingRequestResult::RequestSuccessful)
		{
			UE_LOG(LogTemp, Warning, TEXT("RequestSuccessful"));
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("RequestFailed"));
		}
		if (possessedUnit)
		{
			float Distance = possessedUnit->GetDistanceTo(Hero);
			UE_LOG(LogTemp, Warning, TEXT("Distance: %f"), Distance);
			if (Distance <= 200.f)
			{
				if (!GetWorld()->GetTimerManager().IsTimerActive(AttackTimerHandle))
				{
					UE_LOG(LogTemp, Warning, TEXT("Attack"));

					GetWorld()->GetTimerManager().SetTimer(AttackTimerHandle, this, &AZombieController::Attack,
					                                       possessedUnit->GetAttackSpeed(), true,0);
				}
			}
			else
			{
				GetWorld()->GetTimerManager().ClearTimer(AttackTimerHandle);
			}
		}
	}
}

bool AZombieController::CanSenseHero(AActor* Actor, FActorPerceptionBlueprintInfo& Info)
{
	PerceptionComp->GetActorsPerception(Actor, Info);
	if (Info.LastSensedStimuli.Num() > 0)
	{
		return true;
	}
	return false;
}
