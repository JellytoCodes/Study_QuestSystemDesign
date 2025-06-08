# 🧪 Study_QuestSystemDesign  
**Unreal Engine 5.4.4 기반 학습 프로젝트**

<br>

## ✏️ 학습 목적  
**Unreal Engine의 **Subsystem / Data 중심 흐름 / UI 분리 / Save 연동**을 학습하기 위해 진행하였습니다.**  

<br>

## 📐 적용 설계 원칙
**📚 SRP (단일 책임 원칙)**  
&nbsp;&nbsp;&nbsp;→ Trigger/NPC Actor는 상호작용만 담당하고, 퀘스트 상태 관리는 Subsystem에서 분리 수행하도록 설계
  
**📚DIP (의존성 역전 원칙)**  
&nbsp;&nbsp;&nbsp;→ UI는 Subsystem에 직접 접근하지 않고, Delegate를 통해 상태 변화를 수신하도록 설계

**📚 LSP (리스코프 치환 원칙)**  
&nbsp;&nbsp;&nbsp;→ 퀘스트 상태 관리에 사용되는 구조체 및 Map은 일관된 인터페이스로 처리되어, 각 조건/보상 시스템이 변경 없이 확장 가능토록 설계

**📚 ISP (인터페이스 분리 원칙)**  
&nbsp;&nbsp;&nbsp;→ 퀘스트 UI는 QuestItemWidget(리스트 출력) / QuestNotifyWidget(알림 출력)으로 기능 분리를 설계

**📚 OCP (개방-폐쇄 원칙)**  
&nbsp;&nbsp;&nbsp;→ 새로운 트리거 조건, 보상 타입, 퀘스트 분기가 추가되어도 Subsystem의 데이터 기반 설계만으로 확장 가능토록 설계

**📚 Event-Driven Design**  
&nbsp;&nbsp;&nbsp;→ 퀘스트 시작/완료 시 Subsystem에서 Broadcast → HUD에서 UI 자동 갱신될 수 있도록 설계

**📚 Data-Driven Flow**  
&nbsp;&nbsp;&nbsp;→ FQuestData 기반 UDataTable에서 모든 퀘스트를 정의 및 관리할 수 있도록 설계

<br>

## 🗂️ 시스템 아키텍처 요약
**🧱 GameInstance**  
&nbsp;└──UPrototypeQuestSubsystem (퀘스트 상태 등록 및 처리)
  
**🧱 TriggerVolume / QuestNPC**  
 &nbsp;├──퀘스트 시작 / 완료 조건 판별  
&nbsp;└──Subsystem과 연동하여 상태 전달

**🧱 GameHUD**  
&nbsp;└──UI 위젯 생성 및 관리  

**🧱 QuestUIWidget**  
&nbsp;├──QuestItemWidget       ← 퀘스트 리스트 출력 (병렬 출력)  
&nbsp;└──QuestNotifyWidget     ← 퀘스트 시작/완료 알림 애니메이션 

<br>

## ⚙️ 핵심 구현 사항 (완료 항목)
✅ **Subsystem 연동 및 트리거/완료 조건 구현**   

✅ **Delegate 기반 반응형 UI 연동**  

✅ **DataTable 기반 퀘스트 정의**  

✅ **SaveGame 구조 (퀘스트 현황 Save / Load)**  

✅ **병렬 퀘스트 대응 설계**  

<br>

## 🧑‍💻 Author
**JellytoCodes / 2025.05**
