// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "UPrototypeQuestSubsystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnQuestUpdated, FName, QuestID, bool, bCompleted);

UENUM(BlueprintType)
enum class EQuestTriggerType : uint8
{
	None UMETA(DisplayName = "None"),
	Trigger UMETA(DisplayName = "Trigger"),
	Interaction UMETA(DisplayName = "Interaction"),
	Pickup UMETA(DisplayName = "Pickup"),
};

UENUM(BlueprintType)
enum class EQuestConditionType : uint8
{
	None,
	ReachArea,
	TalkToNPC,
	PickupItem,
	KillEnemy,
	Custom,
};

USTRUCT(BlueprintType)
struct FQuestData
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	bool bIsStarted = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	bool bIsCompleted = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	EQuestTriggerType TriggerType = EQuestTriggerType::None;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	EQuestConditionType ConditionType = EQuestConditionType::None;

	UPROPERTY()
	FName RequiredValue = NAME_None;
};

UCLASS()
class PROTOTYPEPROJECT_API UUPrototypeQuestSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public :
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	void SetQuestStarted(FName QuestID, FQuestData AddData);
	void SetQuestCompleted(FName QuestID);
	void RegisterQuest(FName QuestID, EQuestTriggerType Type);

	bool IsQuestStarted(FName QuestID) const;
	bool IsQuestCompleted(FName QuestID) const;

	EQuestTriggerType GetQuestTriggerType(FName QuestID) const;
	EQuestConditionType GetQuestConditionType(FName QuestID) const;

	bool TryCompleteQuest(FName QuestID, EQuestConditionType CompletedType, FName Value);

	UPROPERTY(BlueprintAssignable)
	FOnQuestUpdated OnQuestUpdated;

	FName GetCurrentQuestID(bool bIsCompleted) const;

private :
	UPROPERTY(EditDefaultsOnly, Category = "Quest")
	TMap<FName, FQuestData> QuestMap;
};