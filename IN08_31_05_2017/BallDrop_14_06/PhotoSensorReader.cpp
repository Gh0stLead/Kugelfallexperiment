#include "PhotoSensorReader.h"

//constructor of the PhotoSensorReader
PhotoSensorReader::PhotoSensorReader() {
    pinMode(m_pinNumber, INPUT);
    //initializes the array with zeros
    resetMemory();
}
//returns true if the data array is filled with values
bool PhotoSensorReader::isDataAvailable() {
    //check if the index is at the end of the array
    return m_savedDataIndex == m_savedDataSize;
}
//read in the PhotoSensor values into different arrays (continuely reading)
void PhotoSensorReader::readSensor() {
    //set pinmode
    int m_currentValue = digitalRead(m_pinNumber);
    //add value only if flank raises or falls
    if (m_currentValue != m_lastValue) {
        //add time stamp to saved data array
        addToSavedData(millis());
        Serial.println(getSegmentTime());
        isStable();     //TODO why do we do this here?
    }
    //current value will be last value in the next loop
    m_lastValue = m_currentValue;
}
//add the time stamp to the saved data array
void PhotoSensorReader::addToSavedData(unsigned long value) {
    //implementing a FIFO data structure
    for (int index = 0; index < m_savedDataSize - 1; index++) {
        m_savedData[index] = m_savedData[index + 1]; //shift the values one to the left to make place for the new value: FIFO
    }
    //TODO why not unsing the first place of the array or shifting from left to right
    //are 
    //Set the last element to the current timestamp
    m_savedData[m_savedDataSize - 1] = millis();

    if (m_savedDataIndex < m_savedDataSize) {
        m_savedDataIndex++;//increment the index if the array is not full yet
    }

    //Add new difference to the differences array
    //Shift one to the left
    for (int index = 0; index < m_savedDataSize - 2; index++) {
        m_savedDataDifferences[index] = m_savedDataDifferences[index + 1];
    }
    //TODO Eventually chech already here for instability
    m_savedDataDifferences[m_savedDataSize - 2] = m_savedData[m_savedDataSize - 1] - m_savedData[m_savedDataSize - 2];

    //DEBUG
    //printSavedData();
}
//reset all arrays and indices
void PhotoSensorReader::resetMemory() {

    //Reset saved data array
    for (int index = 0; index < m_savedDataSize; index++) {
        m_savedData[index] = 0;
    }

    //Reset saved differences
    for (int index = 0; index < m_savedDataSize - 1; index++) {
        m_savedDataDifferences[index] = 0;
    }
    //reset array pointer
    m_savedDataIndex = 0;
}

//TODO: make function return false if speed is to low or to high
bool PhotoSensorReader::isPlateSpeedAsRequired() {
    //calculate current RoundTime based on the last SegmentTime
    unsigned long currentRoundTime = getSegmentTime() * 12;
    //false if plate is to slow
    bool tooSlow = m_lowerSpeedLimit < currentRoundTime;
    //false if plate is to fast
    bool tooFast = currentRoundTime < m_upperSpeedLimit;

    if (tooSlow) { 
        Serial.println("Too Slow");
        return false;
    }
    else if (tooFast) { 
        Serial.println("Too fast");
        return false;
    }
    return true;
}
//returns false when the system is instable
bool PhotoSensorReader::isSystemStable() {
    //so when its 3
    if (m_instableCount > 2)
        return false;
    return true;
}
//calculates the Segmenttime of the last segment of the PhotoSensor
//TODO tought this method should work otherwise like in the description not the last six values
unsigned long PhotoSensorReader::getSegmentTime() {
    int numberOfValuesForAverage = 6;
    unsigned long sum = 0;
    //build the sum of the last six values in the data array
    for (int index = 0; index < numberOfValuesForAverage; index++) {
        sum += m_savedData[m_savedDataIndex - index - 1] - m_savedData[m_savedDataIndex - index - 2];
    }
    //calculate the average over six
    unsigned long segmentTime = sum / numberOfValuesForAverage;
    //for comparison in the next loop
    m_lastSpeed = segmentTime;
    return segmentTime;
}

/*
  REGION: Help functions for debugging
*/
void PhotoSensorReader::printCurrentValue() {
    Serial.print("DEBUG: PHOTOSENSOR: Current value is: ");
    Serial.println(m_currentValue);
}

void PhotoSensorReader::printSavedData() {
    Serial.print("Saved data: [ ");
    for (int index = 0; index < m_savedDataSize - 1; index++) {
        Serial.print(m_savedData[index]);
        Serial.print(", ");
    }
    Serial.print(m_savedData[m_savedDataSize - 1]);
    Serial.println(" ] ");
    Serial.print("Saved data index ");
    Serial.print(m_savedDataIndex);
    Serial.println();
    Serial.print("Array size ");
    Serial.print(m_savedDataSize);
    Serial.println();

    Serial.print("Saved differences: [ ");
    for (int index = 0; index < m_savedDataSize - 2; index++) {
        Serial.print(m_savedDataDifferences[index]);
        Serial.print(", ");
    }
    Serial.print(m_savedDataDifferences[m_savedDataSize - 2]);
    Serial.println(" ] ");
}
//see if the rotation is stable
void PhotoSensorReader::isStable() {
    unsigned long averageSpeed = 0;
    //calculate the average speed the last 3 data
    for (int i = 0; i < 3; i++)
    {
        averageSpeed += m_savedData[i];
    }
    averageSpeed /= 3;
    /*Serial.print("m_savedDataDifferences[m_savedDataSize-2] : ");
      Serial.print((float)m_savedDataDifferences[m_savedDataSize-2]);
      Serial.print("m_savedDataDifferences[0] : ");
      Serial.println((float)m_savedDataDifferences[0]);*/
    float ratio = ((float)(m_savedDataDifferences[m_savedDataSize - 2] + m_savedDataDifferences[m_savedDataSize - 3])) / ((float)(m_savedDataDifferences[0] + m_savedDataDifferences[1]));
    //Serial.print(ratio);
    if ((ratio < 1.2f) && (0.9f < ratio))
    {
        //  Serial.println(" stable");
        m_instableCount = 0;
    }
    else {
        //  Serial.println(" instable ");
        m_instableCount++;
        //Serial.println(m_instableCount);
    }

}


