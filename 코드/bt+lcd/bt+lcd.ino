/*
  blue test: 
  http://www.kccistc.net/
  작성일 : 2024.03.22
  작성자 : IoT 임베디드 KSH
*/
#include <SoftwareSerial.h>
#include <Wire.h>
#include <MsTimer2.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

#define DEBUG
#define ARR_CNT 5
#define CMD_SIZE 60
char lcdLine1[17] = "Smart Home";
char lcdLine2[17] = "";
char sendBuf[CMD_SIZE];
char recvBuf[CMD_SIZE];
bool timerIsrFlag = false;
unsigned int secCount;
SoftwareSerial BTSerial(10, 11); // RX ==>BT:TXD, TX ==> BT:RXD
bool updatTimeFlag = true;

typedef struct {
  int year;
  int month;
  int day;
  int hour;
  int min;
  int sec;
} DATETIME;
DATETIME dateTime = { 0, 0, 0, 12, 0, 0 };

bool dbRequestFlag = false;
unsigned int dbRequestCounter = 0;

void setup()
{
#ifdef DEBUG
  Serial.begin(115200);
  Serial.println("setup() start!");
#endif
  lcd.init();
  lcd.backlight();
  lcdDisplay(0, 0, lcdLine1);
  lcdDisplay(0, 1, lcdLine2);
 
  BTSerial.begin(9600); // set the data rate for the SoftwareSerial port
  MsTimer2::set(1000, timerIsr); // 1000ms period
  MsTimer2::start();
}

void loop()
{
  if (BTSerial.available())
    bluetoothEvent();

  if (timerIsrFlag)   //1마다 실행
  {
    timerIsrFlag = false;

    sprintf(lcdLine1, "%02d.%02d  %02d:%02d:%02d", dateTime.month, dateTime.day, dateTime.hour, dateTime.min, dateTime.sec);
    lcdDisplay(0, 0, lcdLine1);

    if (updatTimeFlag) {
      BTSerial.write("[GETTIME]\n");
      updatTimeFlag = false;
    }

    if (dbRequestFlag) {
      BTSerial.write("[OJS_SQL]GETDB\n");
      dbRequestFlag = false;
    }
  }
  
#ifdef DEBUG
  if (Serial.available())
    BTSerial.write(Serial.read());
#endif
}

void bluetoothEvent()
{
  int i = 0;
  char * pToken;
  char * pArray[ARR_CNT] = {0};
  char recvBuf[CMD_SIZE] = {0};
  int len = BTSerial.readBytesUntil('\n', recvBuf, sizeof(recvBuf) - 1);

#ifdef DEBUG
  Serial.print("Recv : ");
  Serial.println(recvBuf);
#endif

  pToken = strtok(recvBuf, "[@]");
  while (pToken != NULL)
  {
    pArray[i] =  pToken;
    if (++i >= ARR_CNT)
      break;
    pToken = strtok(NULL, "[@]");
  }

  if (!strcmp(pArray[0], "GETTIME")) 
  {  //GETTIME
    dateTime.year = (pArray[1][0] - 0x30) * 10 + pArray[1][1] - 0x30;
    dateTime.month = (pArray[1][3] - 0x30) * 10 + pArray[1][4] - 0x30;
    dateTime.day = (pArray[1][6] - 0x30) * 10 + pArray[1][7] - 0x30;
    dateTime.hour = (pArray[1][9] - 0x30) * 10 + pArray[1][10] - 0x30;
    dateTime.min = (pArray[1][12] - 0x30) * 10 + pArray[1][13] - 0x30;
    dateTime.sec = (pArray[1][15] - 0x30) * 10 + pArray[1][16] - 0x30;
    return;
  } 

  if(!strcmp(pArray[1],"SENSOR") && pArray[2] != NULL && pArray[3] != NULL)
  {
    sprintf(lcdLine2, "T:%s H:%s", pArray[2], pArray[3]);
    lcdDisplay(0,1,lcdLine2);
    return;
  }
}

void timerIsr()
{
  timerIsrFlag = true;
  secCount++;
  clock_calc(&dateTime);

  dbRequestCounter++;
  if(dbRequestCounter >= 10)
  {
    dbRequestFlag = true;
    dbRequestCounter = 0;
  }
}

 void clock_calc(DATETIME *dateTime) {
  int ret = 0;
  dateTime->sec++;  // increment second

  if (dateTime->sec >= 60)  // if second = 60, second = 0
  {
    dateTime->sec = 0;
    dateTime->min++;

    if (dateTime->min >= 60)  // if minute = 60, minute = 0
    {
      dateTime->min = 0;
      dateTime->hour++;  // increment hour
      if (dateTime->hour == 24) {
        dateTime->hour = 0;
        updatTimeFlag = true;
      }
    }
  }
}

void lcdDisplay(int x, int y, char * str)
{
  int len = 16 - strlen(str);
  lcd.setCursor(x, y);
  lcd.print(str);
  for (int i = len; i > 0; i--)
    lcd.write(' ');
}
