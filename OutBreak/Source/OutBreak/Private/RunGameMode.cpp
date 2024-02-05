// Fill out your copyright notice in the Description page of Project Settings.


#include "RunGameMode.h"

#include "HealthComponent.h"
#include "Hero.h"
#include "Tile.h"
#include "Kismet/GameplayStatics.h"
#include "Components/ArrowComponent.h"


void ARunGameMode::OnPlayerDeath()
{
	UWorld* World = GetWorld();
	FTimerHandle TimerHandle;
	Hero->Kill();
}

void ARunGameMode::BeginPlay()
{
	Super::BeginPlay();

	Hero = Cast<AHero>(UGameplayStatics::GetPlayerPawn(this,0));

	if(Hero == nullptr)
	{
		UE_LOG(LogTemp,Warning,TEXT("RunCharacter is null"));
		return;
	}
	Hero->GetHealthComponent()->OnDeath.AddDynamic(this, &ARunGameMode::OnPlayerDeath);
	
	for (int i = 0; i < NumberOfStartingTiles; ++i)
	{
		SpawnNextTile(LastTile);
	}
}

void ARunGameMode::DestroyExitedTile(ATile* ExitedTile)
{

	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, [ExitedTile]()
	{
		ExitedTile->Destroy();
	}, 30.0f, false);
}

void ARunGameMode::SpawnNextTile(ATile* PreviousTile)
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.Instigator = GetInstigator();

	if(LastTile == nullptr)
	{
		UE_LOG(LogTemp,Warning,TEXT("LastTile is null"));
		LastTile = GetWorld()->SpawnActor<ATile>(TileClass, FVector::ZeroVector, FRotator::ZeroRotator, SpawnParams);
		LastTile->OnExitTile.AddDynamic(this, &ARunGameMode::SpawnNextTile);
		LastTile->OnExitTile.AddDynamic(this, &ARunGameMode::DestroyExitedTile);
		return;
	}
	FVector SpawnLocation = LastTile->GetAttachPoint()->GetComponentLocation();
	FRotator SpawnRotation = LastTile->GetAttachPoint()->GetComponentRotation();

	LastTile = GetWorld()->SpawnActor<ATile>(TileClass, SpawnLocation, SpawnRotation, SpawnParams);
	LastTile->OnExitTile.AddDynamic(this, &ARunGameMode::SpawnNextTile);
	LastTile->OnExitTile.AddDynamic(this, &ARunGameMode::DestroyExitedTile);
}
