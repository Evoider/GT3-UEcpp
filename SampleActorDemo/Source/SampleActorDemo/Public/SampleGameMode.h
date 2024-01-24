// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SampleGameMode.generated.h"

/**
 * 
 */
UCLASS()
class SAMPLEACTORDEMO_API ASampleGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ASampleGameMode();

	UFUNCTION(BlueprintCallable, Category = "GameMode")
	void IncreasePoints();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameMode")
	int32 PointsToWin;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameMode")
	int32 CurrentPoints = 0;

protected:
	UFUNCTION(BlueprintImplementableEvent, Category = "GameMode")
	void OnPointsIncreased() ;
	UFUNCTION(BlueprintImplementableEvent, Category = "GameMode")
	void OnWin();
};
