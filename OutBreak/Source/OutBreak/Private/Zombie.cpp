// Fill out your copyright notice in the Description page of Project Settings.


#include "Zombie.h"

#include "HealthComponent.h"
#include "Hero.h"
#include "Engine/DamageEvents.h"

// Sets default values
AZombie::AZombie()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
	HealthComponent->SetMaxHealth(100.f);

	AttackSpeed = 1.f;
	Damage = 10.f;
}

// Called when the game starts or when spawned
void AZombie::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AZombie::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AZombie::StartAttacking()
{
	UE_LOG(LogTemp, Warning, TEXT("Zombie Attack"));
	TArray<FHitResult> HitResults;
	GetWorld()->SweepMultiByObjectType(HitResults, GetActorLocation(),
	                                   GetActorLocation() + GetActorForwardVector() * 300.f, FQuat::Identity,
	                                   FCollisionObjectQueryParams::AllDynamicObjects,
	                                   FCollisionShape::MakeSphere(50.f));
	for (auto Hit : HitResults)
	{
		if (Hit.GetActor() != this)
			Hero = reinterpret_cast<AHero*>(Hit.GetActor());
		if (Hero)
			break;
		Hero = nullptr;
	}
	if (Hero)
	{
		Hero->TakeDamage(Damage, FDamageEvent(), GetController(), this);
		Attack();
	}
}
