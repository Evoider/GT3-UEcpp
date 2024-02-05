// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Hero.h"
#include "GameFramework/Actor.h"
#include "Tile.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnExitTile,ATile*,ExitedTile);
UCLASS()
class OUTBREAK_API ATile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATile();


protected:

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category = "Tile")
	USceneComponent* Root;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Tile")
	class UArrowComponent* AttachPoint;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Tile")
	class UBoxComponent* ExitTrigger;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Tile")
	UBoxComponent* ObstacleSpawnArea;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Tile")
	UBoxComponent* CoinSpawnArea;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Obstacle")
	TArray<TSubclassOf<class AObstacle>> Obstacles;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
	TArray<TSubclassOf<class AZombie>> Zombies;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
	int32 MaxNumberOfEnemy = 5;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pickup")
	TArray<TSubclassOf<class AWeapon>> Pickups;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
	int32 MaxNumberOfPickups = 5;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp,class AActor* OtherActor,
		class UPrimitiveComponent* OtherComp,int32 OtherBodyIndex,bool bFromSweep,const FHitResult& SweepResult);

private:
	UFUNCTION()
	void TrySpawnObstacle();

	UFUNCTION()
	void TrySpawnPickup();
	
	UFUNCTION(BlueprintCallable,Category = "Obstacle")
	void SpawnObstacle();

	UFUNCTION()
	void SpawnPickup();

	UFUNCTION()
	void SpawnZombie();
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable,Category = "Tile")
	UArrowComponent* GetAttachPoint();

	UPROPERTY(BlueprintAssignable,Category = "Tile")
	FOnExitTile OnExitTile;
};
