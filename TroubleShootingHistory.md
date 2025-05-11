# 📝 QuestSystemDesign TroubleShooting History

**퀘스트 시스템을 구현하면서 문제 해결 과정을 기록하고자 만든 기록물입니다.**  

<br>

## 📌 CASE 1 : UI 위젯 생성 시 Constructor에서의 크래시 (2025.04)  
**⚠️ 문제 상황**  
&nbsp;&nbsp;&nbsp;→ 퀘스트 완료 후 메시지를 출력하는 위젯을 생성자(Constructor) 내에서 CreateWidget을 호출하여 생성, 게임 실행 직후 크래시 발생  
&nbsp;&nbsp;&nbsp;→ PIE 테스트 시점에서도 즉시 종료도히었고 로그에는 월드 참조 오류가 발생  

**🔍 원인 분석**  
&nbsp;&nbsp;&nbsp;→ Actor 생성 사이클상 Constructor는 UWrold가 완전히 초기화되지 않은 시점으로 이때 위젯을 생성하면 해당 위젯이 필요한 컨텍스트(GameInstance, PlayerController 등)이 없어 참조 오류가 발생하는 문제  

**🛠️ 해결 방안**  
&nbsp;&nbsp;&nbsp;→ CreateWidget 호출을 BeginPlay로 옮기고 퀘스트 완료 시점에는 Delegate를 통해 위젯 출력 로직을 제어하도록 구조 변경  

**📈 개선 방안**  
&nbsp;&nbsp;&nbsp;→ **생성 타이밍을 고려하여 구조 설계할 수 있도록하며 상태 기반 트리거를 통해 분리 관리하는 방법도 고려해볼 수 있도록 함**  

<br>

## 📌 CASE 2 : TriggerVolume과 QuestNPC의 조건 분기 충돌 (2025.04)
**⚠️ 문제 상황**  
&nbsp;&nbsp;&nbsp;→ TriggerVolume과 QuestNPC가 동일한 퀘스트를 처리할 때 조건이 충돌하거나 중복 반응하여 퀘스트가 정상 완료되지 않거나 잘못된 트리거가 반응하는 문제 발생  

**🔍 원인 분석**  
&nbsp;&nbsp;&nbsp;→ 퀘스트 분기 로직이 구분 없이 분산되어 있었고 조건 체크 방식이 일관되지 않아 의도한 흐름과 실제 처리 흐름이 엇갈려 생긴 문제  
  
**🛠️ 해결 방안**  
&nbsp;&nbsp;&nbsp;→ FQuestData 구조체에 멤버를 세분화하여 명확히 구분하여 저장하도록 리팩토링  
&nbsp;&nbsp;&nbsp;→ 퀘스트 관련 Actor는 데이터 기반으로 판단하도록 통일하고 QuestSubsystem을 통해 상태를 중앙관리하도록 변경  

**📈 개선 방안**  
&nbsp;&nbsp;&nbsp;→ **논리 흐름만이 아닌 데이터 설계로도 흐름을 제어할 수 있도록 하며 조건 분기는 구조체 단위에서 명확하게 구분하여 유지보수와 확장성을 고려하여 설계하도록 함**  

<br>

## 📌 CASE 3 : 퀘스트 진행 상태가 UI에 반영되지 않음 (2025.05)
**⚠️ 문제 상황**  
&nbsp;&nbsp;&nbsp;→ 퀘스트가 시작되거나 완료되었음에도 UI에 관련 메시지가 표시되지 않는 현상 발생

**🔍 원인 분석**  
&nbsp;&nbsp;&nbsp;→ 바인딩이 위젯이 완전히 생성되기 전에 QuestSubSystem에서 Broadcast는 반응하나 UI 위젯에서 해당 Delegate를 수신하지 못하여 발생한 문제  

**🛠️ 해결 방안**  
&nbsp;&nbsp;&nbsp;→ Delegate 바인딩 코드를 위젯의 NativeConstruct 함수 내부로 옮겨 위젯 생성 이후에 연결되도록 수정  

**📈 개선 방안**  
&nbsp;&nbsp;&nbsp;→ **Delegate를 사용하는 구조에서는 반드시 생성 시점과 연결 시점을 구분하여 연결 타이밍의 신뢰성을 보장하는 구조로 안정성을 높이도록 함**  

<br>

## 📌 CASE 4 : 퀘스트 메시지 출력 중복 및 시각적 충돌
**⚠️ 문제 상황**  
&nbsp;&nbsp;&nbsp;→ 퀘스트 메시지가 여러 개 동시에 출력될 경우 UI가 겹쳐 보이며 Fade In/Out 타이밍이 어긋남

**🔍 원인 분석**  
&nbsp;&nbsp;&nbsp;→ 여러 개의 메시지를 동시에 출력 요청하는 구조에서 출력 순서를 제어하지 않아 메시지가 겹치는 문제

**🛠️ 해결 방안**  
&nbsp;&nbsp;&nbsp;→ 메시지를 출력 요청 시 Queue에 쌓아 순차적으로 출력되도록 구조를 변경하고, 출력 중에는 다음 메시지를 대기 상태로 유지하여 시각적 충돌 방지

**📈 개선 방안**  
&nbsp;&nbsp;&nbsp;→ **UI도 데이터처럼 선형 흐름과 상태를 고려하여 설계하여 연출에 몰입감을 더할 수 있도록 함**  
