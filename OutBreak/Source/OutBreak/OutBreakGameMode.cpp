// Copyright Epic Games, Inc. All Rights Reserved.

#include "OutBreakGameMode.h"
#include "UObject/ConstructorHelpers.h"

AOutBreakGameMode::AOutBreakGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	//static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Ressoures/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	//DefaultPawnClass = PlayerPawnClassFinder.Class;

}
