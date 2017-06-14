#ifndef SERVOCONTROLLER_H
#define SERVOCONTROLLER_H

#include <Arduino.h>
#include <Servo.h>

class ServoController {
  public:
    ServoController() ;
    void dropBall();

  private:
    const int m_openAngle = 30;
    const int m_loadAngle = 0;
    const int m_closedAngle = 20;
    const int m_pinNumber = 9;
	  const int m_dropDelay = 500;
    Servo m_servo;
};
#endif
