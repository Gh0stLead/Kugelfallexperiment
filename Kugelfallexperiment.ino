#include "Analyzer.h"
#include <Servo.h>


Servo servo;
analyser a;

int geschwindigkeit = 0;
unsigned long lastTime;
int lastFlank = 0;
bool triggered = false;
unsigned long lastHall;
int hallsensor_old_val = 0;
int fallTime = 500; //in ms
int bisFallDauer = fallTime;
int letzteRundeZeitButton;
int drehDauer;

void setup() {
    
    //analyser a;//= new analyser();
    a.getTriggered();
    //setTime(0,0,0,0,0,0);
    //Photosensor
    pinMode(2, INPUT);
    //hallsensor
    pinMode(3, INPUT);
    //trigger (1 if pressed)
    pinMode(4, INPUT);
    //switch
    pinMode(5, INPUT);
    //servo
    pinMode(9, OUTPUT);
    //LED gruen
    pinMode(13, OUTPUT);
    //LED gelb
    pinMode(12, OUTPUT);


    //attach Pin to servo class
    servo.attach(9);

    Serial.begin(9600);
    lastTime = 0;
    servo.write(20);
}

void loop() {
    int photosensor_val = digitalRead(2);
    int hallsensor_val = digitalRead(3);
    int trigger_val = digitalRead(4);
    int switch_val = digitalRead(5);

    if (hallsensor_val == 1)
    {
        digitalWrite(13, HIGH);
    }
    else
    {
        digitalWrite(13, LOW);
    }

    if (trigger_val == 1 && !triggered) {
        triggered = true;
        letzteRundeZeitButton = millis();
        //load the ball
        servo.write(0);
        int deltaLastHall = millis() - lastHall;
        fallTime = (550 + drehDauer - deltaLastHall) % drehDauer;
        bisFallDauer = fallTime;
    }

    if (hallsensor_old_val == 1 && hallsensor_val == 0) {
        lastHall = millis();
        //Serial.println(hallsensor_old_val);
        //Serial.print(hallsensor_val);
        //Serial.println(lastHall);
    }

    if (triggered && (bisFallDauer > 0))
    {
        int rundeZeitButton = millis();
        bisFallDauer -= (rundeZeitButton - letzteRundeZeitButton);
        letzteRundeZeitButton = rundeZeitButton;
        if (bisFallDauer <= 0)
        {
            triggered = false;
            bisFallDauer = fallTime;
            servo.write(20);
            
        }
    }


    //Serial.println(hallsensor_val);
    if (photosensor_val != lastFlank)
    {
        geschwindigkeit = millis() - lastTime;
        lastTime = millis();
        lastFlank = photosensor_val;
        //erial.println(hallsensor_val);
        //Serial.print(" ; ");
        //Serial.println(photosensor_val);
        drehDauer = geschwindigkeit * 12;
        Serial.println(drehDauer);
        
    }
    //Serial.print(geschwindigkeit);   // turn the LED on (HIGH is the voltage level)
    //Serial.print(" ");
    //Serial.print(" ; ");
    //Serial.println(photosensor_val);
    //Serial.println(millis());
    //Serial.println(servo.read());


    delay(5);              // wait for a second
    hallsensor_old_val = hallsensor_val;
}