// MainController.h

#ifndef _MAINCONTROLLER_h
#define _MAINCONTROLLER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
class MainController
{
private:
    void initialize();
public:
    void eventLoop();
    void startNormalExecution();
    void startTestExecution();
    MainController();
};

#endif

