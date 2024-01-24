// Fill out your copyright notice in the Description page of Project Settings.


#include "SamplePawn.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Bullet.h"

// Sets default values
ASamplePawn::ASamplePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComponent");
	SetRootComponent(StaticMeshComponent);

	FloatingPawnMovement = CreateDefaultSubobject<UFloatingPawnMovement>("FloatingPawnMovement");

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArmComponent->SetupAttachment(GetRootComponent());
	SpringArmComponent->TargetArmLength = 500.0f;
	SpringArmComponent->TargetOffset = FVector(0.0f, 0.0f, 100.0f);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(SpringArmComponent);
	

	bUseControllerRotationYaw = true;
	bUseControllerRotationPitch = true;
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

void ASamplePawn::Turn(float value)
{
	AddControllerYawInput(value);
}

void ASamplePawn::LookUp(float value)
{
	AddControllerPitchInput(value);
}

void ASamplePawn::Fire()
{
	if(!BulletClass) return; //if no bullet class is set, return

	//spawn bullet
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.Owner = this;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParameters.Instigator = this;
	SpawnParameters.bNoFail = true;

	FTransform SpawnTransform;
	SpawnTransform.SetLocation(GetActorLocation() + GetActorForwardVector() * BulletSpawnOffset);
	SpawnTransform.SetRotation(GetActorRotation().Quaternion());
	
	
	
	ABullet* Bullet = GetWorld()->SpawnActor<ABullet>(BulletClass, SpawnTransform, SpawnParameters);
	
	
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

	PlayerInputComponent->BindAxis("MoveForward",this,&ASamplePawn::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASamplePawn::MoveRight);
	PlayerInputComponent->BindAxis("Turn",this, &ASamplePawn::Turn);
	PlayerInputComponent->BindAxis("LookUp", this, &ASamplePawn::LookUp);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ASamplePawn::Fire);
}

