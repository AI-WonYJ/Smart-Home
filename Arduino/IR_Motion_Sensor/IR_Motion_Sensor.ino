/*
 * PIR sensor tester
 */
 
int ledPin = 11;                // choose the pin for the LED
int inputPin = 12;               // choose the input pin (for PIR sensor)
int val = 0;                    // variable for reading the pin status
 
void setup() {
  pinMode(ledPin, OUTPUT);      // declare LED as output
  pinMode(inputPin, INPUT);     // declare sensor as input
  Serial.begin(115200);
}
 
void loop(){
  val = digitalRead(inputPin);  // read input value
  if (val == HIGH) {            // check if the input is HIGH
    digitalWrite(ledPin, HIGH);  // turn LED ON
    Serial.println("On");
  } else {
    digitalWrite(ledPin, LOW); // turn LED OFF
    Serial.println("Off");
  }
}