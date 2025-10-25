#include <Arduino.h>
#include <AccelStepper.h>

int enPin = 4; 
int stepPin = 10;
int dirPin = 3;
int speed = 100; // Vitesse en RPM
int stepsPerRevolution = 200;

int button1 = A2;
int button2 = A3;
int button3 = A4;
int button4 = A5;

int pump1 = 6;
int pump2 = 7;
int pump3 = 8;
int pump4 = 9;

int delayTime = 5000;

AccelStepper myStepper(AccelStepper::DRIVER, stepPin, dirPin);

void activeStepper(bool active) {
  if(active == true) {
    digitalWrite(enPin, LOW);
  } else if(active == false) {
    digitalWrite(enPin, HIGH);
  }
}

void serveDrink(int drink) {
  int moveDistance = 0;
  int pumpPin = 0;

  if(drink == 1) { moveDistance = 150; pumpPin = pump1; }
  else if(drink == 2) { moveDistance = 750; pumpPin = pump2; }
  else if(drink == 3) { moveDistance = 1400; pumpPin = pump3; }
  else if(drink == 4) { moveDistance = 2000; pumpPin = pump4; }

  activeStepper(true);

  myStepper.moveTo(moveDistance);
  myStepper.runToPosition();

  activeStepper(false);

  digitalWrite(pumpPin, HIGH); 
  delay(delayTime);
  digitalWrite(pumpPin, LOW);

  delay(1500);

  activeStepper(true);

  myStepper.moveTo(0);
  myStepper.runToPosition();

  activeStepper(false);
}

void drink1(){
  Serial.println("Boisson 1");
  digitalWrite(13, HIGH);
  serveDrink(1);
  digitalWrite(13, LOW);
}

void drink2(){
  Serial.println("Boisson 2");
  digitalWrite(13, HIGH);
  serveDrink(2);
  digitalWrite(13, LOW);
}

void drink3(){
  Serial.println("Boisson 3");
  digitalWrite(13, HIGH);
  serveDrink(3);
  digitalWrite(13, LOW);
}

void drink4(){
  Serial.println("Boisson 4");
  digitalWrite(13, HIGH);
  serveDrink(4);
  digitalWrite(13, LOW);
}

void setup() {
  Serial.begin(9600);

  while(!Serial);
  Serial.println("DRINK_BOT_V4 prêt à recevoir des données !");

  pinMode(button1, INPUT);
  pinMode(button2, INPUT);
  pinMode(button3, INPUT);
  pinMode(button4, INPUT);

  pinMode(pump1, OUTPUT);
  pinMode(pump2, OUTPUT);
  pinMode(pump3, OUTPUT);
  pinMode(pump4, OUTPUT);

  pinMode(13, OUTPUT);

  pinMode(enPin, OUTPUT);
  activeStepper(false);

  myStepper.setMaxSpeed(2000);
  myStepper.setAcceleration(5000);
}

void loop() {
  if(digitalRead(button1) == LOW) {
    drink1();
  } else if (digitalRead(button2) == LOW) {
    drink2();
  } else if (digitalRead(button3) == LOW) {
    drink3();
  } else if (digitalRead(button4) == LOW) {
    drink4();
  } else if(Serial.available() > 0){
    String input = Serial.readStringUntil('\n');
    int command = input.toInt();

    if(command == 1){
      drink1();
    } else if(command == 2){
      drink2();
    } else if(command == 3){
      drink3();
    } else if(command == 4){
      drink4();
    }
  }
}




// #include <Arduino.h>
// #include <AccelStepper.h>

// int stepPin = 10;
// int dirPin = 3;
// int enPin = 4; // Enable actif LOW

// AccelStepper stepper(AccelStepper::DRIVER, stepPin, dirPin);

// void enableDriver(bool enable) {
//   digitalWrite(enPin, enable ? LOW : HIGH);
// }

// void setup() {
//   pinMode(enPin, OUTPUT);
//   enableDriver(true);

//   stepper.setMaxSpeed(1000);      // Vitesse max en pas/s
//   stepper.setAcceleration(400);   // Accélération en pas/s²
// }

// void loop() {
//   // Déplacement dans un sens
//   stepper.moveTo(1000); // 1000 pas dans un sens
//   while (stepper.distanceToGo() != 0) {
//     stepper.run(); // Gère vitesse + accélération
//   }

//   delay(1000); // Pause 1 seconde

//   // Déplacement dans l’autre sens
//   stepper.moveTo(-1000); // 1000 pas dans l’autre sens
//   while (stepper.distanceToGo() != 0) {
//     stepper.run();
//   }

//   delay(1000); // Pause 1 seconde
// }