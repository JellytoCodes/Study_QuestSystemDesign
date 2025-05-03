// Copyright Epic Games, Inc. All Rights Reserved.

#include "PrototypeProjectGameMode.h"
#include "PrototypeProjectCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "GameHUD.h"

APrototypeProjectGameMode::APrototypeProjectGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	HUDClass = AGameHUD::StaticClass();
}
