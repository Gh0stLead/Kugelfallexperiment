#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

#include "ExecutionTypeManager.h"
#include "TestExecutor.h"
#include "TriggerReader.h"
#include "ServoController.h"
#include "Analyzer.h"
#include "HallSensorReader.h"
#include "PhotoSensorReader.h"


/**
   The main controller is responsible for the event handling.
   It includes a state machine.
*/

class MainController {
  public:

    MainController();
    void eventLoop();
    enum State {IDLE, TEST, ANALYZE, DROP_BALL};

  private:
    /**
       Memeber variables
    */
    const int m_delayMillis = 5;

    State m_currentState;

    PhotoSensorReader* m_photoSensorReader;
    HallSensorReader* m_hallSensorReader;
    ExecutionTypeManager* m_executionTypeManager;
    TestExecutor* m_testExecutor;
    TriggerReader* m_triggerReader;
    Analyzer* m_analyzer;
    ServoController* m_servoController;

    const int m_greenLED_pin = 12;
    const int m_yellowLED_pin = 13;
    bool m_debugging = true;
    bool m_testExecution = false;

    /**
       Private methods
    */
    void setState(State state);
};

#endif
