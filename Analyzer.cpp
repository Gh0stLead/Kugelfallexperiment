// 
// 
// 
#include "Arduino.h"
#include "Analyzer.h"
#include "StabilityChecker.h"

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

AnalyzedData* SensorData;
ApproximationData* ApproximatedData;
StabilityChecker* Stabilizer;
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
    switch (SensorData->status)
    {
    case INIT:
        if (Photo_Value != SensorData->PhotoValues[SensorData->PhotoLastIndex].value)
        {
            addNewPhotoValue();
            NewPhotoValue = true;
        }
        if ((SensorData->PhotoCount > 0) && (Hall_Value != SensorData->HallValue.value))
        {
            SensorData->HallValue.time = Millis_Value;
            SensorData->HallValue.value = Hall_Value;
            SensorData->PhotoCount = 0;
            SensorData->status = Analyzer::COLLECT_DATA;
        }
        break;
    case COLLECT_DATA:
        if (Hall_Value != SensorData->HallValue.value)
        {
            SensorData->HallValue.time = Millis_Value;
            SensorData->HallValue.value = Hall_Value;
        }
        if (Photo_Value != SensorData->PhotoValues[SensorData->PhotoLastIndex].value)
        {
            addNewPhotoValue();
            SensorData->status = READY;
            digitalWrite(13, HIGH);
            NewPhotoValue = true;
        }
        break;
    case READY:
        if (Photo_Value != SensorData->PhotoValues[SensorData->PhotoLastIndex].value)
        {
            addNewPhotoValue();
            NewPhotoValue = true;
        }
        if (Hall_Value != SensorData->HallValue.value)
        {
            SensorData->HallValue.time = Millis_Value;
            SensorData->HallValue.value = Hall_Value;
            SensorData->PhotoCount = 0;
            SensorData->status = COLLECT_DATA;
            digitalWrite(13, LOW);
        }
        break;
    default:
        break;
    }
    return NewPhotoValue;
}

void Analyzer::initSensorData()
{
    SensorData->status = INIT;
    SensorData->PhotoLastIndex = MaximumNumbersOfPhotoValues - 1;
    SensorData->PhotoCount = 0;
    SensorData->PhotoTotalCount = 0;
    digitalWrite(13, LOW);
    for (int i = 0; i < 13; i++) {
        SensorData->PhotoValues[i].time = 0;
        SensorData->PhotoValues[i].value = -1;
    }
    SensorData->HallValue.time = millis();
    SensorData->HallValue.value = digitalRead(3);
}

void Analyzer::initApproximationData()
{
    ApproximatedData->isValid = false;
    ApproximatedData->time = 0;
    ApproximatedData->nextDropTime = 0;
    startApproximation = true;
}

void Analyzer::addNewPhotoValue()
{
    SensorData->PhotoLastIndex = (SensorData->PhotoLastIndex + 1) % MaximumNumbersOfPhotoValues;
    SensorData->PhotoValues[SensorData->PhotoLastIndex].time = Millis_Value;
    SensorData->PhotoValues[SensorData->PhotoLastIndex].value = Photo_Value;
    SensorData->PhotoCount++;
    SensorData->PhotoTotalCount++;
}

void Analyzer::approximate()
{
}

void Analyzer::readInputs()
{
    Trigger_Value = digitalRead(4);
    Millis_Value = millis();
    Photo_Value = digitalRead(2);
    Hall_Value = digitalRead(3);    
    
}

void Analyzer::CalcDropTime()
{
    int timeDelay;
        if (ApproximatedData->velocity < 400.0)
        {
            timeDelay = 391;
        }
        else
        {
            timeDelay = 499;
        }
        unsigned long n = (12 - (ApproximatedData->angle + 15) / 30) % 12;
        unsigned long tmin, current = millis();
        do
        {
            tmin = ApproximatedData->time + n * ApproximatedData->velocity + ApproximatedData->velocity / 2 + (n * (n + 1)) / 2 * ApproximatedData->acceleration;
            n += 12;
        } while (tmin < current + timeDelay);
        ApproximatedData->nextDropTime = tmin - timeDelay;
}

boolean Analyzer::busyWaitForDrop()
{
    unsigned long current;
        while (true)
        {
            current = millis();
            if (current >= ApproximatedData->nextDropTime)
            {
                // Abwurfzeitpunkt erreicht
                return true;
            }
            readInputs();
            if (updateMemory())
            {
                // neue Approximation aufgrund neuer Sensorwerte
                approximate();
                if (!ApproximatedData->isValid)
                {
                    return false;
                }
                CalcDropTime();
            }
            else
            {
                //if (!Stabilizer->validateSpeedUp())
                if (!validateSpeedUp())
                {
                    // der tatsächliche quot-Wert des aktuellen Abschnittes kann nur größer sein
                    // plötzlicher Stopp innerhalb eines 30°-Segmentes wird erkannt
                    ApproximatedData->isValid = false;
                    digitalWrite(12, LOW);
                    return false;
                }
            }
        }
}

boolean Analyzer::validateSpeedUp()                                                                           
{
    float t1, t2, quot;
    t2 = (float)millis() - (float)SensorData->PhotoValues[SensorData->PhotoLastIndex].time;
    t1 = (float)SensorData->PhotoValues[SensorData->PhotoLastIndex].time - (float)SensorData->PhotoValues[(SensorData->PhotoLastIndex + 13 - 1) % 13].time;
    quot = t2 / t1;
    return quot <= 1.5;
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
