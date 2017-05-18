// 
// 
// 

#include "SensorManager.h"
#include "TestButtonReader.h"

void SensorManager::fetchSensorValues()
{
}

SensorManager::SensorManager() {
    initialize();
}

void SensorManager::initialize() {
    
    /*SensorReader photoSensorReader;
    SensorReader hallSensorReader;
    SensorReader triggerReader;
    SensorReader normalButtonReader;
    SensorReader testButtonReader;*/
    
    auto testButtonReader = new TestButtonReader();
}
