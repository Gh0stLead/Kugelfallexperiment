#include "ServoController.h"
//constructor of the ServoController
ServoController::ServoController() {
    //attach the servo instance to pin of the servo
    m_servo.attach(m_pinNumber);
    //bring the servo in closed position
    m_servo.write(m_closedAngle);
}
//use the servo to drop the ball
void ServoController::dropBall() {
    Serial.println("DEBUG: ServoController: dropBall called ");
    //release ball
    m_servo.write(m_openAngle);
    delay(m_dropDelay);
    //back to zero for loading the next ball
    m_servo.write(m_loadAngle);
    delay(m_dropDelay);
    //go in position for dropping the next ball
    m_servo.write(m_closedAngle);
}


