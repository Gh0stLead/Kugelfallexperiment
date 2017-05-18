// SensorManager.h

#ifndef _SENSORMANAGER_h
#define _SENSORMANAGER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
    #include "SensorReader.h"
#else
	#include "WProgram.h"
#endif
class SensorManager {
private:
    SensorReader photoSensorReader;
    SensorReader hallSensorReader;
    SensorReader triggerReader;
    SensorReader normalButtonReader;
    SensorReader testButtonReader;
    void initialize();
public:
    void fetchSensorValues();
    SensorManager();
};

#endif

