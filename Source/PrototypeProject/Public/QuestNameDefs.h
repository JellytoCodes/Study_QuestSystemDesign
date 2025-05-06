#pragma once

#include "CoreMinimal.h"
#include "QuestNameDefs.generated.h"

UENUM(BlueprintType)
enum class EQuestName : uint8
{
	None,
	EnteredArea01,
	EnteredArea02,
	TalkToNPC01,
	TalkToNPC02,
	PickedKeyItem,
};

class FQuestNameHelper
{
public :
	static FName ToFName(EQuestName Quest)
	{
		switch(Quest)
		{
			case EQuestName::EnteredArea01 : return "EnteredArea01";
			case EQuestName::EnteredArea02 : return "EnteredArea02";
			case EQuestName::TalkToNPC01 : return "TalkToNPC01";
			case EQuestName::TalkToNPC02 : return "TalkToNPC02";
			case EQuestName::PickedKeyItem : return "PickedKeyItem";
			default : return NAME_None;
		}
	}

	static EQuestName FromFName(const FName& QuestName)
	{
		if(QuestName == "None") return EQuestName::None;
		else if(QuestName == "EnteredArea01") return EQuestName::EnteredArea01;
		else if(QuestName == "EnteredArea02") return EQuestName::EnteredArea02;
		else if(QuestName == "TalkToNPC01") return EQuestName::TalkToNPC01;
		else if(QuestName == "TalkToNPC02") return EQuestName::TalkToNPC02;
		else if(QuestName == "PickedKeyItem") return EQuestName::PickedKeyItem;
		else return EQuestName::None;
	}
};