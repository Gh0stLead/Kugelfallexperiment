#include "MainController.h"

MainController::MainController() {

  Serial.begin(9600);

  pinMode(m_greenLED_pin, OUTPUT);
  pinMode(m_yellowLED_pin , OUTPUT);

  m_photoSensorReader = new PhotoSensorReader();
  m_hallSensorReader = new HallSensorReader();
  m_executionTypeManager = new ExecutionTypeManager();
  m_testExecutor = new TestExecutor();
  m_triggerReader = new TriggerReader();
  m_servoController = new ServoController();
  m_analyzer = new Analyzer(m_photoSensorReader, m_hallSensorReader);

  //Set default state
  setState(IDLE);
}

void MainController::eventLoop() {
  /**
     State machine
  */
  switch (m_currentState) {

    case IDLE:
      m_triggerReader->readSensor();
     
      //Read the photosensor values
      m_photoSensorReader->readSensor();


      //Ask the photosensor if data is available
      if (m_photoSensorReader->isDataAvailable()) {
        //  Serial.println("DEBUG: MAINCONTROLLER: State IDLE: Data is available");
        setState(ANALYZE);
      }
      break;

    case TEST:
      m_triggerReader->readSensor();
      m_testExecutor->testLoop();
      if (m_triggerReader->getNumberOfTriggers() > 0) {
        setState(DROP_BALL);
      }
      break;

    case ANALYZE:
      //Ask the photosensor if data is available
      if (!m_photoSensorReader->isDataAvailable() || !m_photoSensorReader->isPlateSpeedAsRequired()  || !m_photoSensorReader->isSystemStable()) {
        //If no data is available go back to idle
        setState(IDLE);
      }
      m_triggerReader->readSensor();
      m_photoSensorReader->readSensor();
      m_hallSensorReader->readSensor();
      m_analyzer->analyzeSystem();

      if (m_triggerReader->getNumberOfTriggers() > 0 && m_photoSensorReader->isPlateSpeedAsRequired() && m_photoSensorReader->isSystemStable()) {
        setState(DROP_BALL);
      }
      break;

    case DROP_BALL:

      if (m_analyzer->prepareToDrop()) {
        Serial.println("prepareToDrop true");
        //drop the ball
        m_servoController->dropBall();
        m_triggerReader->decrementTriggers();
     
        //after dropped go back to idle or test
        if (m_testExecution == true)
          setState(TEST);
        else {
          setState(IDLE);
        }
      } else {
        if ( !m_photoSensorReader->isPlateSpeedAsRequired() || !m_photoSensorReader->isSystemStable())
        {
          setState(IDLE);
        }
        //read sensors while waiting for the right moment to drop the ball
        m_hallSensorReader->readSensor();
        m_photoSensorReader->readSensor();
        m_triggerReader->readSensor();
      }
      break;

  }

  // Check if one of the execution buttons was pressed and set the corresponding state
  if (m_executionTypeManager->wasTestExecButtonPressed()) {
    setState(TEST);
    m_testExecution = true;
  } else if (m_executionTypeManager->wasNormalExecButtonPressed()) {
    setState(IDLE);
    m_testExecution = false;
  }

  delay(m_delayMillis);

}

void MainController::setState(State state) {
  if (m_debugging) {
    Serial.print("DEBUG: Maincontroller - Entering state: ");
    Serial.print(state);
    Serial.println();
  }
  m_currentState = state;

  //Light up your life
  if (m_currentState == IDLE) {
     m_photoSensorReader->resetMemory();
    digitalWrite(m_greenLED_pin, LOW);
    digitalWrite(m_yellowLED_pin, LOW);
  }
  else if (m_currentState == ANALYZE) {
    digitalWrite(m_greenLED_pin, HIGH);
    digitalWrite(m_yellowLED_pin, LOW);
  }
  else if (m_currentState == DROP_BALL) {
    digitalWrite(m_greenLED_pin, LOW);
    digitalWrite(m_yellowLED_pin, HIGH);
  }
}


//TODO: setDebugger(bool enabled) -- using the switch to enable the debugger


