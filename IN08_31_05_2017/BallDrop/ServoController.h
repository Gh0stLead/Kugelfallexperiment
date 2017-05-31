#ifndef SERVOCONTROLLER_H
#define SERVOCONTROLLER_H

#include <Arduino.h>
#include <Servo.h>

class ServoController {
  public:
    ServoController() ;
    void dropBall();

  private:
    const int openAngle = 25;
    const int closedAngle = 0;
    const int pinNumber = 9;
    Servo m_servo;
};
#endif
