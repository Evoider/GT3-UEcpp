// Fill out your copyright notice in the Description page of Project Settings.


#include "Hero.h"

#include "HealthComponent.h"
#include "WeaponComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"


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

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
	HealthComponent->SetMaxHealth(100.f);
	
	

	bUseControllerRotationYaw = false;

}

void AHero::Die()
{
	UE_LOG(LogTemp, Warning, TEXT("Hero Died"));
	// Play death animation
	
	// Disable input
	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	DisableInput(PlayerController);
	// Disable collision
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	// Disable movement
	GetCharacterMovement()->DisableMovement();
	// Disable shooting
	StopFire();
	// Restart level
	UGameplayStatics::OpenLevel(this, FName(GetWorld()->GetName()));
}

// Called when the game starts or when spawned
void AHero::BeginPlay()
{
	Super::BeginPlay();

	HealthComponent->OnDeath.AddDynamic(this, &AHero::Die);
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


