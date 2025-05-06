// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "QuestDataDefs.h"
#include "QuestNameDefs.h"
#include "UPrototypeQuestSubsystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnQuestUpdated, FName, QuestID, bool, bCompleted);

USTRUCT(BlueprintType)
struct FQuestState
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	bool bIsStarted = false;

	UPROPERTY(BlueprintReadWrite)
	bool bIsCompleted = false;
};

UCLASS()
class PROTOTYPEPROJECT_API UUPrototypeQuestSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public :
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	void SetQuestStarted(FName QuestID);
	void SetQuestCompleted(FName QuestID);

	bool IsQuestStarted(FName QuestID) const;
	bool IsQuestCompleted(FName QuestID) const;

	UPROPERTY(BlueprintAssignable)
	FOnQuestUpdated OnQuestUpdated;

	const FQuestData* GetQuestData(FName QuestID);

	bool TryCompleteQuest(FName ItemID);
private :
	UPROPERTY()
	class UDataTable* QuestDataTable;

	UPROPERTY(EditDefaultsOnly, Category = "Quest")
	TMap<FName, FQuestState> QuestStateMap;
};