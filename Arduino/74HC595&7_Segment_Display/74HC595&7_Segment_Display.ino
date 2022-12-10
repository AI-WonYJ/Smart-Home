unsigned char LED_OF[] = {
  B00111111,  //0
  B00000110,  //1
  B01011011,  //2
  B01001111,  //3
  B01100110,  //4
  B01101101,  //5
  B01111101,  //6
  B00000111,  //7
  B01111111,  //8
  B01101111   //9
};

int SH_CP = 12;
int ST_CP = 8;
int DS = 11;

void setup() {
  pinMode(SH_CP, OUTPUT);
  pinMode(ST_CP, OUTPUT);
  pinMode(DS, OUTPUT);
}

void loop() {
  for (int i = 0; i < 16; i++) {
    shiftOut(DS,SH_CP, MSBFIRST, LED_OF[i]);
    digitalWrite(ST_CP, LOW);
    digitalWrite(ST_CP, HIGH);
    delay(1000);
  }
}
