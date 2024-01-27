// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "RunGameMode.generated.h"

/**
 * 
 */
UCLASS()
class ENDLESSRUNNERCPP_API ARunGameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category = "GameMode")
	class ARunCharacter* RunCharacter;

	
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable,Category = "GameMode")
	void SpawnNextTile();
};
