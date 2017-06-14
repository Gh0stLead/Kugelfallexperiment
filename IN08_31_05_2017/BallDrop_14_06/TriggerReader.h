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
    const int m_triggersLimit = 10;//limit of registered triggers
    int m_currentValue = -1;
    int m_oldValue = -1;
    unsigned long m_lastTimestamp = 0;//the timestamp of the last trigger press
    unsigned long m_threshold = 200; //ms between registered triggers
    int m_triggersToProcess = 0;

    bool wasPressedAndReleased(); 
    void incrementTriggers() ;

};

#endif
