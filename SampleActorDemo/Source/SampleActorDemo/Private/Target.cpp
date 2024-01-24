// Fill out your copyright notice in the Description page of Project Settings.


#include "Target.h"
#include "Components/StaticMeshComponent.h"
#include "SampleGameMode.h"
#include "Bullet.h"

// Sets default values
ATarget::ATarget()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComponent");
	SetRootComponent(StaticMeshComponent);

	MovementRange = 300.0f;
}

// Called when the game starts or when spawned
void ATarget::BeginPlay()
{
	Super::BeginPlay();

	OnActorHit.AddDynamic(this, &ATarget::OnTargetHit);

	MoveDirection = FMath::VRand();
}

void ATarget::OnTargetHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{
	
	if (ABullet* Bullet = Cast<ABullet>(OtherActor))
	{
		if (ASampleGameMode* GameMode = GetWorld()->GetAuthGameMode<ASampleGameMode>())
		{
			GameMode->IncreasePoints();
			Destroy();
		}
	}
}

// Called every frame
void ATarget::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector movement = MoveDirection * MovementRange * FMath::Sin(GetWorld()->GetTimeSeconds()) * DeltaTime;
	AddActorWorldOffset(movement, true);
}

