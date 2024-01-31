// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SkeletalMeshComponent.h"
#include "WeaponComponent.generated.h"

UENUM()
enum EWeaponType : uint8
{
	WT_None UMETA(DisplayName = "None"),
	WT_Pistol UMETA(DisplayName = "Pistol"),
	WT_Rifle UMETA(DisplayName = "Rifle"),
	WT_Shotgun UMETA(DisplayName = "Shotgun"),
};


class AHero;
/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnFire);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnUnequip);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEquip);


UCLASS(Blueprintable, BlueprintType, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class OUTBREAK_API UWeaponComponent : public USkeletalMeshComponent
{
	GENERATED_BODY()

protected:

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	FName WeaponName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	TEnumAsByte<EWeaponType> WeaponType = WT_None;

	/** Projectile class to spawn */
	UPROPERTY(EditDefaultsOnly, Category=Projectile)
	TSubclassOf<class AOutBreakProjectile> ProjectileClass;

	/** Sound to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	USoundBase* FireSound;
	
	/** AnimMontage to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	UAnimMontage* FireAnimation;

	/** Gun muzzle's offset from the characters location */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	FVector MuzzleOffset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	FName AttachToSocketName;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	float FireRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	float Range;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	float Damage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	int32 AmmoCapacity;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon")
	int32 Ammo;

	int32 ShotgunAmmoPerFire = 5;

	FTimerHandle FireTimer;
	
public:

	UWeaponComponent();

	/** Attaches the actor to a FirstPersonCharacter */
	UFUNCTION(BlueprintCallable, Category="Weapon")
	void AttachWeapon(AHero* TargetCharacter);

	UFUNCTION(BlueprintCallable, Category="Weapon")
	void DetachWeapon();

	UFUNCTION(BlueprintCallable, Category="Weapon")
	void Fire();

	UFUNCTION(BlueprintCallable, Category="Weapon")
	void StopFire();

	UFUNCTION(BlueprintCallable, Category="Weapon")
	FName GetWeaponName() const { return WeaponName;}

	UFUNCTION(BlueprintCallable, Category="Weapon")
	EWeaponType GetWeaponType() const { return WeaponType; }

	UFUNCTION(BlueprintCallable, Category="Weapon")
	int32 GetAmmo() const { return Ammo; }

	UFUNCTION(BlueprintCallable, Category="Weapon")
	int32 GetAmmoCapacity() const { return AmmoCapacity; }

	UFUNCTION(BlueprintCallable, Category="Weapon")
	void AddAmmo(int32 Amount);

	UFUNCTION(BlueprintCallable, Category="Weapon")
	virtual void SpawnProjectile();

	UPROPERTY(BlueprintAssignable, Category = "Weapon")
	FOnFire OnFire;

	UPROPERTY(BlueprintAssignable, Category = "Weapon")
	FOnUnequip OnUnequip;

	UPROPERTY(BlueprintAssignable, Category = "Weapon")
	FOnEquip OnEquip;
private:
	AHero* Hero;
};
