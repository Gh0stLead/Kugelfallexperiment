#ifndef EXECUTIONTYPEMANAGER_H
#define EXECUTIONTYPEMANAGER_H

#include <Arduino.h>

class ExecutionTypeManager {

  public:
    ExecutionTypeManager();

    bool wasTestExecButtonPressed() ;
    bool wasNormalExecButtonPressed();

  private:
    /**
       Constants
    */
    const int m_normalExecButtonPinNumber = 10;
    const int m_testExecButtonPinNumber = 11;
    const unsigned long m_pressThreshold = 3000; //after pushing a button a new press is only detected after 3 seconds

    unsigned long m_lastPressTimestamp;
    unsigned long m_currentTimestamp;
    int m_currentTestExecButtonValue;
    int m_lastTestExecButtonValue;
    int m_currentNormalExecButtonValue;
    int m_lastNormalExecButtonValue;
};

#endif

