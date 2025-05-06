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
}

// Called every frame
void AQuestNPC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AQuestNPC::Interact(APrototypeProjectCharacter *PlayerCharacter)
{		
	if(APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0))
	{
		//����Ʈ ����ý��� �Ҵ� �� �ε� Failed �� return
		auto QuestSystem = GetGameInstance()->GetSubsystem<UUPrototypeQuestSubsystem>();
		if(!QuestSystem || QuestID.IsNone()) return;

		//����Ʈ ���������̺� �Ҵ� �� �ε� Failed �� return
		const FQuestData* QuestData = QuestSystem->GetQuestData(QuestID);
		if(!QuestData) return;

		//�̹� �Ϸ�� ����Ʈ Skip�� ���� ��ġ
		if(QuestSystem->IsQuestCompleted(QuestID)) return;
		
		//����Ʈ Trigger Ÿ�� �˻�
		if(QuestData->TriggerType != EQuestTriggerType::Interaction) return;

		//����Ʈ ���� ó��
		if(!QuestSystem->IsQuestStarted(QuestID))
		{
			QuestSystem->SetQuestStarted(QuestID);
			UE_LOG(LogTemp, Log, TEXT("Started Quest :%s"), *QuestData->QuestTitle.ToString());
		}
	}
}

FName AQuestNPC::GetQuestID() const
{
	return QuestID;
}
