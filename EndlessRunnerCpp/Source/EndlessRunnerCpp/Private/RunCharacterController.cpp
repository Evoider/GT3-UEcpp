// Fill out your copyright notice in the Description page of Project Settings.


#include "RunCharacterController.h"
#include "RunCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"

void ARunCharacterController::BeginPlay()
{
	Super::BeginPlay();

	RunCharacter = Cast<ARunCharacter>(GetPawn());
	if(RunCharacter)
	{
		UE_LOG(LogTemp,Warning,TEXT("RunCharacter is valid"));
		if(UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext,0);
		}
		else
		{
			UE_LOG(LogTemp,Warning,TEXT("Subsystem is not valid"));
		}
	}
	else
	{
		UE_LOG(LogTemp,Warning,TEXT("RunCharacter is not valid"));
	}
}

void ARunCharacterController::Move(const FInputActionValue& Value)
{
	 FVector2D MovementVector = Value.Get<FVector2D>();


	 FVector RightVector = RunCharacter->GetActorRightVector();
	
	RunCharacter->AddMovementInput(RightVector, MovementVector.X);

}

void ARunCharacterController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UInputComponent* PlayerInputComp = InputComponent;

	if(UEnhancedInputComponent* EnhancedInputComp = Cast<UEnhancedInputComponent>(PlayerInputComp))
	{
		UE_LOG(LogTemp,Warning,TEXT("EnhancedInputComp is valid"));
		EnhancedInputComp->BindAction(MoveAction,ETriggerEvent::Triggered,this,&ARunCharacterController::Move);
	}
	else
	{
		UE_LOG(LogTemp,Warning,TEXT("EnhancedInputComp is not valid"));
	}

	
}

