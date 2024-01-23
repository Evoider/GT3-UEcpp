// Fill out your copyright notice in the Description page of Project Settings.


#include "SamplePawn.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Camera/CameraComponent.h"

// Sets default values
ASamplePawn::ASamplePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComponent");
	SetRootComponent(StaticMeshComponent);

	FloatingPawnMovement = CreateDefaultSubobject<UFloatingPawnMovement>("FloatingPawnMovement");

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(GetRootComponent());
	CameraComponent->SetRelativeLocation(FVector(-500.0f, 0.0f, 500.0f));
	CameraComponent->SetRelativeRotation(FRotator(-45.0f, 0.0f, 0.0f));
	
}

// Called when the game starts or when spawned
void ASamplePawn::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASamplePawn::MoveForward(float Value)
{
	FloatingPawnMovement->AddInputVector(GetActorForwardVector() * Value);
}

void ASamplePawn::MoveRight(float Value)
{
	FloatingPawnMovement->AddInputVector(GetActorRightVector() * Value);
}

// Called every frame
void ASamplePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASamplePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"),this,&ASamplePawn::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &ASamplePawn::MoveRight);
}

