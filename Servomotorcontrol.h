// Servomotor.h

#ifndef _SERVOMOTORCONTROL_h
#define _SERVOMOTORCONTROL_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
    #include "Servo.h"
#else
	#include "WProgram.h"
#endif
class ServoMotorControl
{
public:
    ServoMotorControl();
    void initialize();
    void dropball();
private:
    int PIN = 9;
    Servo TheServo;
    void intendedDelay(unsigned long time);
    ///TODO: Here could be the Servo PIN be added instead of in MAIN
};

#endif

