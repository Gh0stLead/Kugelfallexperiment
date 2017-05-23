// 
// 
// 
#include "Arduino.h"
#include "Analyzer.h"

const int MaximumNumbersOfPhotoValues = 13;

enum MemoryStatus
{
    INIT,
    COLLECT_DATA,
    READY
};

struct TimeValue
{
    unsigned long time;
    int value;
};

struct AnalyzedData
{
    MemoryStatus status;
    int PhotoLastIndex;
    int PhotoCount;
    int PhotoTotalCount;
    TimeValue PhotoValues[MaximumNumbersOfPhotoValues];
    TimeValue HallValue;
};

struct ApproximationData
{
    bool isValid;
    float velocity;
    float acceleration;
    int angle;
    unsigned long time;
    unsigned long nextDropTime;
};

AnalyzedData SensorData;
ApproximationData ApproximatedData;
bool startApproximation;
int Trigger_Value;
int Photo_Value;
int Hall_Value;
unsigned long Millis_Value;

Analyzer::Analyzer()
{
    pinMode(LED_BUILTIN, OUTPUT);
    _pin = LED_BUILTIN;
}

boolean Analyzer::updateMemory()
{
    boolean NewPhotoValue = false;
    switch (SensorData.status)
    {
    case INIT:
        if (Photo_Value != SensorData.PhotoValues[SensorData.PhotoLastIndex].value)
        {
            addNewPhotoValue();
            NewPhotoValue = true;
        }
        if ((SensorData.PhotoCount > 0) && (Hall_Value != SensorData.HallValue.value))
        {
            SensorData.HallValue.time = Millis_Value;
            SensorData.HallValue.value = Hall_Value;
            SensorData.PhotoCount = 0;
            SensorData.status = COLLECT_DATA;
        }
        break;
    case COLLECT_DATA:
        if (Hall_Value != SensorData.HallValue.value)
        {
            SensorData.HallValue.time = Millis_Value;
            SensorData.HallValue.value = Hall_Value;
        }
        if (Photo_Value != SensorData.PhotoValues[SensorData.PhotoLastIndex].value)
        {
            addNewPhotoValue();
            SensorData.status = READY;
            digitalWrite(PIN_LED_Green, HIGH);
            NewPhotoValue = true;
        }
    case READY:
    default:
        break;
    }
    return boolean();
}

void Analyzer::initSensorData()
{
    SensorData.status = INIT;
    SensorData.PhotoLastIndex = MaximumNumbersOfPhotoValues - 1;
    SensorData.PhotoCount = 0;
    SensorData.PhotoTotalCount = 0;
    digitalWrite(PIN_LED_Green, LOW);
    for (int i = 0; i < MaximumNumberPhotoValues; i++) {
        SensorData.PhotoValues[i].time = 0;
        SensorData.PhotoValues[i].value = -1;
    }
    SensorData.HallValue.time = millis();
    SensorData.HallValue.value = digitalRead(PIN_Hall);
}

void Analyzer::initApproximationData()
{
    ApproximatedData.isValid = false;
    ApproximatedData.time = 0;
    ApproximatedData.nextDropTime = 0;
    startApproximation = true;
}



void Analyzer::onoff()
{
    digitalWrite(_pin, HIGH);
    delay(200);
    digitalWrite(_pin, LOW);
    delay(200);    
}

ApproximationData Analyzer::getApproxData()
{
    return ApproximationData();
}

AnalyzedData Analyzer::getAnalyzeData()
{
    return AnalyzedData();
}
