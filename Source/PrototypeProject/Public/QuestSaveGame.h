// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "QuestDataDefs.h"
#include "UPrototypeQuestSubsystem.h"
#include "QuestSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class PROTOTYPEPROJECT_API UQuestSaveGame : public USaveGame
{
	GENERATED_BODY()
	
public :
	UPROPERTY()
	TMap<FName, FQuestState> SavedQuestStates;
};
