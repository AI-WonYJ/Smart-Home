# include <Keypad.h>  // 4x4 키패드 작동 헤더파일
#include <LiquidCrystal_I2C.h>  // I2C_LCD 작동 헤더파일
#include <Servo.h>  // 서보모터 작동 헤더파일

// 4x4 키패드 설정
const byte ROWS = 4;  // 행 개수 정의
const byte COLS = 4;  // 열 개수 정의

char keys[ROWS][COLS] = {  // 행과 열 정의
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {29, 28, 27, 26};  // 행 연결 핀 정의
byte colPins[COLS] = {25, 24, 23, 22};  // 열 연결 핀 정의

Keypad keypad = Keypad( makeKeymap (keys), rowPins, colPins, ROWS, COLS);  // 키패드 오브젝트 생성

// LCD 통신 설정
LiquidCrystal_I2C lcd(0x27, 16, 2);  // I2C 통신 설정
int LCD_ROW, LCD_COL = 0;  // LCD 출력 위치 저장 함수

// 서보모터 작동 설정
Servo myServo;  // 서보모터 선언
int Door_Servo_Pin = 11;  // 서보모터 연결 핀 정의
int Door_Servo_Angle = 0;  // 서보모터 각도 정의

// Password 설정
int tru = 0;  // 패스워드 맞은 수 
int count = 0;
char PW[4] {'1', '2', '3', '4'};
int ch = -1;
int del = 50;

// 초음파센서 설정
#define TRIG 31 //TRIG 핀 설정 (초음파 보내는 핀)
#define ECHO 30 //ECHO 핀 설정 (초음파 받는 핀)
int distance = 0;

// 스피커 설정
#define BUTTON 53
int speakerPin = 12;



void setup() {
  Serial.begin(115200);  // 아두이노 속도 115200으로 Serial 통신 시작
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(BUTTON, INPUT);
  pinMode(speakerPin, OUTPUT);
  lcd.begin();  // LCD 작동 시작
  lcd.clear();  // LCD 출력창 초기화
  myServo.attach(Door_Servo_Pin);
  Fa();
  delay(500);
}

void loop() {
  if(digitalRead(BUTTON) == HIGH) {
    tone(speakerPin,200,100);  //500: 음의 높낮이(주파수), 1000: 음의 지속시간(1초)
  }
  distance = Distance_get();  
  Serial.println(distance);
  if (distance <=20) {
    ch *= -1;
    tone(speakerPin,200,300);  //500: 음의 높낮이(주파수), 1000: 음의 지속시간(1초)
    lcd.backlight();
    lcd.display();
    delay(1000);
  }
  if (ch == 1) {
    lcd.backlight();
    lcd.display();
  } else {
    Fa();
    lcd.noBacklight();
    lcd.noDisplay();
  }
  
  char key = keypad.getKey();
  if (key) {
    Serial.println(key);
    lcd.setCursor(LCD_COL, 1);
    lcd.print(key);
    LCD_COL++ ;
    if(key == PW[count]) {
      count++;
      tru++;
    } else if(key == '#') {
      re();
      tru = 0;
      count = 0;
    } else {
      count++;
    }
  }
  if (count == 4){
    if(tru == 4) {
      Su();
    } else {
      Fa();
    }
    tru = 0;
    count = 0;
  }
  delay(del);
}










int Distance_get() {
  long duration, distance;
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);
  duration = pulseIn (ECHO, HIGH);
  distance = duration * 17 / 1000; 
  // Serial.println(duration );
  Serial.print("\nDIstance : ");
  Serial.print(distance);
  Serial.println(" Cm");

  return distance;
}

void Su() {
  myServo.write(100);
  Serial.println("Open the door");
  lcd.clear();
  lcd.home();
  lcd.print("Open the door");
  lcd.setCursor(0, 1);
  lcd.print("Welcome!");
}

void Fa() {
  myServo.write(0);
  Serial.println("close the door");
  lcd.clear();
  lcd.home();
  lcd.print("Close the door");
  lcd.setCursor(0, 1);
  lcd.print("Enter:");
  LCD_COL = 7;
}

void re() {
  tru = 0;
  count = 0;
  Serial.println("password reset");
  lcd.clear();
  lcd.home();
  lcd.print("ReEnter Password");
  lcd.setCursor(0, 1);
  lcd.print("Enter:");
  LCD_COL = 7;
}