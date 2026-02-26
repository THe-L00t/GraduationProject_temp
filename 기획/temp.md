### 예상 최종 구조
```
DX12GraduationProject/
 ├─ DX12GraduationProject.sln
 ├─ Engine/              (Static Library)
 ├─ Game/                (Executable)
 ├─ Tools/               (Optional - Asset 변환기)
 ├─ ThirdParty/
 │    ├─ FMOD/
 │    ├─ Assimp/
 │    └─ ImGui/
 ├─ Assets/
 ├─ Shaders/
 └─ Docs/
 ```

### 특징
PBR lite로 개발 진행, 능력이 된다면 풀 PBR진행 
-> 특징을 살리기 위해 최소한 맵을 많이 돌아다니게 되는 장르 

### 그래픽은 PBR로 커버치고, 그렇다면 구조설계가 중요한 장르가 있을까?

실외 -> 실내 -> 시네마틱/실외
실외에서 실내 전환을 통해 PBR효과 극대화, 실외로 나올때는 연출을 통해 PBR효과 보여주기.
* 에셋 퀵셀 사의 메가스캔 이용하기.
https://quixel.com/megascans/

### 그럼 스토리 선으로 어떻게 실외에서 실내로, 실내에서 실외로 이동해야할까?

🌲 2️⃣ 버려진 자연 속 연구시설
세계관
자연에 잠식된 비밀 연구소를 배경으로 어린아이가 이야기를 만들어감. 그리고 옆에서 아빠가 이야기를 들어주는 형식.
* tts 생성 AI 사용하기
https://toolkit.artlist.io/voice-over-generator?mode=text-to-speech&modelGroupID=206&voiceID=32&language=English&voice-catalog=artlist-voices

<실외>
이끼 낀 콘크리트
습기 먹은 금속
거친 암석 + 부드러운 식물 대비

<실내>
녹슨 철문
벗겨진 페인트
먼지 낀 유리
깜빡이는 형광등

👉 “거칠기 맵 + 노멀맵” 체감이 강함.

