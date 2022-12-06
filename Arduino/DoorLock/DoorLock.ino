#include <Keypad.h>
#include <Servo.h>

int tru = 0;
int count = 0;
char PW[4] {'1', '2', '3', '4'};

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

Keypad keypad = Keypad( makeKeymap (keys), rowPins, colPins, ROWS, COLS);

Servo myServo;

void setup() {
  Serial.begin(9600);
  myServo.attach(11);
  Fa();
}

void loop() {
  char key = keypad.getKey();
  if (key) {
    Serial.println(key);
    if(key == PW[count]) {
      count++;
      tru++;
    } else if (key != PW[count]) {
      count++;
    }
    
    if(key == "#") {
      re();
      tru = 0;
      count = 0;
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
  }
}

void Su() {
  myServo.write(100);
  Serial.println("Open the door");
}

void Fa() {
  myServo.write(0);
  Serial.println("close the door");
}

void re() {
  tru = 0;
  count = 0;
  Serial.println("password reset");
}