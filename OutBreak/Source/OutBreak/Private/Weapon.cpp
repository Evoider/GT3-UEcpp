// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"

#include "PickupComponent.h"
#include "WeaponComponent.h"

// Sets default values
AWeapon::AWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	
	WeaponComponent = CreateDefaultSubobject<UWeaponComponent>(TEXT("WeaponComponent"));
	WeaponComponent->SetRelativeLocation(FVector(0.f, 0.f, 50.f));
	
	
	PickupComponent = CreateDefaultSubobject<UPickupComponent>(TEXT("Pickup"));
	PickupComponent->SetupAttachment(WeaponComponent);
	
	
}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();

	PickupComponent->OnPickUp.AddDynamic(this, &AWeapon::PickupWeapon);
	WeaponComponent->OnEquip.AddDynamic(this, &AWeapon::EquipWeapon);
	WeaponComponent->OnUnequip.AddDynamic(this, &AWeapon::UnequipWeapon);
}

void AWeapon::PickupWeapon(AHero* Hero)
{
	WeaponComponent->AttachWeapon(Hero);
}

void AWeapon::EquipWeapon_Implementation()
{
}


void AWeapon::UnequipWeapon_Implementation()
{
	Destroy();
}




