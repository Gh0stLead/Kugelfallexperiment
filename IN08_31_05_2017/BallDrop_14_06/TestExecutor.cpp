#include "TestExecutor.h"

TestExecutor::TestExecutor() {
  m_photoSensorReader = new PhotoSensorReader();
  m_hallSensorReader = new HallSensorReader();
}

void  TestExecutor::testLoop() {
  //m_currentPhotoSensorValue = m_photoSensorReader->readSensor();
 // m_currentHallSensorValue = m_hallSensorReader->readSensor();
  Serial.print("Photosensor value: ");
  Serial.print( m_currentPhotoSensorValue);
  Serial.print( "; Hallsensor value: ");
  Serial.print( m_currentHallSensorValue);
  Serial.println();
}

