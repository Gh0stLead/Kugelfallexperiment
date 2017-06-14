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
    Serial.println(getSegmentTime());
    isStable();
    //Serial.print(getSegmentTime());
    //Serial.println(",");
  }
  m_lastValue = m_currentValue;
}

void PhotoSensorReader::addToSavedData(unsigned long value) {

  for (int index = 0; index < m_savedDataSize - 1; index++) {
    m_savedData[index] = m_savedData[index + 1]; //shift the values one to the left to make place for the new value: FIFO
  }
  //Set the last element to the current timestamp
  m_savedData[m_savedDataSize - 1] = millis();

  if (m_savedDataIndex < m_savedDataSize) {
    m_savedDataIndex++;//increment the index if the array is not full yet
  }

  //Add new difference to the differences array
  //Shift one to the left
  for (int index = 0; index < m_savedDataSize - 2; index++) {
    m_savedDataDifferences[index] = m_savedDataDifferences[index + 1];
  }
  //TODO Eventually chech already here for instability
  m_savedDataDifferences[m_savedDataSize - 2] = m_savedData[m_savedDataSize - 1] - m_savedData[m_savedDataSize - 2];

  //DEBUG
  //printSavedData();
}

void PhotoSensorReader::resetMemory() {

  //Reset saved data array
  for (int index = 0; index < m_savedDataSize; index++) {
    m_savedData[index] = 0;
  }

  //Reset saved differences
  for (int index = 0; index < m_savedDataSize - 1; index++) {
    m_savedDataDifferences[index] = 0;
  }

  m_savedDataIndex = 0;
}

//TOODOO: make function return false if speed is to low or to high
bool PhotoSensorReader::isPlateSpeedAsRequired() {
  unsigned long currentSpeed = getSegmentTime() * 12;
  bool tooSlow = m_lowerSpeedLimit < currentSpeed;
  bool tooFast = currentSpeed < m_upperSpeedLimit;

  if (tooSlow){
    
    Serial.println("Too Slow");
    return false;
  }

  if (tooFast){
    
    Serial.println("Too fast");
    return false;
  }

  return true;
}

//TODOO
bool PhotoSensorReader::isSystemStable() {
  if (m_instableCount > 2)
    return false;
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

  Serial.print("Saved differences: [ ");
  for (int index = 0; index < m_savedDataSize - 2; index++) {
    Serial.print(m_savedDataDifferences[index]);
    Serial.print(", ");
  }
  Serial.print(m_savedDataDifferences[m_savedDataSize - 2]);
  Serial.println(" ] ");
}

void PhotoSensorReader::isStable() {
  unsigned long averageSpeed = 0;
  for (int i = 0; i < 3; i++)
  {
    averageSpeed += m_savedData[i];
  }
  averageSpeed /= 3;
  /*Serial.print("m_savedDataDifferences[m_savedDataSize-2] : ");
    Serial.print((float)m_savedDataDifferences[m_savedDataSize-2]);
    Serial.print("m_savedDataDifferences[0] : ");
    Serial.println((float)m_savedDataDifferences[0]);*/
  float ratio = ((float)(m_savedDataDifferences[m_savedDataSize - 2] + m_savedDataDifferences[m_savedDataSize - 3])) / ((float)(m_savedDataDifferences[0] + m_savedDataDifferences[1]));
  //Serial.print(ratio);
  if ((ratio < 1.2f) && (0.9f < ratio))
  {
  //  Serial.println(" stable");
    m_instableCount = 0;
  } else {
  //  Serial.println(" instable ");
    m_instableCount++;
    //Serial.println(m_instableCount);
  }

}


