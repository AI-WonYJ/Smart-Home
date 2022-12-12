#include <DHT11.h>  // 온습도센서 헤더파일
#include "LedControl.h" // 라이브러리 헤더파일
#include <IRremote.h>  //IR리모컨 헤더파일
#include <Servo.h>  // 서보모터 헤더파일
#include "MQ135.h"  //MQ135 CO2 센서 헤더파일

// 온습도 센서 설정
int pin = 2;  // 온습도센서 연결 핀
DHT11 dht11(pin);
int DHT11_Error_Code = 0;  //온습도센서 오류 코드 저장
float temp = 0;
float humi = 0;

// 8x32 매트릭스 설정
// Din 핀을 12번, ClK핀을 11번 CS핀을 10번에 연결, 매트릭스는 4개를 사용 선언
LedControl lc=LedControl(12,11,10,4);
byte digits[10][8] = {  // 8x32 매트릭스 숫자 표현
  {  // 0
    B00000000,
    B00011000,
    B00100100,
    B00100100,
    B00100100,
    B00100100,
    B00011000,
    B00000000,    
  },
  {  // 1
    B00000000,
    B00001000,
    B00011000,
    B00001000,
    B00001000,
    B00001000,
    B00011100,
    B00000000
  },
  {  // 2
    B00000000,
    B00011000,
    B00100100,
    B00000100,
    B00001000,
    B00010000,
    B00111100,
    B00000000
  },
  {  // 3
    B00000000,
    B00011000,
    B00100100,
    B00011000,
    B00000100,
    B00100100,
    B00011000,
    B00000000
  },
  {  // 4
    B00000000,
    B00000100,
    B00001100,    
    B00010100,
    B00100100,
    B00111100,
    B00000100,
    B00000000
  },
  {  // 5
    B00000000,
    B00111100,
    B00100000,
    B00111000,
    B00000100,
    B00100100,
    B00011000,
    B00000000
  },
  {  // 6
    B00000000,
    B00011000,
    B00100000,
    B00111000,
    B00100100,
    B00100100,
    B00011000,
    B00000000
  },
  {  // 7
    B00000000,
    B00111100,
    B00000100,
    B00000100,
    B00001000,
    B00010000,
    B00010000,
    B00000000
  },
  {  // 8
    B00000000,
    B00011000,
    B00100100,
    B00011000,
    B00100100,
    B00100100,
    B00011000,
    B00000000
  },
  {  // 9
    B00000000,
    B00011000,
    B00100100,
    B00100100,
    B00011100,
    B00000100,
    B00011000,
    B00000000
  }
};

byte signs [4][8] ={  // 8x32 매트릭스 기호 표현
  {
    B00000000,
    B01111101,
    B00010001,
    B00010000,
    B00010000,
    B00010001,
    B00010001,
    B00000000,
  },
  {
    B00100000,
    B01010000,
    B00100110,
    B00001000,
    B00001000,
    B00001000,
    B00001000,
    B00000110
  },
  {
    B00000000,
    B00000001,
    B01001001,
    B01001000,
    B01111000,
    B01001001,
    B01001001,
    B00000000
  },
  {
    B00000000,
    B01000010,
    B10100100,
    B01001000,
    B00010000,
    B00100100,
    B01001010,
    B10000100
  }
};

// IR리모컨 설정
// 3125149440 3108437760 3125149440: ch- ch ch+
// 3141861120 3208707840 3158572800: << >> >|
// 4161273600 3927310080 4127850240: - + EQ
// 3910598400 3860463360 4061003520: 0 100+ 200+
// 4077715200 3877175040 2707357440: 1 2 3
// 4144561920 3810328320 2774204160: 4 5 6
// 3175284480 2907897600 3041591040: 7 8 9
#define irOut A0  // IR 리모컨 핀 번호
IRrecv irrecv(irOut);

//서보모터 설정
Servo myServo;
int servoPin = 9;

// 
int ch = 0;
int fan = 1;
int door = 0;

