#include <AccelStepper.h>
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

Adafruit_MotorShield AFMS = Adafruit_MotorShield();

Adafruit_StepperMotor *myStepper1 = AFMS.getStepper(200, 1);
Adafruit_StepperMotor *myStepper2 = AFMS.getStepper(200, 2);

bool isRunning = 0;
bool dance1move = 0;
bool dance2move = 0;
bool dance3move = 0;
bool dance4move = 0;
bool dance5move = 0;

//char mySteps;
int mode = -1;

unsigned long currentTime;
unsigned long lastTime;

void forwardstep1() {
  myStepper1->onestep(FORWARD, DOUBLE);
}
void backwardstep1() {
  myStepper1->onestep(BACKWARD, DOUBLE);
}

void forwardstep2() {
  myStepper2->onestep(FORWARD, DOUBLE);
}
void backwardstep2() {
  myStepper2->onestep(BACKWARD, DOUBLE);
}

AccelStepper Astepper1(forwardstep1, backwardstep1);
AccelStepper Astepper2(forwardstep2, backwardstep2);

void setup() {
  Serial.begin(9600);
  AFMS.begin();

  Astepper1.setMaxSpeed(100.0);
  Astepper1.setAcceleration(500.0);
  Astepper2.setMaxSpeed(100.0);
  Astepper2.setAcceleration(500.0);

}

void loop() {
  currentTime = millis();
  if (currentTime - lastTime <= 2000) {
    mode = 0;
  } else if (currentTime - lastTime > 2000 && currentTime - lastTime <= 12000) {
    mode = 1;
  } else if (currentTime - lastTime > 12000 && currentTime - lastTime <= 14000) {
    mode = 5;
  } else if (currentTime - lastTime > 14000 && currentTime - lastTime <= 30000) {
    mode = 2;
  } else if (currentTime - lastTime > 30000 && currentTime - lastTime <= 32000) {
    mode = 0;
  } else if (currentTime - lastTime > 32000 && currentTime - lastTime <= 39000) {
    mode = 3;
  } else if (currentTime - lastTime > 39000 && currentTime - lastTime <= 55000) {
    mode = 4;
  }
  else {
    lastTime  = currentTime;
  }

  if (!isRunning) {
    switch (mode) {
      case 1:
        dance1();
        break;
      case 2:
        dance3();
        break;
      case 3:
        dance2();
        break;
      case 4:
        dance4();
        break;
      case 5:
        dance5();
        break;
      default:
        //nothing
        break;
    }
  }

  if (!Astepper1.run() && !Astepper2.run() && isRunning) {
    Serial.println("stepping done!");
    isRunning = false;
  }

  Astepper1.run();
  Astepper2.run();
}

void dance1() {
  Astepper1.setMaxSpeed(300.0);
  Astepper1.setAcceleration(500.0);
  Astepper2.setMaxSpeed(300.0);
  Astepper2.setAcceleration(500.0);
  if (dance1move) {
    Astepper1.move(20);
    Astepper2.move(-20);
    dance1move = false;
  }
  else {
    Astepper1.move(-20);
    Astepper2.move(20);
    dance1move = true;
  }
  isRunning = true;
}


void dance2() {
  Astepper1.setMaxSpeed(300.0);
  Astepper1.setAcceleration(500.0);
  Astepper2.setMaxSpeed(300.0);
  Astepper2.setAcceleration(500.0);
  if (dance2move) {
    Astepper1.move(-40);
    Astepper2.move(40);
    dance2move = false;
  }
  else {
    Astepper1.move(40);
    Astepper2.move(-40);
    dance2move = true;
  }
  isRunning = true;
}

void dance3() {
  Astepper1.setMaxSpeed(100.0);
  Astepper1.setAcceleration(500.0);
  Astepper2.setMaxSpeed(100.0);
  Astepper2.setAcceleration(500.0);
  if (dance3move) {
    Astepper1.move(-20);
    Astepper2.move(-20);
    dance3move = false;
  }
  else {
    Astepper1.move(20);
    Astepper2.move(20);
    dance3move = true;
  }
  isRunning = true;
}


void dance4() {
  Astepper1.setMaxSpeed(100.0);
  Astepper1.setAcceleration(500.0);
  Astepper2.setMaxSpeed(100.0);
  Astepper2.setAcceleration(500.0);
  if (dance4move) {
    Astepper1.move(10);
    Astepper2.move(10);
    dance4move = false;
  }
  else {
    Astepper1.move(-10);
    Astepper2.move(-10);
    dance4move = true;
  }
  isRunning = true;
}

void dance5() {
  Astepper1.setMaxSpeed(300.0);
  Astepper1.setAcceleration(500.0);
  Astepper2.setMaxSpeed(300.0);
  Astepper2.setAcceleration(500.0);
  if (dance5move) {
    Astepper1.move(1);
    Astepper2.move(-1);
    dance5move = false;
  }
  else {
    Astepper1.move(-1);
    Astepper2.move(1);
    dance5move = true;
  }
  isRunning = true;
}

