// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponComponent.h"

#include "Hero.h"
#include "Projectile.h"

void UWeaponComponent::BeginPlay()
{
	Super::BeginPlay();
	Ammo = AmmoCapacity;
}

UWeaponComponent::UWeaponComponent()
{
	// Default offset from the character location for projectiles to spawn
	MuzzleOffset = FVector(150.0f, 0.0f, 10.0f);
	AttachToSocketName = "GripPoint";

	SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SetCollisionProfileName("NoCollision");
	SetGenerateOverlapEvents(false);
	SetCanEverAffectNavigation(false);
	CanCharacterStepUpOn = ECB_No;

	WeaponName = "Weapon";
	AmmoCapacity = 30;
	FireRate = 10;
}

void UWeaponComponent::AttachWeapon(AHero* TargetCharacter)
{
	Hero = TargetCharacter;
	if(!Hero) return;
	if(!Hero->GetMeshFP()) 
	{
		UE_LOG(LogTemp, Warning, TEXT("MeshFP does not exist"));
		return;
	}
	if(!Hero->GetMeshFP()->DoesSocketExist(AttachToSocketName))
	{
		UE_LOG(LogTemp, Warning, TEXT("GripPoint socket does not exist"));
		return;
	}
	if(Hero->GetHasWeapon()) DetachWeapon();

	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::KeepWorld, false);
	AttachToComponent(Hero->GetMeshFP(), AttachmentRules, AttachToSocketName);
	SetCastShadow(false);

	Hero->AddWeapon(this);
	OnEquip.Broadcast();
	
}

void UWeaponComponent::DetachWeapon()
{
	if(!Hero) return;

	UWeaponComponent* WeaponComponent = Hero->GetWeaponComponent();
	WeaponComponent->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
	Hero->RemoveWeapon();
	WeaponComponent->OnUnequip.Broadcast();
}

void UWeaponComponent::Fire()
{
	UE_LOG(LogTemp, Warning, TEXT("Fire"));
	FireTimer = FTimerHandle();

	switch (WeaponType)
	{
	case WT_None:
		break;
	case WT_Pistol:
		SpawnProjectile();
		break;
	case WT_Rifle:
		GetWorld()->GetTimerManager().SetTimer(FireTimer, this, &UWeaponComponent::SpawnProjectile, 1/FireRate, true,0);
		break;
	case WT_Shotgun:
		for (int i = 0; i < ShotgunAmmoPerFire; i++)
		{
			SpawnProjectile();
		}
		break;
	}
	
	
}

void UWeaponComponent::StopFire()
{
	GetWorld()->GetTimerManager().ClearTimer(FireTimer);
	UE_LOG(LogTemp, Warning, TEXT("StopFire"));
}

void UWeaponComponent::AddAmmo(int32 Amount)
{
	Ammo += Amount;
	if(Ammo > AmmoCapacity) Ammo = AmmoCapacity;
}

void UWeaponComponent::SpawnProjectile()
{
	if(Ammo > 0) Ammo--;
	else return;
	
	AProjectile* Projectile = nullptr;

	if (ProjectileClass != nullptr)
	{
		UWorld* const World = GetWorld();
		if (World != nullptr)
		{
			OnFire.Broadcast();

			APlayerController* PlayerController = Cast<APlayerController>(Hero->GetController());
			const FRotator SpawnRotation = PlayerController->PlayerCameraManager->GetCameraRotation();
			const FVector SpawnLocation = GetOwner()->GetActorLocation() + SpawnRotation.RotateVector(MuzzleOffset);

			//Set Spawn Collision Handling Override
			FActorSpawnParameters ActorSpawnParams;
			ActorSpawnParams.SpawnCollisionHandlingOverride =
				ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

			// Spawn the projectile at the muzzle
			Projectile = World->SpawnActor<AProjectile>(ProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);
		}
	}
	if(Projectile)
	{
		Projectile->SetDamage(Damage);
		//Projectile->SetRange(Range);
		Projectile->SetOwner(Hero);
	}
	
}
