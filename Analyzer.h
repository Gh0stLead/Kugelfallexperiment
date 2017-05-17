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
private:
    int _pin;
};

#endif

