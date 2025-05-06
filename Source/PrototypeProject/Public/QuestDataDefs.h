#pragma once

#include "CoreMinimal.h"
#include "Engine/Datatable.h"
#include "QuestDataDefs.generated.h"

//퀘스트 트리거 타입 정의
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
struct FQuestData : public FTableRowBase
{
	GENERATED_BODY()

	//퀘스트 식별
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FName QuestID;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FText QuestTitle;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FText QuestDescription;

	//퀘스트 트리거 방식
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	EQuestTriggerType TriggerType;

	//퀘스트 타입 설정
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	EQuestConditionType ConditionType;

	//완료 조건에 필요한 아이템
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TArray<FName> RequiredItems;
	
	//특정 액터와의 상호작용 조건
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TArray<FName> RequiredInteractions;

	//연계 퀘스트
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TArray<FName> NextQuestIDs;

	//반복 퀘스트 설정
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	bool bIsRepeatable = false;
};