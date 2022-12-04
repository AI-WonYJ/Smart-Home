#include "LedControl.h" // 8x32 도트 매트릭스 라이브러리
#include <DHT11.h>  // 온습도센서 라이브러리

LedControl lc=LedControl(12,11,10,4); // Din 핀을 12번, ClK핀을 11번 CS핀을 10번에 연결, 매트릭스는 4개를 사용 선언
int num;

int pin = 2;  // 온습도 센서 Serial핀을 2번 핀과 연결
DHT11 dht11(pin);  // 온습도 센서 핀으로 설정

void setup() {
  Serial.begin(115200);
  for(num=0; num<4; num++) { // 매트릭스 0번부터 3번까지 세팅
    lc.shutdown(num,false); // 0~3번까지 매트릭스 절전모드 해제
    lc.setIntensity(num,8); // 매트릭스의 밝기 선언 0~15의 수
    lc.clearDisplay(num); // 매트릭스 led를 초기화
  }
}


void matrix() {  // matrix 함수 선언
  // 한글 '매'를 이진수로 배열 선언
  byte m[8]={
    B00000101,
    B00000101,
    B11110101,
    B10010111,
    B10010101,
    B11110101,
    B00000101,
    B00000101
  };
  // 한글 '트'를 이진수로 배열 선언
  byte t[8]={
    B00111100,
    B00100000,
    B00111100,
    B00100000,
    B00111100,
    B00000000,
    B01111110,
    B00000000
    };
  // 한글 '릭'를 이진수로 배열 선언
  byte r[8]={
    B01111010,
    B00001010,
    B01111010,
    B01000010,
    B01111010,
    B00000000,
    B00111110,
    B00000010
    };
    // 한글 '스'를 이진수로 배열 선언
    byte x[8]={
      B00000000,
      B00001000,
      B00010100,
      B00100010,
      B01000001,
      B00000000,
      B01111111,
      B00000000
      };
    // lc.setRow 함수는 행(Row) 기준으로 도트매트릭스를 제어 lc.setRow(matrix_number,Row,value)
    for(int j=0; j<8; j++) {
      lc.setRow(3,j,m[j]); // 0번째 매트릭스에서 '매'출력
      lc.setRow(2,j,t[j]); // 1번째 매트릭스에서 '트'출력
      lc.setRow(1,j,r[j]); // 2번째 매트릭스에서 '릭'출력
      lc.setRow(0,j,x[j]); // 3번째 매트릭스에서 '스'출력
 }
 delay(1000);
}

void loop() {
  matrix();
  for(num=0; num<4; num++) {  // 4개의 매트릭스led 초기화
  lc.clearDisplay(num);
  }
  int err;
  float temp, humi;
  if((err=dht11.read(humi, temp)) == 0) {
    Serial.pirnt("Temperature: ");
    Serial.print(temp);
    Serial.print(" humidity:");
    Serial.print(humi);
    Serial.println();
  }
  else {
    Serial.println();
    Serial.print("Error No: ");
    Serial.print(err);
    Serial.println():
  }
  delay(1000);
}