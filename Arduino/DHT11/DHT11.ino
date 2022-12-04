#include <DHT11.h>
int pin = 2;
DHT11 dht11(pin);

void setup() {
  Serial.begin(115200);
}

void loop() {
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
  delay(DHT11_RETRY_DELAY);
}