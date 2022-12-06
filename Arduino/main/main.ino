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
Servo myServo;
int Door_Servo_Pin = 11;
int Door_Servo_Angle = 0;

// Password 설정
char* Password = "1234";
int position = 0;
int wrong = 0;

void setup() {
  Serial.begin(115200);  // 아두이노 속도 115200으로 Serial 통신 시작
  lcd.begin();  // LCD 작동 시작
  lcd.clear();  // LCD 출력창 초기화
  myServo.attach(Door_Servo_Pin);
  setLocked(true);
  delay(500);
}

void loop() {
  lcd.home();
  lcd.print("Enter a Password");
  char key = keypad.getKey();  // 4x4 키패드에 입력된 값을 key변수에 저장
  Serial.println(position, wrong);
  Serial.println(key);
  if ((key >= "0" && key <="9") || (key >= "A" && key <="D") || (key == "*" || key == "#")) {
    if(key == "*" || key == "#") {
      position = 0;
      wrong = 0;
      setLocked(true);
    } else if (key = Password[position]) {
      position++;
      wrong = 0;
    } else if (key != Password[position]) {
      position = 0;
      setLocked(true);
      wrong++;
    }
    if (position == 4) {
      setLocked(false);
    }
    if (wrong == 4) {
      Serial.println("4회 오류");
      wrong = 0;
    }    
  }
  delay(100);


  // if(key) {  // 4x4 키패드에 입력이 들어오면
  //   Input_Password[LCD_COL] += key;
  //   Serial.println(Input_Password);
  //   lcd.setCursor(LCD_COL, 1);
  //   lcd.print(key);
  //   LCD_COL += 1;
  //   Serial.println(key);  // Serial Monitor에 출력
  // }
  // if(Input_Password == Password) {
  //   myServo.write(100);
  //   delay(15);    
  // } else {
  //   myServo.write(0);
  //   delay(15);
  // }
  // delay(10);
}

void setLocked(int locked) {
  if(locked) {
    myServo.write(0);
    Serial.println("Locked");
  } else {
    myServo.write(100);
    Serial.println("UnLocked");
  }
}