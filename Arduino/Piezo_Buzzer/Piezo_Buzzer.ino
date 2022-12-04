int speakerpin = 12; //스피커가 연결된 디지털핀 설정
 
void setup() {
}
 
void loop() {
  tone(speakerpin,500,1000);  //500: 음의 높낮이(주파수), 1000: 음의 지속시간(1초)
  delay(2000); 
}
