// Fill out your copyright notice in the Description page of Project Settings.


#include "SampleGameMode.h"

ASampleGameMode::ASampleGameMode()
{
	PointsToWin = 10;
}

void ASampleGameMode::IncreasePoints()
{
	CurrentPoints ++;
	OnPointsIncreased();
	if (CurrentPoints >= PointsToWin)
	{
		UE_LOG(LogTemp, Warning, TEXT("You win!"));
		OnWin();
	}
}
