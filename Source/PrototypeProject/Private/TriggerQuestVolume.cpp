// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerQuestVolume.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "QuestUIWidget.h"
#include "GameHUD.h"

// Sets default values
ATriggerQuestVolume::ATriggerQuestVolume()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));
	RootComponent = BoxComponent;
	BoxComponent->SetCollisionProfileName(TEXT("Trigger"));
	BoxComponent->SetGenerateOverlapEvents(true);
}

// Called when the game starts or when spawned
void ATriggerQuestVolume::BeginPlay()
{
	Super::BeginPlay();	
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ATriggerQuestVolume::OnOverlapBegin);

	if(UUPrototypeQuestSubsystem* QuestSystem = GetGameInstance()->GetSubsystem<UUPrototypeQuestSubsystem>())
	{
		QuestSystem->RegisterQuest(FQuestNameHelper::ToFName(QuestID), TriggerType);
	}
}

void ATriggerQuestVolume::OnOverlapBegin(UPrimitiveComponent *OverlappedComp, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
	if(ACharacter* Character = Cast<ACharacter>(OtherActor))
	{
		if(UUPrototypeQuestSubsystem* QuestSystem = GetGameInstance()->GetSubsystem<UUPrototypeQuestSubsystem>())
		{
			FName QuestName = FQuestNameHelper::ToFName(QuestID);
			EQuestTriggerType Type = QuestSystem->GetQuestTriggerType(QuestName);
			if(Type == TriggerType)
			{
				if (APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0))
				{

					if (AGameHUD* HUD = Cast<AGameHUD>(PC->GetHUD()))
					{
						if(!QuestSystem->IsQuestStarted(QuestName))
						{
							FQuestData Data;
							Data.TriggerType = EQuestTriggerType::Trigger;
							Data.ConditionType = EQuestConditionType::ReachArea;
							Data.RequiredValue = "None";

							QuestSystem->SetQuestStarted(QuestName, Data);
							HUD->StartedWidget(QuestName);
						}
						else if(!QuestSystem->IsQuestCompleted(QuestName))
						{
							QuestSystem->SetQuestCompleted(QuestName);
							HUD->CompletedWidget(QuestName);
						}
					}
				}
				BoxComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
				Destroy();
			}		
		}
	}
}
