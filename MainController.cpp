// 
// 
// 

#include "MainController.h"
#include "SensorManager.h"

#include <Arduino.h>

/*
* Implementation of the main controller
*/

bool debugging = false;    //only enabled in test mode
SensorManager* sensorManager;

/*
* Constructor of the main controller.
* Calls the initializer function.
*/
MainController::MainController() {
    if (debugging) {
        Serial.println(" Debug: MainController: Constructor called. ");
    }
    initialize();
}

/*
* The event loop represents the cental execution loop of the appication
*/
void MainController::eventLoop() {
    if (debugging) {
        Serial.println(" Debug: MainController: Event loop called. ");
    }
}

void MainController::startNormalExecution()
{
    //start normal execution functions
    debugging = false; //disable debugging
}

void MainController::startTestExecution()
{
    //start test mode for statistics
    debugging = true;
    
}

/*
* Initializes the serial port(used for debugging), the sensor manager
*/
void MainController::initialize() {
    Serial.begin(9600);
    sensorManager = new SensorManager();
}


