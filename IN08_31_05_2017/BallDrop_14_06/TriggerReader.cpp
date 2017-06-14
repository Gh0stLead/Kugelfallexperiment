#include "TriggerReader.h"
 
//constructor of the TriggerReader
TriggerReader::TriggerReader() {
  pinMode(m_pinNumber, INPUT);
}

//read the sensor
int TriggerReader::readSensor() {
    //read the current value from the sensor (always)
	m_currentValue = digitalRead(m_pinNumber);
    //the button was released and the current time is bigger than the last pressed timestand plus a treshold
	if (wasPressedAndReleased() && (millis() > (m_lastTimestamp + m_threshold))) {
		//set timestamp for latest press
        m_lastTimestamp = millis();
        //increment trigger count
		incrementTriggers();
	}
    //set the current value to the old value for comparison in next loop
	m_oldValue = m_currentValue;
}
//decrement triggercount (happens when a ball is released)
void TriggerReader::decrementTriggers() {
	if (m_triggersToProcess > 0)
		m_triggersToProcess--;
}
//getter function for getting trigger count
int TriggerReader::getNumberOfTriggers() {
	return m_triggersToProcess;
}
//detect the trigger button was pushed (with some extra features)
bool TriggerReader::wasPressedAndReleased() {
    //detects the falling flank(releasing) of the button
	if (m_oldValue == 1 && m_currentValue == 0) {
		return true;
	}
	return false;
}
//increment the trigger count
void TriggerReader::incrementTriggers() {
	if (m_triggersToProcess < m_triggersLimit)
		m_triggersToProcess++;
}



