// ExecutionTypeManager.h

#ifndef _EXECUTIONTYPEMANAGER_h
#define _EXECUTIONTYPEMANAGER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
class ExecutionTypeManager
{
public:
    ExecutionTypeManager();
    void receiveTestButtonSignal();
    void receiveNormalButtonSignal();
};
#endif

