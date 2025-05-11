# Study_QuestSystemDesign

**Unreal Engine 5.4.4 기반의 학습용 실험 프로젝트**

**이 기능을 이러한 구조로 만든 이유"라는 목적에 중점을 둔 구조 설계형 퀘스트 시스템입니다.**


## 학습 목적
> 본 프로젝트는 Unreal Engine의 구조적 특성을 바탕으로 **Subsystem / Data 중심 흐름 / UI 분리 / Save 연동**을 적용한 구조 설계 기반으로 완성했습니다.  


## 적용 설계 원칙
1. **SRP (단일 책임 원칙)**  
  → Trigger/NPC Actor는 상호작용만 담당하고, 퀘스트 상태 관리는 Subsystem에서 분리 수행하도록 설계하였습니다.

2. **DIP (의존성 역전 원칙)**  
  → UI는 Subsystem에 직접 접근하지 않고, Delegate를 통해 상태 변화를 수신하도록 설계하였습니다.

3. **LSP (리스코프 치환 원칙)**  
  → 퀘스트 상태 관리에 사용되는 구조체 및 Map은 일관된 인터페이스로 처리되어, 각 조건/보상 시스템이 변경 없이 확장 가능

4. **ISP (인터페이스 분리 원칙)**  
  → 퀘스트 UI는 QuestItemWidget(리스트 출력) / QuestNotifyWidget(알림 출력)으로 기능 분리를 설계하였습니다.

5. **OCP (개방-폐쇄 원칙)**  
  → 새로운 트리거 조건, 보상 타입, 퀘스트 분기가 추가되어도 Subsystem의 데이터 기반 설계만으로 확장 가능토록 설계하였습니다.

6. **Event-Driven Design**  
  → 퀘스트 시작/완료 시 Subsystem에서 Broadcast → HUD에서 UI 자동 갱신될 수 있도록 설계하였습니다.

7. **Data-Driven Flow**  
  → FQuestData 기반 UDataTable에서 모든 퀘스트를 정의 및 관리할 수 있도록 설계하였습니다.


## 시스템 아키텍처 요약
**[GameInstance]**  
  └──UPrototypeQuestSubsystem (퀘스트 상태 등록 및 처리)
  
**[TriggerVolume / QuestNPC]**  
  ├──퀘스트 시작 / 완료 조건 판별  
  └──Subsystem과 연동하여 상태 전달

**[GameHUD]**  
  └──UI 위젯 생성 및 관리  

**[QuestUIWidget]**  
  ├──QuestItemWidget       ← 퀘스트 리스트 출력 (병렬 출력)  
  └──QuestNotifyWidget     ← 퀘스트 시작/완료 알림 애니메이션 


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