// CO2센서 설정
//#define RLOAD 1000
#define RZERO 1
MQ135 gasSensor = MQ135(A0);
int MQval;
int MQsensorPin = A0; 
int MQsensorValue = 0;



void setup() {
  Serial.begin(9600);
  irrecv.enableIRIn();
  myServo.attach(servoPin);
  myServo.write(180);
  pinMode(MQsensorPin, INPUT); 
  delay(1000);
  pinMode(5, OUTPUT);.
  pinMode(6, OUTPUT);
  lc.shutdown(0, false);
  lc.shutdown(1, false);
  lc.shutdown(2, false); 
  lc.shutdown(3, false); 
  lc.setIntensity(0,2);
  lc.setIntensity(1,2);
  lc.setIntensity(2,2);
  lc.setIntensity(3,2);
  lc.clearDisplay(0);
  lc.clearDisplay(1);
  lc.clearDisplay(2);
  lc.clearDisplay(3);
}

void loop() {
  if (irrecv.decode()) {  // IR리모컨에서 신호가 왔을 때
    switch (IrReceiver.decodedIRData.decodedRawData) {  // 신호에 따라 동작
      case 3108437760:  //ch, 매트릭스 온도 표현
        ch = 1;
        int j;
        int t10 = temp/10;
        int t1 = temp-(t10*10);
        Serial.println(temp);
        for (j = 0; j < 8; j++) {
          lc.setRow(3, j, signs[0][j]);
          lc.setRow(2, j, digits[t10][j]);
          lc.setRow(1, j, digits[t1][j]);
          lc.setRow(0, j, signs[1][j]);
        }
        break;
      case 3125149440:  //ch+, 매트릭스 습도 표현
        ch = 2;
            int j;
            int h10 = humi/10;
            int h1 = humi-(h10*10);
            for (j = 0; j < 8; j++) {
              lc.setRow(3, j, signs[2][j]);
              lc.setRow(2, j, digits[h10][j]);
              lc.setRow(1, j, digits[h1][j]);
              lc.setRow(0, j, signs[3][j]);
            }
        break; 
      case 3125149440:  //ch-, 매트릭스 끄기
        ch = 0;
        lc.clearDisplay(0);
        lc.clearDisplay(1);
        lc.clearDisplay(2);
        lc.clearDisplay(3);
        break;
      case 3141861120:  // <<, 창문 닫기
        door = 0;
        myServo.write(180);
        break;
      case 3208707840:  // >>, 창문 열기
        door = 1;
        myServo.write(130);
        break;
      case 3158572800:  // >|, fan 작동 정지 또는 작동 가능 상태 설정
        if (fan == 1) {
          fan = 0;
        } else {
          fan = 1;
        }
        if (DHT11_Error_Code == 0 && fan == 1) {  // 온습도센서 오류 없고 fan 작동 가능 상태일 때
          if (temp >= 20) {  // 온도가 20도 이상이면 fan on
            analogWrite(5,0);
            analogWrite(6,150);
          }
          else {  // 아닐 경우 fan off
            analogWrite(5,0);
            analogWrite(6,0);
          }
        }
      default:
        break;
    }
    irrecv.resume();
  }
  MQval = analogRead(A0); 
  Serial.print("raw = "); 
  Serial.println(MQval); 
  float ppm = gasSensor.getPPM();   // CO2 측정
  int err;
  float temp, humi;
  if((err=dht11.read(humi, temp)) == 0) {  // 온습도 측정
    DHT11_Error_Code = 0;
  }
  else {
    DHT11_Error_Code = 1;
  }
  // 데이터 값을 보낸다.
  Serial.print(ppm); 
  Serial.print("/");
  Serial.print(temp);
  Serial.print("/");
  Serial.print(humi);
  Serial.print("/");
  Serial.print(ch);
  Serial.print("/");
  Serial.print(fan);
  Serial.print("/");
  Serial.print(door);
  delay(300);
}