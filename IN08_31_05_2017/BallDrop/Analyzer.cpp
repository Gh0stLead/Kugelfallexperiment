#include "Analyzer.h"

Analyzer::Analyzer(PhotoSensorReader* photoSensorReader, HallSensorReader* hallSensorReader) {
  m_photoSensorReader = photoSensorReader;
  m_hallSensorReader = hallSensorReader;
}

void Analyzer::analyzeSystem() {
  // Serial.println("DEBUG: ANALYZER: analyzeSystem called");
  //get the holes position from the hallsensor
  m_lastHoleAboveTargetTimestamp = m_hallSensorReader->getLastHoleAboveTargetTimestamp();

  //check if system is stable
  m_systemStable = m_photoSensorReader->isSystemStable();

  //predict when ball should be dropped
  //lastTimestamp + 12 * timePer30degree - m_ballDropTimeDelay

  m_dropTimestamp =  calculateTimeToWait();
}

bool Analyzer::prepareToDrop() {
 /* Serial.println("DEBUG: ANALYZER: prepareToDrop called");
  Serial.println(m_dropTimestamp);
  Serial.println(millis());*/
  if (m_dropTimestamp < millis() && m_systemStable) {
    //   Serial.println("DEBUG: ANALYZER: m_dropTimestamp < millis() is true");
    return true;
  }
  //get the holes position from the hallsensor
  m_lastHoleAboveTargetTimestamp = m_hallSensorReader->getLastHoleAboveTargetTimestamp();

  //check if system is stable
  m_systemStable = m_photoSensorReader->isSystemStable();
  return false;
}

unsigned long Analyzer::getTimeTillNextHole() //wird wahrscheinlich ausgelagert. Gibt die Zeit an, bis wieder ein Loch kommt
{
  unsigned long lastHole = m_hallSensorReader->getLastHoleAboveTargetTimestamp();
  //Serial.println("getCurrentSpeed");
  //Serial.println(getCurrentSpeed());
  return lastHole + getCurrentSpeed() * 12;
}

unsigned long Analyzer::getCurrentSpeed() // Sollte von PhotoSensorReader gegeben werden
{
  return m_photoSensorReader->getSegmentTime();
}


unsigned long Analyzer::calculateTimeToWait()
{
  unsigned long timeTillHole = getTimeTillNextHole();
  unsigned long currentSpeed = getCurrentSpeed();
  long addFactor = 0;
  if(currentSpeed > 100)
  {
    addFactor = 50;
  }
  unsigned long timeToWait = timeTillHole - m_ballDropTimeDelay + addFactor; //+ currentSpeed;

  Serial.println(currentSpeed);
/*
  Serial.println(" Analyzer::calculateTimeToWait");
  Serial.println(timeTillHole);
  Serial.println(currentSpeed);
  Serial.println(timeToWait);
  Serial.println( millis());
  Serial.println("while:");*/
  while (timeToWait < millis())
  {
    timeToWait += currentSpeed * 12;
    //Serial.println(timeToWait);
  }

  //hier einfügen die zusätzliche Zeit zur Abbremsung
  return timeToWait;
  /*unsigned long timePerRound = getCurrentSpeed() * 12;

  // The calculated time per round gets classified into one of six ranges. 
  // For each range the pre delay gets calculated with a
  // different factor or doesnt get calculated at all, if the time per round
  // is to low or to high. 

  unsigned long preDelay;
  unsigned long DROPTIME = m_ballDropTimeDelay;
  // high speed
  if (timePerRound < 440) {
    preDelay = (timePerRound - (DROPTIME%timePerRound)) + timePerRound / 2 + timePerRound / 12.13;

    //Serial.println("high speed");
  }


  // mid speed
  else if (timePerRound >= 440 && timePerRound < 600) {
    preDelay = (timePerRound - (DROPTIME%timePerRound)) + timePerRound / 2 + timePerRound / 16.01;

    //Serial.println("mid speed");
  }

  // slow speed
  else if (timePerRound >= 600 && timePerRound < 900) {
    preDelay = (timePerRound - (DROPTIME%timePerRound)) + timePerRound / 2 + timePerRound / 18.5;

    //Serial.println("low speed");
  }

  // ultra slow speed 

  else {
    preDelay = (timePerRound - (DROPTIME%timePerRound)) + timePerRound / 2 + timePerRound / 19;

    //Serial.println("ultra low speed");
  }
  return m_hallSensorReader->getLastHoleAboveTargetTimestamp()+preDelay;*/
}


