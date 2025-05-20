const int buttonPins[3] = {2, 3, 4};    
const int ledPins[3] = {5, 6, 7};       

const int motorIn1 = 8;
const int motorIn2 = 9;
const int motorEnable = 10;

int currentFloor = 0;

void setup() {
  Serial.begin(9600);
  
  for (int i = 0; i < 3; i++) {
    pinMode(buttonPins[i], INPUT_PULLUP);  
    pinMode(ledPins[i], OUTPUT);
  }

  pinMode(motorIn1, OUTPUT);
  pinMode(motorIn2, OUTPUT);
  pinMode(motorEnable, OUTPUT);

  updateLEDs();
}

void loop() {
  for (int i = 0; i < 3; i++) {
    if (digitalRead(buttonPins[i]) == LOW) {
      Serial.print("Button ");
      Serial.print(i);
      Serial.println(" pressed");

      if (i != currentFloor) {
        moveElevator(i);
        currentFloor = i;
        updateLEDs();
      }
      delay(500); 
    }
  }
}

void moveElevator(int targetFloor) {
  int direction = (targetFloor > currentFloor) ? 1 : -1;

  Serial.print("Moving from floor ");
  Serial.print(currentFloor);
  Serial.print(" to floor ");
  Serial.println(targetFloor);

  if (direction == 1) {
    digitalWrite(motorIn1, HIGH);
    digitalWrite(motorIn2, LOW);
  } else {
    digitalWrite(motorIn1, LOW);
    digitalWrite(motorIn2, HIGH);
  }

  digitalWrite(motorEnable, HIGH);
  delay(abs(targetFloor - currentFloor) * 2000); 

  digitalWrite(motorEnable, LOW);
  digitalWrite(motorIn1, LOW);
  digitalWrite(motorIn2, LOW);

  Serial.println("Motor stopped");
}

void updateLEDs() {
  for (int i = 0; i < 3; i++) {
    digitalWrite(ledPins[i], (i == currentFloor));
  }
  Serial.print("LED Floor: ");
  Serial.println(currentFloor);
}
