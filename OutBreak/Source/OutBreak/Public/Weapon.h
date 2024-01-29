// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

class AHero;
class UPickup;
class UWeaponComponent;

UCLASS()
class OUTBREAK_API AWeapon : public AActor
{
	GENERATED_BODY()
protected:

	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon")
	UWeaponComponent* WeaponComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon")
	UPickup* Pickup;
public:	
	// Sets default values for this actor's properties
	AWeapon();

protected:
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void PickupWeapon(AHero* Hero);

	UFUNCTION(BlueprintNativeEvent)
	void EquipWeapon();
	
	UFUNCTION(BlueprintNativeEvent)
	void UnequipWeapon();	
};
