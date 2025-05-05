// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestNPC.h"
#include "PrototypeProject/PrototypeProjectCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "GameHUD.h"
#include "Components/BoxComponent.h"

// Sets default values
AQuestNPC::AQuestNPC()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CollisionComp = CreateDefaultSubobject<UBoxComponent>("Collision");
	RootComponent = CollisionComp;
	CollisionComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionComp->SetCollisionObjectType(ECC_WorldDynamic);
	CollisionComp->SetCollisionResponseToChannels(ECR_Ignore);
	CollisionComp->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
}

// Called when the game starts or when spawned
void AQuestNPC::BeginPlay()
{
	Super::BeginPlay();

	if (UUPrototypeQuestSubsystem* QuestSystem = GetGameInstance()->GetSubsystem<UUPrototypeQuestSubsystem>())
	{
		QuestSystem->RegisterQuest(FQuestNameHelper::ToFName(QuestID), TriggerType);
	}
}

// Called every frame
void AQuestNPC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool AQuestNPC::Interact(APrototypeProjectCharacter *PlayerCharacter)
{
	if(UUPrototypeQuestSubsystem* QuestSystem = GetGameInstance()->GetSubsystem<UUPrototypeQuestSubsystem>())
	{
		FName QuestName = FQuestNameHelper::ToFName(QuestID);
		EQuestTriggerType Type = QuestSystem->GetQuestTriggerType(QuestName);
		
		if(Type == TriggerType) //TriggerType = EQuestTriggerType::Interaction
		{			
			if(APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0))
			{
				if(AGameHUD* HUD = Cast<AGameHUD>(PC->GetHUD()))
				{
					if(!QuestSystem->IsQuestStarted(QuestName))
					{
						FQuestData Data;
						Data.TriggerType = EQuestTriggerType::Interaction;
						Data.ConditionType = EQuestConditionType::PickupItem;
						Data.RequiredValue = "KEY001";

						QuestSystem->SetQuestStarted(QuestName, Data);

						HUD->StartedWidget(QuestName);
					}
					/*PiupItemQuest 변경으로 해당 코드는 사용하지 않음
					else if(!QuestSystem->IsQuestCompleted(QuestName))
					{
						QuestSystem->SetQuestCompleted(QuestName);
						HUD->CompletedWidget(QuestName);
					}*/
				}
			}
			return true;
		}
	}
	return false;
}