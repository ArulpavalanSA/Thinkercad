#include <Servo.h>

const int moisturePin = A0;
const int threshold = 500;  
const int servoPin = 9;

Servo valve;

void setup() {
  Serial.begin(9600);
  valve.attach(servoPin);
  valve.write(0); 
}

void loop() {
  int moisture = analogRead(moisturePin);
  Serial.print("Moisture Level: ");
  Serial.println(moisture);

  if (moisture < threshold) {
    Serial.println("Soil is dry! Opening valve...");
    valve.write(90); 
    delay(3000);     
    valve.write(0);  
  } else {
    Serial.println("Soil is wet. No watering needed.");
    valve.write(0);
  }

  delay(5000); 
}
