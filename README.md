#Study_QuestSystemDesign

**Unreal Engine 5.4.4 기반의 학습용 실험 프로젝트**

## 학습 목적
1. Subsystem 구조를 이해하고 설계하는 방법에 대해 배워보고자 AI(Chatgpt)를 활용하여 실습중입니다.
  
2. 단순 기능을 구현했다는 목적이 아닌 OOP 설계 원칙에 어긋나지 않게 기능을 구현하는 것을 목표로 하여
   Unreal Engine의 구조 및 시스템 흐름 구조화를 학습하고자 합니다.

3. 이 학습을 통해 포트폴리오를 만드는데 위 내용에 언급한 바와 같이 이런 기능을 왜 구현하였는가?
   보다 이 기능을 구현하기 위해 왜 이런 구조를 설계하였는가? 라는 목표로 하고자합니다.

## 학습 목표
1. UGameInstanceSubsystem 및 UWorldSubsystem의 구조 이해  

2. Subsystem을 활용한 **데이터 중심 퀘스트 흐름** 구현  

3. DataTable을 활용한 **데이터 관리 방법** 진행  

## 구현 시스템

1. **UPrototypeQuestSubsystem** [GameInstanceSubsystem Class]  
→ 퀘스트 등록 / 진행 / 완료 상태 관리  

2. **AQuestTriggerVolume** [Actor Class]  
→ 퀘스트 트리거 영역 판별 및 퀘스트 현황 Subsystem 연동  

3. **AQuestNPC** [Actor Class]  
→ 상호작용에 의한 퀘스트 발생 및 퀘스트 현황 Subsystem 연동  
→ 퀘스트 완료 조건 제어  
 
4. **UQuestUIWidget** [UserWidget Class]  
→ 퀘스트 이름/상태 출력 담당  
→ 출력 애니메이션 (Fade In/Out) 구현  

5. **GameHUD** [HUD Class]  
→ UI 매니징 및 위젯 호출 처리 담당  

## 학습한 기술
1. 언리얼 구조를 이해하면서 OOP 설계 원칙 중 **단일 책임 원칙(SRP)**, **의존성 역전 원칙(DIP)**을 학습

2. Subsystem을 통해 퀘스트 진행 조건을 Actor가 직접 판단하지 않는 **단일 책임 원칙(SRP)**을 학습
   
3. Delegate를 활용한 Subsystem↔UI 출력 연동으로 **반응형 시스템 설계**를 학습

4. DataTable, SaveGame을 통한 상태 저장 및 로딩으로 **데이터 기반 흐름 구성**을 학습

## 진행 현황
**완료된 항목**
- [X] Subsystem 연동 및 트리거/완료 조건 구현  
  → UserWidget, HUD, Subsystem 등의 구조 세분화를 통해 Actor의 책임을 명확히 분리  
- [X] Delegate 기반 UI 출력  
  → GameInstanceSubsystem을 활용하여 반응형 퀘스트 알림 구조 완성  
- [X] DataTable 연동  
  → FQuestData를 선언 및 정의하여 퀘스트 데이터 정의 자동화 및 일관된 관리가 가능하도록 구성  
- [X] SaveGame 구조 (퀘스트 현황 Save / Load)
  → USaveGame을 활용하여 퀘스트 상태를 저장 및 복원하여 지속 가능한 퀘스트 시스템 구현
  → 플레이어가 특정 키를 Bind 했을 때 Save/Load Widget이 활성화/비활성화될 수 있도록 구현

**예정된 항목**
- [ ] 병렬 퀘스트 대응 설계
  → 다수의 퀘스트를 동시에 진행 및 트래킹할 수 있는 병렬 구조 설계

## Author
   **JellytoCodes / 2025.05**
