#include "PhotoSensorReader.h"

PhotoSensorReader::PhotoSensorReader() {
  Serial.println("Photosensor constructor");
  pinMode(m_pinNumber, INPUT);
  m_savedDataIndex = 0;
}

bool PhotoSensorReader::isDataAvailable(int dataSize) {
  //check if the current index is bigger than the requested data
  return m_savedDataIndex > dataSize - 1;
}

void PhotoSensorReader::readSensor() {
  //SensorData currentData = {digitalRead(m_pinNumber), millis()};
  int m_currentValue = digitalRead(m_pinNumber);
  if (m_currentValue != m_lastValue) {
    addToSavedData(millis());
  }
  //Serial.println("DEBUG: PHOTOSENSORREADER: Photosensor readSensor method called");
  // Serial.println("DEBUG: PHOTOSENSORREADER: CurrentValue | LastValue | SavedDataIndex | millis ");
  // Serial.println(m_currentValue);
  // Serial.println(m_lastValue);
  // Serial.println(m_savedDataIndex);
  //Serial.println(millis());
  m_lastValue = m_currentValue;
}

void PhotoSensorReader::addToSavedData(unsigned long value) {
  //if queue is already full
  if (m_savedDataIndex == (sizeof(m_savedData) / sizeof(unsigned long)) - 1) {
    for (int index = 0; index < m_savedDataIndex; index++) {
      m_savedData[index] = m_savedData[index + 1]; //shift the values one to the left to make place for the new value: FIFO
    }
    /*Serial.println("Adding data to index:");
      Serial.println(millis());
      Serial.println(m_savedDataIndex);*/
    m_savedData[m_savedDataIndex] = millis();
  }
  else {
    /*  Serial.println("Queue is not full");
      Serial.println("Adding data to index:");
      Serial.println(millis());
      Serial.println(m_savedDataIndex);*/
    m_savedData[m_savedDataIndex++] = millis();
  }
}

void PhotoSensorReader::resetMemory() {
  m_savedDataIndex = 0;
}

//TOODOO: make function return false is speed is to low
bool PhotoSensorReader::isPlateSpeedAsRequired() {

  unsigned long currentSpeed = getPlateSpeed();
  // Serial.println("DEBUG: PHOTOSENSORREADER : isPlateSpeedAsRequired");
  Serial.println(currentSpeed);
  // Serial.println(m_lowerSpeedLimit < currentSpeed < m_upperSpeedLimit);
  return m_lowerSpeedLimit < currentSpeed < m_upperSpeedLimit;
}

//TODOO
bool PhotoSensorReader::isSystemStable() {
  return true;
}

//int PhotoSensorReader::getLastValues(SensorData arrayOfLastValues[]) {
//  int sizeOfArray =  (sizeof(arrayOfLastValues)/sizeof(int));
//  for (int index = 0; index < sizeOfArray ; index ++) {
///    arrayOfLastValues[index] = m_savedData[m_savedDataIndex - index];
// }
//  return arrayOfLastValues;
//}

unsigned long PhotoSensorReader::getPlateSpeed() {
  int numberOfValuesForAverage = 3;
  unsigned long sum = 0;
  /*Serial.println("sum : ");*/
  for (int index = 0; index < numberOfValuesForAverage; index++) {
    sum += m_savedData[m_savedDataIndex - index - 1] - m_savedData[m_savedDataIndex - index - 2];
    /*  Serial.print(m_savedData[m_savedDataIndex - index - 1]);
      Serial.print(" at index ");
      Serial.println(m_savedDataIndex - index - 1);
      Serial.println("-");
      Serial.println(m_savedData[m_savedDataIndex - index - 2]);
      Serial.println("=");
      Serial.println(m_savedData[m_savedDataIndex - index - 1] - m_savedData[m_savedDataIndex - index - 2]);*/
  }
  //Serial.println("PhotoSensorReader::getPlateSpeed()");
  //Serial.println(m_savedDataIndex);
  //Serial.println(sum / numberOfValuesForAverage);
  unsigned long segmentTime = sum / numberOfValuesForAverage;
  m_lastSpeed = segmentTime;
  return sum / numberOfValuesForAverage;
}

