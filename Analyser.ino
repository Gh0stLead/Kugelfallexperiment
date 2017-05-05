class analyser
{
public://public field
    int hallsensor = 0;
    int photosensor = 0;
    int trigger_val = 0;
    int switchposition = 0;
    bool triggered = false;
    bool getTriggered();
private://private field
    int photosensor_pin_number= 2;
    int hallsensor_pin_number = 3;
    int trigger_pin_number = 4;
    int switch_pin_number = 5;
    void setup()
    {
        //Photosensor Pin
        pinMode(photosensor_pin_number, INPUT);
        //Hallsensor Pin
        pinMode(hallsensor_pin_number, INPUT);
        //Triggersensor(1 if pressed)
        pinMode(trigger_pin_number, INPUT);
        //Switch Pin
        pinMode(switch_pin_number, INPUT);
    }

    void loop()
    {
        photosensor = digitalRead(2);
        hallsensor = digitalRead(3);
        trigger_val = digitalRead(4);
        switchposition = digitalRead(5);

        if (trigger_val == 1)
            triggered = true;
    } 
};

bool analyser::getTriggered()
{
    return false;
}
