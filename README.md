# Project-SmartHome
## STM32와 아두이노를 활용한 스마트홈 구현
----------------------------------------------------------------------------------------

### 1. 프로젝트 개요
- **여름날 불안정한 온도와 습도로 인해 불쾌지수 증가** 
- **실내 환경 변화에 대한 수동 대응 한계**
- **에너지 효율성 저하 및 전기세/난방비 부담**
  
▶ **맞춤형 환경 제어 스마트 홈 시스템 구현**

----------------------------------------------------------------------------------------

### 2. 개발 환경 및 도구
![C](https://img.shields.io/badge/C-00599C?style=flat-square&logo=c&logoColor=white)
![Python](https://img.shields.io/badge/Python-3776AB?style=flat-square&logo=python&logoColor=white)
![STM32](https://img.shields.io/badge/STM32-03234B?style=flat-square&logo=stmicroelectronics&logoColor=white)
![Arduino](https://img.shields.io/badge/Arduino-00979D?style=flat-square&logo=arduino&logoColor=white)
![STM32CubeIDE](https://img.shields.io/badge/STM32CubeIDE-03234B?style=flat-square&logo=stmicroelectronics&logoColor=white)
![Raspberry Pi](https://img.shields.io/badge/Raspberry%20Pi-A22846?style=flat-square&logo=raspberrypi&logoColor=white)

- **MCU : STM32F411RE, Aduino UNO, Raspberry Pi(서버)**
- **입력장치 : 온습도센서, 애플리케이션**
- **출력장치 : 모터, LCD, 히팅패드, 스탭모터**
- **통신장치 : WIFI모듈, BlueTooth모듈**

<img width="1212" height="657" alt="Image" src="https://github.com/user-attachments/assets/acc19cb5-2e5b-470c-b880-16da7cb9551b" />

<img width="1217" height="673" alt="Image" src="https://github.com/user-attachments/assets/b2e7e9ee-18c9-4783-9077-6f2f27ee5f6e" />
<img width="1213" height="656" alt="Image" src="https://github.com/user-attachments/assets/b044d4c9-6d67-4885-a17a-ffdaaa6a9662" />
----------------------------------------------------------------------------------------

### 3. 주요 기능
- **온습도센서 : 실시간으로 온도와 습도를 측정**
- **히팅패드 : 애플리케이션으로 사용자가 입력한 온도 값(MIN_Temp)보다 실시간 온도가 낮으면 히팅패드 동작**
- **모터 : 애플리케이션으로 사용자가 입력한 온도 값(MAX_Temp)보다 실시간 온도가 높으면 모터 동작**
- **스탭모터 : AI가 예측한 습도값와 비교하여 오차범위에 따라서 딜레이 값으로 속도를 조절**
- **LCD : 현재 날짜와 시간 및 실시간 온도와 습도를 출력**

----------------------------------------------------------------------------------------

### 3-1. AI 습도 예측 모델

**데이터셋**
- 출처 : 기상청 ASOS 시간별 데이터
- 규모 : 약 35000개(4년치)

**모델**
- 알고리즘 : Random Forest Regressor
- 특성 : 순황 인코딩(sin/cos)으로 시간 주기성 반영
- 예측 : 2시간 후 습도

**성능**
- R² Score: 0.913 (91.3% 정확도)
- RMSE: 5.41%
- MAE: 3.67%

----------------------------------------------------------------------------------------

### 4. 기술 구현
- **조이스틱 : 방향에 따른 ADC값을 통해서 모드 설정, 인터럽트를 통해서 스위치 클릭 시 정지**
- **물 수위센서 : ADC WatchDog를 사용해서 ADC값의 범위를 설정해준 뒤 범위에 따라 LOW, MIDDLE, HIGH 모드를 구현**
- **서보모터 : 타이머(50Hz, 20ms)마다 인터럽트를 발생시켜주고, 모드에 따른 각도 값을 주어서 속도 조절**
- **여기서 서보모터의 속도는 실제 속도가 아닌 동일한 시간에 움직이는 각도 차이로 인해서 속도가 차이나는 것처럼 보이는 것**

----------------------------------------------------------------------------------------

### 5. 팀원
| 이름 | 담당 |
|------|------|
| **이환중** | 하드웨어 구성 / 블루투스 통신 |
| **오정선** | AI 모델링 / 웹 페이지 구현 / 와이파이 통신 |

----------------------------------------------------------------------------------------

### 6. 어려웠던 점
- **와이파이가 자주 끊겨서 입력에 따른 센서 동작을 확인하는 데 어려웠음**
- **와이파이와 블루투스를 서버와 통신하는 방식을 구현하는 것이 어려웠음**
