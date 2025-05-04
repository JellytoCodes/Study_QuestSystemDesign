// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerQuestVolume.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Character.h"
#include "UPrototypeQuestSubsystem.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
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
}

// Called when the game starts or when spawned
void ATriggerQuestVolume::BeginPlay()
{
	Super::BeginPlay();
	
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ATriggerQuestVolume::OnOverlapBegin);

}

void ATriggerQuestVolume::OnOverlapBegin(UPrimitiveComponent *OverlappedComp, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
	if(ACharacter* Character = Cast<ACharacter>(OtherActor))
	{
		if(UUPrototypeQuestSubsystem* QuestSystem = GetGameInstance()->GetSubsystem<UUPrototypeQuestSubsystem>())
		{
			if (APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0))
			{
				if (AGameHUD* HUD = Cast<AGameHUD>(PC->GetHUD()))
				{
					if(TriggerType == EQuestTriggerType::QuestStart)
					{
						for(FName QuestID : QuestIDs)
						{
							if(!QuestSystem->IsQuestStarted(QuestID))
							{
								QuestSystem->SetQuestState(QuestID, true, false);
								HUD->StartedWidget(QuestID);

								break;
							}
						}
					}
					else if(TriggerType == EQuestTriggerType::QuestComplete)
					{
						for(FName QuestID : QuestIDs)
						{
							if(!QuestSystem->IsQuestCompleted(QuestID))
							{
								QuestSystem->SetQuestState(QuestID, false, true);
								HUD->CompletedWidget(QuestID);
								break;
							}
						}
					}
				}
			}		
		}
	}
	BoxComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Destroy();
}
