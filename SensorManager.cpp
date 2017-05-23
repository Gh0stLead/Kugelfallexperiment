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

void SensorManager::readInputs()
{
    Value_Millis = millis();
    Value_Trigger = digitalRead(PIN_Trigger);
    Value_Photo = digitalRead(PIN_Photo);
    Value_Hall = digitalRead(PIN_Hall);
}
