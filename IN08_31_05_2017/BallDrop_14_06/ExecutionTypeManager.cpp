#include "ExecutionTypeManager.h"

ExecutionTypeManager::ExecutionTypeManager() {
  pinMode(m_normalExecButtonPinNumber, INPUT);
  pinMode(m_testExecButtonPinNumber, INPUT);
}

bool ExecutionTypeManager::wasTestExecButtonPressed() {
  m_currentTimestamp = millis();
  m_currentTestExecButtonValue = digitalRead(m_testExecButtonPinNumber);
  if ((m_currentTimestamp - m_lastPressTimestamp) > m_pressThreshold) {
    if (m_lastTestExecButtonValue == 0 && m_currentTestExecButtonValue == 1) {
      m_lastPressTimestamp = millis();
      return true;
    }
  }
  m_lastTestExecButtonValue = m_currentTestExecButtonValue;
  return false;
}

bool ExecutionTypeManager::wasNormalExecButtonPressed() {
  m_currentTimestamp = millis();
  m_currentNormalExecButtonValue = digitalRead(m_normalExecButtonPinNumber);
  if ((m_currentTimestamp - m_lastPressTimestamp) > m_pressThreshold) {
    if (m_lastNormalExecButtonValue == 0 && m_currentNormalExecButtonValue == 1) {
      m_lastPressTimestamp = millis();
      return true;
    }
  }
  m_lastNormalExecButtonValue = m_currentNormalExecButtonValue;
  return false;
}

