// Copyright Epic Games, Inc. All Rights Reserved.

#include "EndlessRunnercppGameMode.h"
#include "EndlessRunnercppCharacter.h"
#include "UObject/ConstructorHelpers.h"

AEndlessRunnercppGameMode::AEndlessRunnercppGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
