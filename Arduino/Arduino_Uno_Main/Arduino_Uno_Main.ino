#include <DHT11.h>  // 온습도센서 헤더파일
#include "LedControl.h" // 라이브러리 사용 선언
#include <IRremote.h>

// 온습도 센서 설정
int pin = 2;  // 온습도센서 연결 핀
DHT11 dht11(pin);
int DHT11_Error_Code = 0;
float temp = 0;

// 8x32 매트릭스 설정
// Din 핀을 12번, ClK핀을 11번 CS핀을 10번에 연결, 매트릭스는 4개를 사용 선언
LedControl lc=LedControl(12,11,10,4);
byte digits[10][8] = {
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

byte signs [4][8] ={
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
#define irOut A0
IRrecv irrecv(irOut);
int a;





void setup() {
  Serial.begin(9600);
  irrecv.enableIRIn();
  pinMode(5, OUTPUT);              // 5번핀을 출력모드로 설정합니다.
  pinMode(6, OUTPUT);              // 6번핀을 출력모드로 설정합니다.
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
  int a = 0;
}

void loop() {
  if (irrecv.decode()) {   
    Serial.println(IrReceiver.decodedIRData.decodedRawData);
    switch (IrReceiver.decodedIRData.decodedRawData) {
      case 0:
        Serial.println("1");
        a = 1;
        break;
      case 3877175040:
        Serial.println("2");
        a = 2;
        break; 
      case 2707357440:
        Serial.println("3");
        a = 3;
        break; 
      default:
        break;
    }
    irrecv.resume();
  }

  int err;
  float temp, humi;
  if((err=dht11.read(humi, temp)) == 0) {
    DHT11_Error_Code = 0;
  }
  else {
    DHT11_Error_Code = 1;
  }
  if (DHT11_Error_Code == 0) {
    if (temp >= 20) {
      analogWrite(5,0);
      analogWrite(6,150);
    }
    else {
      analogWrite(5,0);
      analogWrite(6,0);
    }
  }
  if (a == 1) {
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
  }
  delay(300);
}