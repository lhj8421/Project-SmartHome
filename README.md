# Project-SmartHome
## STM32와 아두이노 키트의 부품들을 활용한 스마트홈 구현
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

- **MCU : STM32F411RE**
- **입력장치 : 조이스틱, 물 수위센서**
- **출력장치 : 서보모터, LCD**
- **개발방식 : 타이머를 활용한 서보모터 속도 조절, ADC WatchDog를 활용한 물 수위센서의 값에 따라 서보모터 속도 조절**

<img width="1212" height="657" alt="Image" src="https://github.com/user-attachments/assets/acc19cb5-2e5b-470c-b880-16da7cb9551b" />

<img width="1217" height="673" alt="Image" src="https://github.com/user-attachments/assets/b2e7e9ee-18c9-4783-9077-6f2f27ee5f6e" />

<img width="1213" height="656" alt="Image" src="https://github.com/user-attachments/assets/b044d4c9-6d67-4885-a17a-ffdaaa6a9662" />
----------------------------------------------------------------------------------------

### 3. 주요 기능
- **조이스틱 : 방향에 따라서 LOW, MIDDLE, HIGH, AUTO 모드 설정**
- **물 수위센서 : AUTO모드 시 설정한 범위에 따라서 LOW, MIDDLE, HIGH 모드 설정**
- **서보모터 : LOW, MIDDLE, HIGH 모드마다 해당 모드에 맞는 속도 출력**
- **LCD : 어떤 모드로 동작되고 있는지 LCD 화면에 출력**

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
| **이두현** | 서보모터 / LCD |
| **이환중** | 조이스틱 / 물 수위센서 |

----------------------------------------------------------------------------------------

### 6. 어려웠던 점
- **물 수위센서는 물의 높이만 이용해서 측정되기 때문에 강수량 기준으로 하는 AUTO모드에서 물 수위센서의 ADC 값이 
  불안정하여 값의 범위를 정하는 데 어려움이 있었음**
- **데이터형을 선언할 때 한 군데를 잘못 선언하여서 버그가 발생하는 어려움이 있었음**
