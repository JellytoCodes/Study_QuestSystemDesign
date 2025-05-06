#pragma once

#include "CoreMinimal.h"
#include "Engine/Datatable.h"
#include "QuestDataDefs.generated.h"

//����Ʈ Ʈ���� Ÿ�� ����
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

	//����Ʈ �ĺ�
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FName QuestID;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FText QuestTitle;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FText QuestDescription;

	//����Ʈ Ʈ���� ���
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	EQuestTriggerType TriggerType;

	//����Ʈ Ÿ�� ����
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	EQuestConditionType ConditionType;

	//�Ϸ� ���ǿ� �ʿ��� ������
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TArray<FName> RequiredItems;
	
	//Ư�� ���Ϳ��� ��ȣ�ۿ� ����
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TArray<FName> RequiredInteractions;

	//���� ����Ʈ
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TArray<FName> NextQuestIDs;

	//�ݺ� ����Ʈ ����
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	bool bIsRepeatable = false;
};