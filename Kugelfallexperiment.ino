/*
Kugelfallexperimentimplementierung by
@author Christian Kühn
@author Isabella Szen
@author Tobias Roth
*/

#include "ExecutionTypeManager.h"
#include "SensorReader.h"
#include "TestButtonReader.h"
#include "SensorManager.h"
#include "MainController.h"
#include "Servomotorcontrol.h"
#include "Analyzer.h"
#include <Servo.h>

//using const instead of #define, cause compiler likes that more
///Pin numbers for buttons and sensors
const int PIN_PhotoSensor = 2;
const int PIN_HallSensor = 3;
const int PIN_TriggerButton = 4; ///fires endless 1 when pressed
const int PIN_BlackBoxSwitch = 5;
const int PIN_ServoMotor = 9;
const int PIN_ButtonFront = 10;
const int PIN_ButtonBack = 11;
///Pin numbers for LEDs
const int PIN_LED_Yellow = 12;
const int PIN_LED_Green = 13 || LED_BUILTIN;
///Constants needed in the program
const int MAX_NumberPhotoValues = 13;
const float velocityTreshold = 400.0;
const int timeDelaySlowMode = 391;
const int timeDelayFastMode = 391 + 100 + 8;

MainController* mainController;
 
/*ServoMotorControl servo;
Analyzer analyse
//int geschwindigkeit = 0;
//unsigned long lastTime;
//int lastFlank = 0;
//bool triggered = false;
//unsigned long lastHall;
//int hallsensor_old_val = 0;
//int fallTime = 500; //in ms
//int bisFallDauer = fallTime;
//int letzteRundeZeitButton;
//int drehDauer; */


void setup() {
    //Initialize pins
    //Photosensor
    pinMode(PIN_PhotoSensor, INPUT);
    //Hallsensor
    pinMode(PIN_HallSensor, INPUT);
    //trigger (1 if pressed)
    pinMode(PIN_TriggerButton, INPUT);
    //switch
    pinMode(PIN_BlackBoxSwitch, INPUT);
    //Button Front
    pinMode(PIN_ButtonFront, INPUT);
    //Button Back
    pinMode(PIN_ButtonBack, INPUT);
    //servo
    pinMode(PIN_ServoMotor, OUTPUT);
    //LED gruen
    pinMode(PIN_LED_Yellow, OUTPUT);
    //LED gelb
    pinMode(PIN_LED_Green, OUTPUT);

    mainController = new MainController();
}

void loop() 
{
    mainController->eventLoop(); 
    //analyse.onoff();      
    //int photosensor_val = digitalRead(2);
    //int hallsensor_val = digitalRead(3);
    //int trigger_val = digitalRead(4);
    //int switch_val = digitalRead(5); 
    //if (hallsensor_val == 1)
    //{
    //    digitalWrite(13, HIGH);
    //}
    //else
    //{
    //    digitalWrite(13, LOW);     
    //}
    //if (trigger_val == 1 && !triggered) {
    //    triggered = true;
    //    letzteRundeZeitButton = millis();
    //    //load the ball
    //    servo.write(0);
    //    int deltaLastHall = millis() - lastHall;
    //    fallTime = (550 + drehDauer - deltaLastHall) % drehDauer;
    //    bisFallDauer = fallTime;
    //}                                   
    //if (hallsensor_old_val == 1 && hallsensor_val == 0) {
    //    lastHall = millis();
    //    //Serial.println(hallsensor_old_val);
    //    //Serial.print(hallsensor_val);
    //    //Serial.println(lastHall);
    //} 
    //if (triggered && (bisFallDauer > 0))
    //{
    //    int rundeZeitButton = millis();
    //    bisFallDauer -= (rundeZeitButton - letzteRundeZeitButton);
    //    letzteRundeZeitButton = rundeZeitButton;
    //    if (bisFallDauer <= 0)
    //    {
    //        triggered = false;
    //        bisFallDauer = fallTime;
    //        servo.write(20);
    //        
    //    }
    //} 
    ////Serial.println(hallsensor_val);
    //if (photosensor_val != lastFlank)
    //{
    //    geschwindigkeit = millis() - lastTime;
    //    lastTime = millis();
    //    lastFlank = photosensor_val;
    //    //erial.println(hallsensor_val);
    //    //Serial.print(" ; ");
    //    //Serial.println(photosensor_val);
    //    drehDauer = geschwindigkeit * 12;
    //    Serial.println(drehDauer);
    //    
    //}
    ////Serial.print(geschwindigkeit);   // turn the LED on (HIGH is the voltage level)
    ////Serial.print(" ");
    ////Serial.print(" ; ");
    ////Serial.println(photosensor_val);
    ////Serial.println(millis());
    ////Serial.println(servo.read()); 
    //delay(5);              // wait for a second
    //hallsensor_old_val = hallsensor_val;
}