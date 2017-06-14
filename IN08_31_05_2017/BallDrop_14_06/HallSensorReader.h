#ifndef HALLSENSOR_H
#define HALLSENSOR_H

#include <Arduino.h>
#include "SensorDataStruct.h"


class HallSensorReader {
  public:
    HallSensorReader();
    int readSensor();
    unsigned long getLastHoleAboveTargetTimestamp();

  private:
    const int m_pinNumber = 3;
    unsigned long m_lastHoleAboveTargetTimestamp;
    int m_currentData;
    int m_lastData;

};

#endif

