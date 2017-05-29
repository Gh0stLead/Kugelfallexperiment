// StabilityChecker.h

#ifndef _STABILITYCHECKER_h
#define _STABILITYCHECKER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
    #include "Analyzer.h"
#else
	#include "WProgram.h"
#endif
class StabilityChecker
{
public:
    StabilityChecker();
    boolean validateSpeedUp(Analyzer::AnalyzedData);    
};

#endif

