// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;
	bIsDead = false;

	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::TakeDamage);
}

void UHealthComponent::TakeDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
	AController* InstigatedBy, AActor* DamageCauser)
{
	OnDamageTaken.Broadcast();
	Health -= Damage;
	if(Health <= 0) Die();
	OnHealthChanged.Broadcast(Health);
	UE_LOG(LogTemp, Warning, TEXT("Health of %s is %d"), *GetOwner()->GetName(), Health);
}



void UHealthComponent::Die()
{
	OnDeath.Broadcast();
	bIsDead = true;
	Health = 0;
}


void UHealthComponent::Heal(int32 HealAmount)
{
	OnHeal.Broadcast();
	Health += HealAmount;
	if(Health > MaxHealth) Health = MaxHealth;
	OnHealthChanged.Broadcast(Health);
}


