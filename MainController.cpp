// 
// 
// 

#include "MainController.h"
#include "SensorManager.h"
#include "Analyzer.h"

#include <Arduino.h>

/*
* Implementation of the main controller
*/

bool debugging = false;    //only enabled in test mode
SensorManager* sensorManager;
Analyzer analyse;

enum ControllerStatus
{
    IDLE,
    APPROXIAMTION,
    ESTIMATED_DROPTIME
};

ControllerStatus ActualControllerStatus;

/*
* Constructor of the main controller.
* Calls the initializer function.
*/
MainController::MainController() {
    if (debugging) 
    {
        Serial.println(" Debug: MainController: Constructor called. ");
    }
    initialize();
}

/*
* The event loop represents the cental execution loop of the appication
*/
void MainController::eventLoop() {
    if (debugging) 
    {
        Serial.println(" Debug: MainController: Event loop called. ");
    }
    readInputs();//TODO This method used for gathering the data for the analyzer
    //so move it there
    boolean NewValueArrived = updateMemory();//TODO where to?
    switch (ActualControllerStatus)
    {
    case IDLE:
        if (true)//when the trigger button gets smashed
        {
            ActualControllerStatus = APPROXIAMTION;
            analyse.startApproximation = true;
        }
        else
        {
            break;
        }
        break;
    case APPROXIAMTION:
        if (analyse.getAnalyzeData().status = READY)
        {
            if (analyse.startApproximation || NewValueArrived)
            {
                analyse.approximate();
            }   
            if (analyse.getApproxData().isValid)
            {
                ActualControllerStatus = ESTIMATED_DROPTIME;
            }
            else
            {
                break;
            }
        }
        break;
    case ESTIMATED_DROPTIME:
        analyse.CalcDropTime();

        if (analyse.busyWaitForDrop())
        {
            Serial.println(analyse.getApproxData().velocity);
            ActualControllerStatus = IDLE;
        }
        else
        {
            ActualControllerStatus = APPROXIAMTION;
            analyse.startApproximation = true;
        }
        break;
    default:
        break;
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


