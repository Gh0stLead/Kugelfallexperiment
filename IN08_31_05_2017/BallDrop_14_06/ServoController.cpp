#include "ServoController.h"

ServoController::ServoController() {
  m_servo.attach(m_pinNumber);
  m_servo.write(m_closedAngle);
}

void ServoController::dropBall() {
  Serial.println("DEBUG: ServoController: dropBall called ");

  m_servo.write(m_openAngle);
  delay(m_dropDelay);
  m_servo.write(m_loadAngle);
  delay(m_dropDelay);
  m_servo.write(m_closedAngle);
}


