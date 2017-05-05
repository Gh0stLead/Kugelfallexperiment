#include <Servo.h>

//Servo used for ball drop
Servo servo;

void setup() 
{
  //Photosensor input
  pinMode(2, INPUT);
  //Hallsensor input
  pinMode(3, INPUT);
  //Trigger Input (1 if pressed)
  pinMode(4, INPUT);
  //Switch Input
  pinMode(5, INPUT);
  //Servo Output
  pinMode(9, OUTPUT);
  //LED green
  pinMode(13, OUTPUT);
  //LED yellow
  pinMode(12,OUTPUT);
 
  //Attach Pin to the servo
  servo.attach(9);

  //Initialize the serial monitor
  Serial.begin(9600);  
  servo.write(0);
}

void loop() 
{
  //Read the sensor values
  int photosensor_val = digitalRead(2);
  int hallsensor_val = digitalRead(3);
  int trigger_val = digitalRead(4);
  int switch_val = digitalRead(5);

  Serial.print("Photosensor: ");
  Serial.print(photosensor_val);
  Serial.print(" Hallsensor: ");
  Serial.print(hallsensor_val);
  Serial.print(" Trigger: ");
  Serial.print(trigger_val);
  Serial.println();
  
  if(trigger_val == 1)
  {
    servo.write(20);
  }
  else
  {
    servo.write(0);
  }
  
  delay(5);           

}
