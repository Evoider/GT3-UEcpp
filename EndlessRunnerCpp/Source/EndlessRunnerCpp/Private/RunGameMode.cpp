// Fill out your copyright notice in the Description page of Project Settings.


#include "RunGameMode.h"
#include "RunCharacter.h"
#include "Tile.h"
#include "Kismet/GameplayStatics.h"
#include "Components/ArrowComponent.h"


void ARunGameMode::OnPlayerDeath(ARunCharacter* DeadActor)
{
	UWorld* World = GetWorld();
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, [DeadActor,World]()
	{
		UGameplayStatics::OpenLevel(DeadActor, FName(World->GetName()), false);
	}, 3.0f, false);
}

void ARunGameMode::BeginPlay()
{
	Super::BeginPlay();

	RunCharacter = Cast<ARunCharacter>(UGameplayStatics::GetPlayerPawn(this,0));

	if(RunCharacter == nullptr)
	{
		UE_LOG(LogTemp,Warning,TEXT("RunCharacter is null"));
		return;
	}
	RunCharacter->OnDeath.AddDynamic(this, &ARunGameMode::OnPlayerDeath);
	
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
	}, 5.0f, false);
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
