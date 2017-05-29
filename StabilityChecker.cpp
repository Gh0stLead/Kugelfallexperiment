// 
// 
// 

#include "StabilityChecker.h"
#include "Analyzer.h"   

Analyzer* analyseclass;

StabilityChecker::StabilityChecker()
{
}


boolean StabilityChecker::validateSpeedUp(Analyzer::AnalyzedData)
{
    return boolean();
}

boolean StabilityChecker::validateSpeedUp(Analyzer::AnalyzedData)
{
    float t1, t2, quotient;
    //t2 = (float)millis() - (float)DefaultMemory.PhotoValue[DefaultMemory.PhotoLastIndex].time;
    //t2 = (float)millis() - (float)DefaultMemory.PhotoValue[DefaultMemory.PhotoLastIndex].time;
    //    t1 = (float)DefaultMemory.PhotoValue[DefaultMemory.PhotoLastIndex].time - (float)DefaultMemory.PhotoValue[(DefaultMemory.PhotoLastIndex + MaximumNumberPhotoValues - 1) % MaximumNumberPhotoValues].time;
    t2 = (float)millis() - (float)13;    //TODO
    t1 =        //TODO
    quotient = t2 / t1;
    return quotient <= 1.5;
}