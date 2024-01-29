// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponComponent.h"

#include "EnhancedInputSubsystems.h"
#include "Hero.h"

UWeaponComponent::UWeaponComponent()
{
	// Default offset from the character location for projectiles to spawn
	MuzzleOffset = FVector(100.0f, 0.0f, 10.0f);
	AttachToSocketName = "GripPoint";
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
	
	Hero->AddWeapon(this);
	
}

void UWeaponComponent::DetachWeapon()
{
	if(!Hero) return;
	
	DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
	Hero->RemoveWeapon();
}

void UWeaponComponent::Fire()
{
	UE_LOG(LogTemp, Warning, TEXT("Fire"));
}

void UWeaponComponent::AddAmmo(int32 Amount)
{
}
