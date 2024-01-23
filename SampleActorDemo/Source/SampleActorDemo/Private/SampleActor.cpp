// Fill out your copyright notice in the Description page of Project Settings.


#include "SampleActor.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ASampleActor::ASampleActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComponent");
}

// Called when the game starts or when spawned
void ASampleActor::BeginPlay()
{
	Super::BeginPlay();

	StaticMeshComponent->SetWorldScale3D(FMath::VRand()); // Randomize scale
}

// Called every frame
void ASampleActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

