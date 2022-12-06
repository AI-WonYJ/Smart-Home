#include <Servo.h>

 

Servo myServo;

int servoPin = 11;

String buffer = "";

boolean process_it = false;

 

void setup() {

  myServo.attach(servoPin); // 서보 모터 연결

  Serial.begin(9600);

}

 

void loop() {

  myServo.write(110);
  delay(400);
  myServo.write(0);
  delay(800);
  // while (Serial.available()) { // 시리얼 모니터 입력 값 읽기

  //   char data = Serial.read();

  //   if (data == '\n') { // 문자열 종료

  //     process_it = true;

  //     break;

  //   }

  //   buffer += data;

  // }

  // if (process_it) { // 문자열 처리

  //   process_it = false;

  //   int angle = buffer.toInt(); // 정수값으로 변환

  //   Serial.print(String(">> ") + buffer);

  //   if (angle < 0 || angle > 180) { // 잘못된 각도 입력

  //     Serial.println(" ... invalid angle.");

  //   }

  //   else {

  //     Serial.println();

  //     myServo.write(angle); // 각도 제어

  //     delay(3);

  //   }

  //   buffer = ""; // 버퍼 비움

  // }

}