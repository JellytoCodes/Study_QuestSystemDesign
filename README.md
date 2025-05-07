#Study_QuestSystemDesign

**Unreal Engine 5.4.4 기반의 학습용 실험 프로젝트**

## 학습 목적
본 프로젝트는 단순한 기능 구현을 넘어
Unreal Engine의 구조적 특성을 바탕으로 **Subsystem / Data 중심 흐름 / UI 분리 / Save 연동**을 적용하여
**OOP 기반 퀘스트 시스템 설계 및 확장 가능 구조**를 실습한 결과물입니다.

> "**이 기능을 만들었습니다**"라는 것보다 "**이 기능을 이러한 구조로 만든 이유는 이러합니다**"라는
의미에 초점을 두고 설계

## 학습한 설계 원칙
> 단순 구현이 아닌, 객체지향 원칙에 기반한 구조 설계 및 책임 분리를 실습을 통해 체득
- [X] **SRP (단일 책임 원칙)**  
  → 액터는 상호작용만 책임지고, 퀘스트 상태는 Subsystem이 전담

- [X] **DIP (의존성 역전 원칙)**  
  → Delegate를 통해 상태 변화를 UI에 통지

- [X] **Event-Driven Design**  
  → 상태 변화에 따라 UI가 반응 (Broadcast 기반)

- [X] **Data-Driven Flow**  
  → DataTable을 통해 퀘스트 데이터 및 흐름을 코드에서 분리

- [X] **OCP (개방-폐쇄 원칙)** *(부분 적용)*  
  → 조건, 보상, 연계 퀘스트 등을 쉽게 확장 가능한 구조로 설계

## 시스템 아키텍처 요약
[GameInstance]  
  └── UPrototypeQuestSubsystem (퀘스트 상태 관리)

[TriggerVolume / QuestNPC]  
  └── 퀘스트 시작 / 완료 조건 판별  
  └── Subsystem과 연동하여 상태 전달

[GameHUD]  
  └── UI 위젯 생성 및 관리  

[QuestUIWidget]  
  ├── QuestItemWidget       ← 퀘스트 리스트 출력 (병렬 출력)  
  └── QuestNotifyWidget     ← 퀘스트 시작/완료 알림 애니메이션 

## 핵심 구현 사항 (완료 항목)
- [X] **Subsystem 연동 및 트리거/완료 조건 구현**   
  → UserWidget, HUD, Subsystem 등의 구조 세분화를 통해 Actor의 책임을 명확히 분리

- [X] **Delegate 기반 반응형 UI 연동**  
  → 퀘스트 시작/완료 시 Broadcast()로 UI에 실시간 반영

- [X] **DataTable 기반 퀘스트 정의**  
  → FQuestData 구조체 기반으로 ID/트리거/조건 등 퀘스트 구조 설계
  → UDataTable로 관리하여 쉽게 수정 가능

- [X] **SaveGame 구조 (퀘스트 현황 Save / Load)**  
  → USaveGame을 활용하여 퀘스트 상태를 저장 및 불러오기  
  → 플레이어 특정 키 Bind를 통해 GameSaveLoadWidget으로 UI 슬롯 처리  

- [X] **병렬 퀘스트 대응 설계**  
  → TMap을 활용하여 다중 퀘스트 동시 진행 구조화  
  → QuestItemWidget을 통해 실시간 목록 동기화  

## Author
   **JellytoCodes / 2025.05**
