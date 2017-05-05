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
    int hallsensor;
    int photosensor;
    int trigger_val;
    int switchposition;
    bool triggered;
    bool getTriggered();
};

#endif

