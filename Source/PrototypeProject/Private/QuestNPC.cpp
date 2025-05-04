// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestNPC.h"
#include "PrototypeProject/PrototypeProjectCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "UPrototypeQuestSubsystem.h"
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
	
}

// Called every frame
void AQuestNPC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool AQuestNPC::Interact(APrototypeProjectCharacter *PlayerCharacter)
{
	UE_LOG(LogTemp, Warning, TEXT("TriggerType: %d"), static_cast<uint8>(TriggerType));
	if(TriggerType == EQuestTriggerType::Interaction)
	{
		UE_LOG(LogTemp, Log, TEXT("NPC Interact"));
		if(UUPrototypeQuestSubsystem* QuestSystem = GetGameInstance()->GetSubsystem<UUPrototypeQuestSubsystem>())
		{
			UE_LOG(LogTemp, Log, TEXT("QuestSystem Successed"));
			for(FName QuestID : QuestIDs)
			{
				if(!QuestSystem->IsQuestStarted(QuestID))
				{					
					if(APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0))
					{
						if(AGameHUD* HUD = Cast<AGameHUD>(PC->GetHUD()))
						{
							QuestSystem->SetQuestState(QuestID, true, false);
							HUD->StartedWidget(QuestID);
							break;
						}
					}
				}
			}
			return true;
		}
	}
	return false;
}