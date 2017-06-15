#include "Analyzer.h"
//constructor of the Analyzer
Analyzer::Analyzer(PhotoSensorReader* photoSensorReader, HallSensorReader* hallSensorReader) {
    m_photoSensorReader = photoSensorReader;
    m_hallSensorReader = hallSensorReader;
}
//main worker method is called continuely in the eventloop
void Analyzer::analyzeSystem() {

    //check if system is stable
    m_systemStable = m_photoSensorReader->isSystemStable();

    //predict when ball should be dropped
    //lastTimestamp + 12 * timePer30degree - m_ballDropTimeDelay

    m_dropTimestamp = calculateTimeToWait();
}
//releases the ball when true 
bool Analyzer::prepareToDrop() {
    //when estiamted drop time is reached and system is stable
    if ((m_dropTimestamp < millis()) && m_systemStable) {
        //   Serial.println("DEBUG: ANALYZER: m_dropTimestamp < millis() is true");
        return true;
    }  
    //check if system is stable runs in dropball state
    m_systemStable = m_photoSensorReader->isSystemStable();
    return false;
}
//calculates the time till the hole is beneath the target again
unsigned long Analyzer::getTimeTillNextHole()
{
    //get the timestamp from the time the hole was detected
    unsigned long lastHole = m_hallSensorReader->getLastHoleAboveTargetTimestamp();
    //calculate the next predicted time the hole will be there on the current speed
    Serial.println(m_photoSensorReader->getSegmentTime());
    return lastHole + m_photoSensorReader->getSegmentTime() * 12;
}
//this is were the magic happens
//TODO make sure our magic spell is correct
unsigned long Analyzer::calculateTimeToWait()
{
    //time when the hole will beneath the target again
    unsigned long timeTillHole = getTimeTillNextHole();
    //speed of one segment (means the average of six datas)
    unsigned long currentSpeed = m_photoSensorReader->getSegmentTime();
    //how long to wait till releasae
    unsigned long timeToWait = 0;
    
    
    long addFactor = 0;
    if (currentSpeed < 34)
    {
        timeToWait = timeTillHole - m_ballDropTimeDelay + currentSpeed * 12 / 12.13;
    }
    else if ((currentSpeed >= 34) && (currentSpeed < 50)) {
        timeToWait = timeTillHole - m_ballDropTimeDelay + currentSpeed * 12 / 16.01;
    }
    else if ((currentSpeed >= 50) && (currentSpeed < 75)) {
        timeToWait = timeTillHole - m_ballDropTimeDelay + currentSpeed * 12 / 18.05;
    }
    else
    {
        timeToWait = timeTillHole - m_ballDropTimeDelay + currentSpeed * 12 / 19; //+ currentSpeed;
    }    
    /*
      Serial.println(timeToWait);
      Serial.println(" Analyzer::calculateTimeToWait");
      Serial.println(timeTillHole);
      Serial.println(currentSpeed);
      Serial.println(timeToWait);
      Serial.println( millis());
      Serial.println("while:");*/
    //when estimated waiting time is smaller than current time
    while (timeToWait < millis())
    {
        //add time for one rotation
        timeToWait += currentSpeed * 12 + currentSpeed * addFactor;
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


