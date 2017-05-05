#include <Servo.h>


Servo myservo;

//int pos = 0;
int geschwindigkeit = 0;
unsigned long lastTime;
int lastFlank = 0;

void setup() {
    //setTime(0,0,0,0,0,0);
    //Photosensor
    pinMode(2, INPUT);
    //hallsensor
    pinMode(3, INPUT);
    //trigger
    pinMode(4, INPUT);
    //switch
    pinMode(5, INPUT);
    //servo
    pinMode(9, OUTPUT);
    
    pinMode(LED_BUILTIN, OUTPUT);

    //attach Pin to servo class
    myservo.attach(9);

    Serial.begin(9600);
    lastTime = 0;
}

void loop() {
    int photosensor_val = digitalRead(2);
    int hallsensor_val = digitalRead(3);
    int trigger_val = digitalRead(4);
    int switch_val = digitalRead(5);

    digitalWrite(LED_BUILTIN, HIGH);
    delay(500);
    digitalWrite(LED_BUILTIN, LOW);
    delay(500);
    //if (trigger_val == 1) {
    //    //myservo
    //    //analogWrite(9, HIGH);
    //    myservo.write(0);
    //}
    //else {
    //    myservo.write(20);
    //}
    //if (photosensor_val != lastFlank)
    //{
    //    geschwindigkeit = millis() - lastTime;
    //    lastTime = millis();
    //    lastFlank = photosensor_val;

    //    Serial.println(geschwindigkeit);
    //    //Serial.print(" ; ");
    //    //Serial.println(photosensor_val);
    //}
    //Serial.print(geschwindigkeit);   // turn the LED on (HIGH is the voltage level)
    //Serial.print(" ");
    //Serial.print(" ; ");
    //Serial.println(photosensor_val);
    //Serial.println(millis());
    //Serial.println(myservo.read());


    delay(5);              // wait for a second

}
