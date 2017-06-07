#include "PhotoSensorReader.h"

PhotoSensorReader::PhotoSensorReader() {
  pinMode(m_pinNumber, INPUT);
  resetMemory();
}

bool PhotoSensorReader::isDataAvailable() {
  //check if the index is at the end of the array
  return m_savedDataIndex == m_savedDataSize;
}

void PhotoSensorReader::readSensor() {
  int m_currentValue = digitalRead(m_pinNumber);
  if (m_currentValue != m_lastValue) {
    addToSavedData(millis());
  }
  m_lastValue = m_currentValue;
}

void PhotoSensorReader::addToSavedData(unsigned long value) {

  for (int index = 0; index < m_savedDataSize - 1; index++) {
    m_savedData[index] = m_savedData[index + 1]; //shift the values one to the left to make place for the new value: FIFO
  }

  m_savedData[m_savedDataSize - 1] = millis();

  if (m_savedDataIndex < m_savedDataSize) {
    m_savedDataIndex++;
  }

  //DEBUG
  // printSavedData();
}

void PhotoSensorReader::resetMemory() {

  for (int index = 0; index < m_savedDataSize; index++) {
    m_savedData[index] = 0;
  }

  m_savedDataIndex = 0;
}

//TOODOO: make function return false if speed is to low or to high
bool PhotoSensorReader::isPlateSpeedAsRequired() {
  unsigned long currentSpeed = getSegmentTime();
  return m_lowerSpeedLimit < currentSpeed < m_upperSpeedLimit;
}

//TODOO
bool PhotoSensorReader::isSystemStable() {
  return true;
}

unsigned long PhotoSensorReader::getSegmentTime() {
  int numberOfValuesForAverage = 3;
  unsigned long sum = 0;
  for (int index = 0; index < numberOfValuesForAverage; index++) {
    sum += m_savedData[m_savedDataIndex - index - 1] - m_savedData[m_savedDataIndex - index - 2];
  }
  unsigned long segmentTime = sum / numberOfValuesForAverage;
  m_lastSpeed = segmentTime;
  return sum / numberOfValuesForAverage;
}

/*
  REGION: Help functions for debugging
*/
void PhotoSensorReader::printCurrentValue() {
  Serial.print("DEBUG: PHOTOSENSOR: Current value is: ");
  Serial.println(m_currentValue);
}

void PhotoSensorReader::printSavedData() {
  Serial.print("Saved data: [ ");
  for (int index = 0; index < m_savedDataSize - 1; index++) {
    Serial.print(m_savedData[index]);
    Serial.print(", ");
  }
  Serial.print(m_savedData[m_savedDataSize - 1]);
  Serial.println(" ] ");
  Serial.print("Saved data index ");
  Serial.print(m_savedDataIndex);
  Serial.println();
  Serial.print("Array size ");
  Serial.print(m_savedDataSize);
  Serial.println();
}

