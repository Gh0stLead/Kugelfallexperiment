// SensorReader.h

#ifndef _SENSORREADER_h
#define _SENSORREADER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
class SensorReader {
public:
    void readSensor();
    void notifyObservers();
protected:
    void initialize();
};
#endif

