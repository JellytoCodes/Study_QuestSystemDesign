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
}

void ATriggerQuestVolume::OnOverlapBegin(UPrimitiveComponent *OverlappedComp, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
	if(ACharacter* Character = Cast<ACharacter>(OtherActor))
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
		if(QuestData->TriggerType != EQuestTriggerType::Trigger) return;

		//����Ʈ ���� ó��
		if(!QuestSystem->IsQuestStarted(QuestID))
		{
			QuestSystem->SetQuestStarted(QuestID);
			UE_LOG(LogTemp, Log, TEXT("Started Quest :%s"), *QuestData->QuestTitle.ToString());
		}

		//����Ʈ �Ϸ� ó��
		else if(QuestData->ConditionType == EQuestConditionType::ReachArea && 
		QuestSystem->IsQuestStarted(QuestID) && !QuestSystem->IsQuestCompleted(QuestID))
		{
			QuestSystem->SetQuestCompleted(QuestID);
			UE_LOG(LogTemp, Log, TEXT("Completed Quest :%s"), *QuestData->QuestTitle.ToString());
		}
	}

	//�ߺ� ���� ������ ���� ����
	BoxComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Destroy();
}
