// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Hero.generated.h"

class UWeaponComponent;
class USkeletalMeshComponent;
class UCameraComponent;

UCLASS()
class OUTBREAK_API AHero : public ACharacter
{
	GENERATED_BODY()


	
protected:
	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
    USkeletalMeshComponent* MeshFP;

	/** First person camera */
	UPROPERTY(VisibleDefaultsOnly, Category = Camera)
	UCameraComponent* CameraFP;

	UPROPERTY(VisibleDefaultsOnly, Category = Weapon)
	UWeaponComponent* WeaponComponent;
	
	/** Bool for AnimBP to switch to another animation set */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Weapon)
	bool bHasWeapon;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	AHero();
	

	UFUNCTION(BlueprintCallable, Category = Weapon)
	void AddWeapon(UWeaponComponent* NewWeaponComponent);

	UFUNCTION(BlueprintCallable, Category = Weapon)
	void RemoveWeapon();

	UFUNCTION(BlueprintCallable, Category = Weapon)
	bool GetHasWeapon();

	UFUNCTION(BlueprintCallable, Category = Weapon)
	void Fire();

	USkeletalMeshComponent* GetMeshFP() const { return MeshFP; }
	UCameraComponent* GetCameraFP() const { return CameraFP; }
};
