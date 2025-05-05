#Study_PrototypeProject

**Unreal Engine 5.4.4 기반의 학습용 실험 프로젝트**

## 학습 목적
 1. Subsystem 구조를 이해하고 설계하는 방법에 대해 배워보고자 AI(Chatgpt)를 활용하여 실습중입니다.
  
 2. 단순 기능을 구현했다는 목적이 아닌 OOP 설계 원칙에 어긋나지 않게 기능을 구현하는 것을 목표로 하여
 Unreal Engine의 구조 및 시스템 흐름 구조화를 학습하고자 합니다.

 3. 이 학습을 통해 포트폴리오를 만드는데 위 내용에 언급한 바와 같이 이런 기능을 왜 구현하였는가? 보다
 이 기능을 구현하기 위해 왜 이런 구조를 설계하였는가? 라는 철학을 가지기 위한 목표로 하고자합니다.

## 학습 목표
 1. UGameInstanceSubsystem 및 UWorldSubsystem의 구조 이해

 2. Subsystem을 활용한 **데이터 중심 퀘스트 흐름** 구현

 3. DataTable을 활용한 **데이터 관리 방법** 진행

## 구현 시스템

 1. UPrototypeQuestSubsystem [GameInstanceSubsystem Class]
  - 퀘스트 등록 / 진행 / 완료 상태 관리

 3. AQuestTriggerVolume [Actor Class]
  - 퀘스트 트리거 영역 판별 및 퀘스트 현황 Subsystem 연동

 3. AQuestNPC [Actor Class]
  - 상호작용에 의한 퀘스트 발생 및 퀘스트 현황 Subsystem 연동
  - 퀘스트 완료 조건 제어
 
 4. UQuestUIWidget [UserWidget Class]
  - 퀘스트 이름/상태 출력 담당
  - 출력 애니메이션 (Fade In/Out) 구현

 5. GameHUD [HUD Class]
  - UI 매니징 및 위젯 호출 처리 담당

## 학습한 기술
 1. Unreal Subsystem 구조
    
 2. Delegate를 활용한 Subsystem↔UI 출력 연동

 3. 상태 기반 퀘스트 구조 설계

## 진행 상태
 - [X] Subsystem 연동 및 트리거/완료 조건 구현
 - [X] Delegate 기반 UI 출력
 - [ ] DataTable 연동
 - [ ] SaveGame 구조 (퀘스트 현황 Save / Load)
 - [ ] 병렬 퀘스트 대응 설계

## Author
 **JellytoCodes / 2025.05**
