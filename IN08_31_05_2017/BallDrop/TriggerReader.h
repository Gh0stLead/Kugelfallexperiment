#ifndef TRIGGERREADER_H
#define TRIGGERREADER_H

#include <Arduino.h>

class TriggerReader {
  public:
    TriggerReader();

    int readSensor() ;

    void decrementTriggers() ;

    int getNumberOfTriggers();

  private:
    const int m_pinNumber = 4;
    const int triggersLimit = 10;
    int m_currentValue = -1;
    int m_oldValue = -1;
    unsigned long m_lastTimestamp = 0;
    unsigned long m_threshold = 200;
    int triggersToPocess = 0;

    bool checkIfPressed();

    void incrementTriggers() ;

};

#endif
