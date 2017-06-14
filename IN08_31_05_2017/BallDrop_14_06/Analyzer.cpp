#include "Analyzer.h"

Analyzer::Analyzer(PhotoSensorReader* photoSensorReader, HallSensorReader* hallSensorReader) {
  m_photoSensorReader = photoSensorReader;
  m_hallSensorReader = hallSensorReader;
}

void Analyzer::analyzeSystem() {
  // Serial.println("DEBUG: ANALYZER: analyzeSystem called");

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
  if ((m_dropTimestamp < millis()) && m_systemStable) {
    //   Serial.println("DEBUG: ANALYZER: m_dropTimestamp < millis() is true");
    return true;
  }

  //check if system is stable
  m_systemStable = m_photoSensorReader->isSystemStable();
  return false;
}

unsigned long Analyzer::getTimeTillNextHole() //wird wahrscheinlich ausgelagert. Gibt die Zeit an, bis wieder ein Loch kommt
{
  unsigned long lastHole = m_hallSensorReader->getLastHoleAboveTargetTimestamp();
  //Serial.println("getCurrentSpeed");
  return lastHole + m_photoSensorReader->getSegmentTime() * 12;
}

unsigned long Analyzer::calculateTimeToWait()
{
  unsigned long timeTillHole = getTimeTillNextHole();
  unsigned long currentSpeed = m_photoSensorReader->getSegmentTime();
  unsigned long timeToWait = 0;
  long addFactor = 0;
  if (currentSpeed < 34)
  {
    timeToWait = timeTillHole - m_ballDropTimeDelay + currentSpeed * 12 / 12.13;
  }
  else if ((currentSpeed >= 34) && (currentSpeed < 50)) {
    timeToWait = timeTillHole - m_ballDropTimeDelay + currentSpeed * 12 / 16.01;
  } else if ((currentSpeed >= 50) && (currentSpeed < 75)) {
    timeToWait = timeTillHole - m_ballDropTimeDelay + currentSpeed * 12 / 18.05;
  } else
  {
    timeToWait = timeTillHole - m_ballDropTimeDelay + currentSpeed * 12 / 19; //+ currentSpeed;
  }

  //Serial.println(timeToWait);
  /*
    Serial.println(" Analyzer::calculateTimeToWait");
    Serial.println(timeTillHole);
    Serial.println(currentSpeed);
    Serial.println(timeToWait);
    Serial.println( millis());
    Serial.println("while:");*/
  while (timeToWait < millis())
  {
    timeToWait += currentSpeed * 12 + currentSpeed * addFactor;
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


