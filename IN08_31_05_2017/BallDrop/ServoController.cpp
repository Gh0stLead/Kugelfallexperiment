#include "ServoController.h"

ServoController::ServoController() {
  m_servo.attach(pinNumber);
  m_servo.write(closedAngle);
}

void ServoController::dropBall() {
  Serial.println("DEBUG: ServoController: dropBall called ");

  m_servo.write(openAngle);
  delay(500);


  m_servo.write(closedAngle);
}


