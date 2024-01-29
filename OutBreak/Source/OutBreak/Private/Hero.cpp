// Fill out your copyright notice in the Description page of Project Settings.


#include "Hero.h"

#include "WeaponComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"


// Sets default values
AHero::AHero()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	CameraFP = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraFP"));
	CameraFP->SetupAttachment(GetCapsuleComponent());
	CameraFP->SetRelativeLocation(FVector(-39.56f, 1.75f, 64.f)); // Position the camera
	CameraFP->bUsePawnControlRotation = true;

	MeshFP = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MeshFP"));
	MeshFP->SetOnlyOwnerSee(true);
	MeshFP->SetupAttachment(CameraFP);
	MeshFP->bCastDynamicShadow = false;
	MeshFP->CastShadow = false;
	MeshFP->SetRelativeLocation(FVector(-30.f, 0.f, -150.f));
	

	bUseControllerRotationYaw = false;

}

// Called when the game starts or when spawned
void AHero::BeginPlay()
{
	Super::BeginPlay();
	
}

void AHero::AddWeapon(UWeaponComponent* NewWeaponComponent)
{
	bHasWeapon = true;
	WeaponComponent = NewWeaponComponent;
}

void AHero::RemoveWeapon()
{
	WeaponComponent = nullptr;
}

bool AHero::GetHasWeapon()
{
	return bHasWeapon;
}

void AHero::Fire()
{
	if(!WeaponComponent) return;
	WeaponComponent->Fire();
}

void AHero::StopFire()
{
	if(!WeaponComponent) return;
	WeaponComponent->StopFire();
}


