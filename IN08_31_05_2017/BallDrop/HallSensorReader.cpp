#include "HallSensorReader.h"

HallSensorReader::HallSensorReader() {
  pinMode(m_pinNumber, INPUT);
}

unsigned long HallSensorReader::getLastHoleAboveTargetTimestamp() {
  //Serial.println("DEBUG: HallSensorReader: getLastHoleAboveTargetTimestamp: ");
 // Serial.println(m_lastHoleAboveTargetTimestamp);
  return m_lastHoleAboveTargetTimestamp;
}

int HallSensorReader::readSensor() {
  m_currentData = digitalRead(m_pinNumber);

  //hole under target
  if (m_lastData== 1 && m_currentData == 0) {
    m_lastHoleAboveTargetTimestamp = millis();
  }

  m_lastData = m_currentData;

  
  return m_currentData;
}

