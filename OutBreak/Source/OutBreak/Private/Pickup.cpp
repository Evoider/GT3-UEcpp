// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickup.h"

#include "Hero.h"
#include "GameFramework/RotatingMovementComponent.h"

UPickup::UPickup()
{
	RotatingMovementComponent = CreateDefaultSubobject<URotatingMovementComponent>(TEXT("RotatingMovementComponent"));
	SphereRadius = 32.f;
}

void UPickup::BeginPlay()
{
	Super::BeginPlay();
	OnComponentBeginOverlap.AddDynamic(this, &UPickup::OnSphereBeginOverlap);
}

void UPickup::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AHero* Character = Cast<AHero>(OtherActor);
	if(Character != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Pickup"));
		OnPickUp.Broadcast(Character);
		OnComponentBeginOverlap.RemoveAll(this);
		RotatingMovementComponent->DestroyComponent();
		DestroyComponent();
	}
}
