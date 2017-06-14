#include "TriggerReader.h"

TriggerReader::TriggerReader() {
  pinMode(m_pinNumber, INPUT);
}

int TriggerReader::readSensor() {
	m_currentValue = digitalRead(m_pinNumber);
	if (wasPressed() && (millis() > (m_lastTimestamp + m_threshold))) {
		m_lastTimestamp = millis();
		incrementTriggers();
    //Serial.println("Trigger pressed");
    //Serial.println(getNumberOfTriggers());
	}
	m_oldValue = m_currentValue;
}

void TriggerReader::decrementTriggers() {
	if (m_triggersToPocess > 0)
		m_triggersToPocess--;
}

int TriggerReader::getNumberOfTriggers() {
	return m_triggersToPocess;
}

bool TriggerReader::wasPressed() {
	if (m_oldValue == 1 && m_currentValue == 0) {
		return true;
	}
	return false;
}

void TriggerReader::incrementTriggers() {
	if (m_triggersToPocess < m_triggersLimit)
		m_triggersToPocess++;
}



