// Analyzer.h

#ifndef _ANALYZER_h
#define _ANALYZER_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif
class Analyzer
{
public:
    Analyzer();
    void onoff();
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
    ApproximationData getApproxData();
    AnalyzedData getAnalyzeData();

    boolean updateMemory();
    void initSensorData();
    void initApproximationData();
    bool startApproximation;
private:
    int _pin;
};

#endif

