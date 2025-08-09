// Twisted-String Actuator Robot Dog
// By Khalid - August 2025

// ---------------- Pin Definitions ----------------

// Front-Left Motor
const int FL_IN1 = 2;
const int FL_IN2 = 3;
const int FL_PWM = 5;
const int FL_HOME = A0; // Limit switch

// Front-Right Motor
const int FR_IN1 = 4;
const int FR_IN2 = 7;
const int FR_PWM = 6;
const int FR_HOME = A1;

// Back-Left Motor
const int BL_IN1 = 8;
const int BL_IN2 = 9;
const int BL_PWM = 10;
const int BL_HOME = A2;

// Back-Right Motor
const int BR_IN1 = 11;
const int BR_IN2 = 12;
const int BR_PWM = 3;
const int BR_HOME = A3;

int pwmSpeed = 180; // Motor speed (0-255)

// Enum for motor identification
enum MotorId { FL = 0, FR = 1, BL = 2, BR = 3 };

void setup() {
  Serial.begin(9600);

  // Motor pins
  int motorPins[] = {
    FL_IN1, FL_IN2, FL_PWM,
    FR_IN1, FR_IN2, FR_PWM,
    BL_IN1, BL_IN2, BL_PWM,
    BR_IN1, BR_IN2, BR_PWM
  };

  for (int i = 0; i < 12; i++) {
    pinMode(motorPins[i], OUTPUT);
  }

  // Limit switches
  pinMode(FL_HOME, INPUT_PULLUP);
  pinMode(FR_HOME, INPUT_PULLUP);
  pinMode(BL_HOME, INPUT_PULLUP);
  pinMode(BR_HOME, INPUT_PULLUP);

  // Calibrate all actuators
  homeAll();
  delay(500);
}

void loop() {
  // Simple walking gait: move diagonal pairs
  stepDiagonalUp(FL, BR);
  delay(150);
  stepDiagonalDown(FL, BR);
  delay(200);

  stepDiagonalUp(FR, BL);
  delay(150);
  stepDiagonalDown(FR, BL);
  delay(200);
}

// ---------------- Motor Control Functions ----------------
void setMotor(int in1, int in2, int pwmPin, int dir, int speed) {
  if (dir > 0) { // Shorten string
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
  } else if (dir < 0) { // Lengthen string
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
  } else { // Stop
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
  }
  analogWrite(pwmPin, speed);
}

void stopMotorPins(int in1, int in2, int pwmPin) {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  analogWrite(pwmPin, 0);
}

void motorCommand(MotorId m, int dir, int speed) {
  switch (m) {
    case FL: setMotor(FL_IN1, FL_IN2, FL_PWM, dir, speed); break;
    case FR: setMotor(FR_IN1, FR_IN2, FR_PWM, dir, speed); break;
    case BL: setMotor(BL_IN1, BL_IN2, BL_PWM, dir, speed); break;
    case BR: setMotor(BR_IN1, BR_IN2, BR_PWM, dir, speed); break;
  }
}

void motorStop(MotorId m) {
  switch (m) {
    case FL: stopMotorPins(FL_IN1, FL_IN2, FL_PWM); break;
    case FR: stopMotorPins(FR_IN1, FR_IN2, FR_PWM); break;
    case BL: stopMotorPins(BL_IN1, BL_IN2, BL_PWM); break;
    case BR: stopMotorPins(BR_IN1, BR_IN2, BR_PWM); break;
  }
}

// ---------------- Homing Routine ----------------
void homeAll() {
  Serial.println("Homing all actuators...");

  bool homed[4] = {false, false, false, false};
  unsigned long start = millis();

  while (!(homed[0] && homed[1] && homed[2] && homed[3]) && millis() - start < 8000) {
    if (!homed[0]) {
      if (digitalRead(FL_HOME) == LOW) { homed[0] = true; motorStop(FL); }
      else motorCommand(FL, 1, 100);
    }
    if (!homed[1]) {
      if (digitalRead(FR_HOME) == LOW) { homed[1] = true; motorStop(FR); }
      else motorCommand(FR, 1, 100);
    }
    if (!homed[2]) {
      if (digitalRead(BL_HOME) == LOW) { homed[2] = true; motorStop(BL); }
      else motorCommand(BL, 1, 100);
    }
    if (!homed[3]) {
      if (digitalRead(BR_HOME) == LOW) { homed[3] = true; motorStop(BR); }
      else motorCommand(BR, 1, 100);
    }
  }

  // Stop all motors after homing
  motorStop(FL); motorStop(FR); motorStop(BL); motorStop(BR);
  Serial.println("Homing done.");
  delay(200);
}

// ---------------- Gait Functions ----------------
void stepDiagonalUp(MotorId a, MotorId b) {
  motorCommand(a, 1, pwmSpeed);
  motorCommand(b, 1, pwmSpeed);
  delay(350); // Adjust for your string/pulley
  motorStop(a);
  motorStop(b);
}

void stepDiagonalDown(MotorId a, MotorId b) {
  motorCommand(a, -1, pwmSpeed);
  motorCommand(b, -1, pwmSpeed);
  delay(350);
  motorStop(a);
  motorStop(b);
}