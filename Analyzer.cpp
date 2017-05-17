// 
// 
// 
#include "Arduino.h"
#include "Analyzer.h"

Analyzer::Analyzer()
{
    pinMode(LED_BUILTIN, OUTPUT);
    _pin = LED_BUILTIN;
}

void Analyzer::onoff()
{
    digitalWrite(_pin, HIGH);
    delay(1000);
    digitalWrite(_pin, LOW);
    delay(1000);    
}
