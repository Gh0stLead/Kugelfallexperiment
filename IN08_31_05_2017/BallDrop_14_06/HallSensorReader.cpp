#include "HallSensorReader.h"

HallSensorReader::HallSensorReader() {
    //set pinmode
    pinMode(m_pinNumber, INPUT);
}

unsigned long HallSensorReader::getLastHoleAboveTargetTimestamp() {
    //Serial.println("DEBUG: HallSensorReader: getLastHoleAboveTargetTimestamp: ");
   // Serial.println(m_lastHoleAboveTargetTimestamp);
    return m_lastHoleAboveTargetTimestamp;
}

int HallSensorReader::readSensor() {
    m_currentData = digitalRead(m_pinNumber);

    //recognize flank so the hole is under target
    if (m_lastData == 1 && m_currentData == 0) {
        //set time stamp
        m_lastHoleAboveTargetTimestamp = millis();
    }
    //in the next loop current data will be last data
    m_lastData = m_currentData;

    return m_currentData;
}

