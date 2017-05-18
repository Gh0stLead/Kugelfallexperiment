// 
// 
// 

#include "TestButtonReader.h"

TestButtonReader::TestButtonReader() {
    const int pinNumber = 10;
    initialize();
}

void TestButtonReader::readSensor() {
    currentValue = digitalRead(pinNumber);
}

void TestButtonReader::notifyObservers()
{
}

void TestButtonReader::initialize() {

}
