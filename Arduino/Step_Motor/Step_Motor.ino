#include <Stepper.h>

// 2048:한바퀴(360도), 1024:반바퀴(180도)...
const int stepsPerRevolution = 2048; 
// 모터 드라이브에 연결된 핀 IN4, IN2, IN3, IN1
Stepper myStepper(stepsPerRevolution,11,9,10,8);           
void setup() {
  myStepper.setSpeed(14); 
}
void loop() {
  // 시계 반대 방향으로 한바퀴 회전
  myStepper.step(stepsPerRevolution);
  delay(500);

  // 시계 방향으로 한바퀴 회전
  myStepper.step(-stepsPerRevolution);
  delay(500);
}