// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tile.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnExitTile);
UCLASS()
class ENDLESSRUNNERCPP_API ATile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATile();


protected:

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category = "Tile")
	class USceneComponent* Root;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Tile")
	class UArrowComponent* AttachPoint;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Tile")
	class UBoxComponent* ExitTrigger;
	
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp,class AActor* OtherActor,
		class UPrimitiveComponent* OtherComp,int32 OtherBodyIndex,bool bFromSweep,const FHitResult& SweepResult);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintAssignable,Category = "Tile")
	FOnExitTile OnExitTile;
};
