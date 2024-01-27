// Fill out your copyright notice in the Description page of Project Settings.


#include "RunGameMode.h"
#include "RunCharacter.h"
#include "Kismet/GameplayStatics.h"


void ARunGameMode::BeginPlay()
{
	Super::BeginPlay();

	RunCharacter = Cast<ARunCharacter>(UGameplayStatics::GetPlayerPawn(this,0));
}

void ARunGameMode::SpawnNextTile()
{
	
}
