// Fill out your copyright notice in the Description page of Project Settings.


#include "PickupComponent.h"

#include "Hero.h"
#include "GameFramework/RotatingMovementComponent.h"

UPickupComponent::UPickupComponent()
{
	RotatingMovementComponent = CreateDefaultSubobject<URotatingMovementComponent>(TEXT("RotatingMovementComponent"));
	SphereRadius = 32.f;

	SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SetCollisionProfileName("NoCollision");
	SetCollisionResponseToAllChannels(ECR_Ignore);
	SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	SetGenerateOverlapEvents(true);
	SetCanEverAffectNavigation(false);
	CanCharacterStepUpOn = ECB_No;
	
}

void UPickupComponent::BeginPlay()
{
	Super::BeginPlay();
	OnComponentBeginOverlap.AddDynamic(this, &UPickupComponent::OnSphereBeginOverlap);
}

void UPickupComponent::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
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
