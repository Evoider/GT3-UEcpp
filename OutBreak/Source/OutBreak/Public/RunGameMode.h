// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "RunGameMode.generated.h"

/**
 * 
 */
UCLASS()
class OUTBREAK_API ARunGameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category = "GameMode")
	class AHero* Hero;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameMode")
	class ATile* LastTile;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "GameMode")
	TSubclassOf<class ATile> TileClass;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "GameMode")
	int32 NumberOfStartingTiles;

	UFUNCTION()
	void OnPlayerDeath();
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable,Category = "GameMode")
	void DestroyExitedTile(ATile* ExitedTile);
	UFUNCTION(BlueprintCallable,Category = "GameMode")
	void SpawnNextTile(ATile* PreviousTile);
};
