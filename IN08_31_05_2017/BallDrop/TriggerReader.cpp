#include "TriggerReader.h"

TriggerReader::TriggerReader() {

}

int TriggerReader::readSensor() {
  m_currentValue = digitalRead(m_pinNumber);
  //Serial.println(m_currentValue);
  if (checkIfPressed() && millis() > (m_lastTimestamp + m_threshold)) {
  // Serial.println("Trigger pressed");
    m_lastTimestamp = millis();
    incrementTriggers();
  }
  m_oldValue = m_currentValue;
  //Serial.println(triggersToPocess);
}

void TriggerReader::decrementTriggers() {
  if (triggersToPocess > 0)
    triggersToPocess--;
}

int TriggerReader::getNumberOfTriggers() {
  //Serial.println("DEBUG: TRIGGERREADER: getNumberOfTriggers: ");
  // Serial.println(triggersToPocess);
  return triggersToPocess;
}

bool TriggerReader::checkIfPressed() {
  if (m_oldValue == 0 && m_currentValue == 1) {
    return true;
  }
  return false;
}

void TriggerReader::incrementTriggers() {
  if (triggersToPocess < triggersLimit)
    triggersToPocess++;
}



