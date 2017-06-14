#ifndef TESTEXECUTOR_H
#define TESTEXECUTOR_H

#include "PhotoSensorReader.h"
#include "HallSensorReader.h"

class TestExecutor {
  public:
    //Setup
    TestExecutor();

    void testLoop();

  private:
    PhotoSensorReader* m_photoSensorReader;
    HallSensorReader* m_hallSensorReader;
    int m_currentPhotoSensorValue;
    int m_currentHallSensorValue;
};

#endif
