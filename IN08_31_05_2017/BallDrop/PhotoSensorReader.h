#ifndef PHOTOSENSORREADER_H
#define PHOTOSENSORREADER_H

#include <Arduino.h>
#include "SensorDataStruct.h"


class PhotoSensorReader {

public:
	PhotoSensorReader();

	bool isDataAvailable(int dataSize);

	bool isSystemStable();

	unsigned long getPlateSpeed();

	void readSensor();

	int getLastValues(int number);
	bool isPlateSpeedAsRequired();

	void addToSavedData(unsigned long value);
	void resetMemory();

private:
	const int m_pinNumber = 2;

	//Lower speed limit is 10 s/round = 10000 ms/round
	const unsigned long m_lowerSpeedLimit = 10000;
	//Upper speed limit is 3.5 rounds/seconds = 0.28571 s/round = 285.71 ms/round
	const unsigned long m_upperSpeedLimit = 285;

	const unsigned long m_speedOutOfSpecifiedIntervalThreshold = 3000;

	SensorData m_currentData;
	SensorData m_lastData;

	//Contains the last 15 values
   //SensorData m_savedData[1000];
	unsigned long m_savedData[15];
	int m_savedDataIndex;

	unsigned long m_lastSpeed;

	int m_currentValue = 0;
	int m_lastValue = 0;


};

#endif
