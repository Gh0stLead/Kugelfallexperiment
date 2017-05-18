// TestButtonReader.h

#ifndef _TESTBUTTONREADER_h
#define _TESTBUTTONREADER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#include "SensorReader.h"

class TestButtonReader : public SensorReader {
public:
    TestButtonReader();
    void readSensor();
    void notifyObservers();

private:
    const int pinNumber = 10;
    int currentValue;
    void initialize();

};

#endif

