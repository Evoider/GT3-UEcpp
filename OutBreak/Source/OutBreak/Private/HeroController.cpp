// Fill out your copyright notice in the Description page of Project Settings.


#include "HeroController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Hero.h"

void AHeroController::BeginPlay()
{
	Super::BeginPlay();

	// Add Input Mapping Context
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(
		GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
		Subsystem->AddMappingContext(FireMappingContext, 1);
	}

	Hero = Cast<AHero>(GetPawn());
}

void AHeroController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if(!Hero) Hero = Cast<AHero>(GetPawn());
	Hero->AddMovementInput(Hero->GetActorForwardVector(), 1);
}

///////////////////////// INPUT ///////////////////////////
void AHeroController::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();
	
	if(!Hero) Hero = Cast<AHero>(GetPawn());
	Hero->AddMovementInput(Hero->GetActorRightVector(), MovementVector.X);
}

void AHeroController::Jump(const FInputActionValue& Value)
{
	if(!Hero) Hero = Cast<AHero>(GetPawn());
	Hero->Jump();
}

void AHeroController::StopJumping(const FInputActionValue& Value)
{
	if(!Hero) Hero = Cast<AHero>(GetPawn());
	Hero->StopJumping();
}

void AHeroController::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();
	
	ControlRotation.Pitch = FMath::ClampAngle(ControlRotation.Pitch - LookAxisVector.Y, -45.0f, 45.0f);
	ControlRotation.Yaw = FMath::ClampAngle(ControlRotation.Yaw + LookAxisVector.X, -90.0f, 90.0f);
	
}

void AHeroController::Fire(const FInputActionValue& Value)
{
	if(!Hero) Hero = Cast<AHero>(GetPawn());
	if(Hero->GetHasWeapon())
	{
		Hero->Fire();
	}
}

void AHeroController::StopFire(const FInputActionValue& InputActionValue)
{
	if(!Hero) Hero = Cast<AHero>(GetPawn());
	if(Hero->GetHasWeapon())
	{
		Hero->StopFire();
	}
}


void AHeroController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UInputComponent* PlayerInputComponent = InputComponent;

	if (PlayerInputComponent)
	{
		// Set up action bindings
		if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
		{
			// Jumping
			EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &AHeroController::Jump);
			EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this,
			                                   &AHeroController::StopJumping);

			// Moving
			EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AHeroController::Move);

			// Looking
			EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AHeroController::Look);

			// Fire
			EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Started, this, &AHeroController::Fire);
			EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Completed, this, &AHeroController::StopFire);
		}
		
	}
}
