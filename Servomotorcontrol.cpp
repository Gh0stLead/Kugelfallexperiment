// 
// 
// 

#include "Servomotorcontrol.h"
#include "Arduino.h"
#include "Servo.h"

ServoMotorControl::ServoMotorControl()
{
    pinMode(PIN, OUTPUT);
    Servo TheServo;
}

void ServoMotorControl::initialize()
{
    TheServo.attach(PIN);//attach the Servoclass to the PIN
    TheServo.write(0);//set motor in start position
    delay(100);
    TheServo.write(15);//set motor in better position
}

void ServoMotorControl::dropball()
{
    if (TheServo.read() != 15)
        TheServo.write(15);
    for (int pos = 15; pos < 20; pos++)
    {
        TheServo.write(pos);        
    }


}

void ServoMotorControl::intendedDelay(unsigned long time)
{
    unsigned long waitUntil = millis() + time;
    while (millis() < waitUntil)
    {
       //readInputs();
        //updatememory();
    }
}
