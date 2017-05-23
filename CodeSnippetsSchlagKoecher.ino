#include <Servo.h>

Servo TheServo;

const int MaximumNumberPhotoValues = 13;
const float VelocityTreshold = 400.0;
const int TimeDelaySlow = 391;
const int TimeDelayFast = 391 + 100 + 8;

const int PIN_Photo = 2;
const int PIN_Hall = 3;
const int PIN_Trigger = 4; ///fires endless 1 when pressed
const int PIN_BoxSwitch = 5;
const int PIN_Servo = 9;
const int PIN_BTNFront = 10;
const int PIN_BTNBack = 11;

int Value_Trigger = 0;
int Value_Photo = 0;
int Value_Hall = 0;
unsigned long Value_Millis = 0;
///State machine
//enum ControllerStates
//{
//    IDLE,
//    APPROXIMATION,
//    CALC_DROP_TIME
//};
///Analyzer
//enum MemoryStates
//{
//    INIT,
//    NOT_READY,
//    READY
//};
///Analyzer
//struct TimedValue
//{
//    unsigned long time;
//    int value;
//};
///Analyzer
//struct Memory
//{
//    MemoryStates state;
//    int PhotoLastIndex;
//    int PhotoCount;
//    int PhotoTotalCount;
//    TimedValue PhotoValue[MaximumNumberPhotoValues];
//    TimedValue HallValue;
//};
///Analyzer
//struct Approximator
//{
//    bool isValid;
//    float Velocity;
//    float Acceleration;
//    int Angle;
//    unsigned long Time;
//    unsigned long NextDropTime;
//};

//Memory DefaultMemory;
//Approximator DefaultApproximator;
//ControllerStates CurrentControllerState;
//
//bool doApproximation = true;
///MainController
//void setup()
//{
//    pinMode(PIN_Trigger, INPUT);
//    pinMode(PIN_Photo, INPUT);
//    pinMode(PIN_Hall, INPUT);
//    pinMode(PIN_BoxSwitch, INPUT);
//    pinMode(PIN_BTNFront, INPUT);
//    pinMode(PIN_BTNBack, INPUT);
//
//    pinMode(PIN_Servo, OUTPUT);
//    pinMode(PIN_LED_Yellow, OUTPUT);
//    pinMode(PIN_LED_Green, OUTPUT);
//
//    CurrentControllerState = IDLE;
//
//    initMemory();
//    initApproximator();
//
//    TheServo.attach(PIN_Servo);
//    TheServo.write(0);
//    delay(100);
//    TheServo.write(15);
//
//    Serial.begin(9600);
//    delay(100);
//}
///Analyzer
//void initMemory()
//{
//    DefaultMemory.state = INIT;
//    DefaultMemory.PhotoLastIndex = MaximumNumberPhotoValues - 1;
//    DefaultMemory.PhotoCount = 0;
//    DefaultMemory.PhotoTotalCount = 0;
//    digitalWrite(PIN_LED_Green, LOW);
//    for (int i = 0; i < MaximumNumberPhotoValues; i++) {
//        DefaultMemory.PhotoValue[i].time = 0;
//        DefaultMemory.PhotoValue[i].value = -1;
//    }
//    DefaultMemory.HallValue.time = millis();
//    DefaultMemory.HallValue.value = digitalRead(PIN_Hall);
//}
///Analyzer
//void initApproximator()
//{
//    DefaultApproximator.isValid = false;
//    DefaultApproximator.Time = 0;
//    DefaultApproximator.NextDropTime = 0;
//    doApproximation = true;
//}
 ///MainController
//void loop()
//{
//    readInputs();
//    boolean NewValue = updateMemory();
//    switch (CurrentControllerState)
//    {
//    case IDLE:
//        if (Value_Trigger == 1)
//        {
//            CurrentControllerState = APPROXIMATION;
//            doApproximation = true;
//        }
//        else
//        {
//            break;
//        }
//        break;
//    case APPROXIMATION:
//        if (DefaultMemory.state == READY)
//        {
//            if (doApproximation || NewValue)
//            {
//                approximate();
//            }
//            if (DefaultApproximator.isValid)
//            {
//                CurrentControllerState = CALC_DROP_TIME;
//            }
//            else
//            {
//                break;
//            }
//        }
//        else
//        {
//            break;
//        }
//        break;
//    case CALC_DROP_TIME:
//        CalcDropTime();
//
//        if (busyWaitForDrop())
//        {
//            Serial.println(DefaultApproximator.Velocity);
//            CurrentControllerState = IDLE;
//        }
//        else
//        {
//            CurrentControllerState = APPROXIMATION;
//            doApproximation = true;
//        }
//        break;
//    default:
//        break;
//    }
//}
///SensorManager
void readInputs()
{
    Value_Millis = millis();
    Value_Trigger = digitalRead(PIN_Trigger);
    Value_Photo = digitalRead(PIN_Photo);
    Value_Hall = digitalRead(PIN_Hall);
}
///Analyzer
boolean updateMemory()
{
    boolean NewPhotoValue = false;

    switch (DefaultMemory.state)
    {
    case INIT:
        if (Value_Photo != DefaultMemory.PhotoValue[DefaultMemory.PhotoLastIndex].value)
        {
            addPhotoValue();
            NewPhotoValue = true;
        }
        if ((DefaultMemory.PhotoCount > 0) && (Value_Hall != DefaultMemory.HallValue.value))
        {
            DefaultMemory.HallValue.time = Value_Millis;
            DefaultMemory.HallValue.value = Value_Hall;
            DefaultMemory.PhotoCount = 0;
            DefaultMemory.state = NOT_READY;
        }
        break;
    case NOT_READY:
        if (Value_Hall != DefaultMemory.HallValue.value)
        {
            DefaultMemory.HallValue.time = Value_Millis;
            DefaultMemory.HallValue.value = Value_Hall;
        }
        if (Value_Photo != DefaultMemory.PhotoValue[DefaultMemory.PhotoLastIndex].value) {
            addPhotoValue();
            DefaultMemory.state = READY;
            digitalWrite(PIN_LED_Green, HIGH);
            NewPhotoValue = true;
        }
        break;
    case READY:
        if (Value_Photo != DefaultMemory.PhotoValue[DefaultMemory.PhotoLastIndex].value)
        {
            addPhotoValue();
            NewPhotoValue = true;
        }
        if (Value_Hall != DefaultMemory.HallValue.value)
        {
            DefaultMemory.HallValue.time = Value_Millis;
            DefaultMemory.HallValue.value = Value_Hall;
            DefaultMemory.PhotoCount = 0;
            DefaultMemory.state = NOT_READY;
            digitalWrite(PIN_LED_Green, LOW);
        }
        break;
    }
    return NewPhotoValue;
}
///Analyzer
void addPhotoValue()
{
    DefaultMemory.PhotoLastIndex = (DefaultMemory.PhotoLastIndex + 1) % MaximumNumberPhotoValues;
    DefaultMemory.PhotoValue[DefaultMemory.PhotoLastIndex].time = Value_Millis;
    DefaultMemory.PhotoValue[DefaultMemory.PhotoLastIndex].value = Value_Photo;
    DefaultMemory.PhotoCount++;
    DefaultMemory.PhotoTotalCount++;
}
///Analyzer
void  approximate()
{
    if (DefaultMemory.PhotoTotalCount < MaximumNumberPhotoValues)
    {
        DefaultApproximator.isValid = false;
        digitalWrite(PIN_LED_Yellow, LOW);
        return;
    }

    if (!validateSpeedUp())
    {
        DefaultApproximator.isValid = false;
        digitalWrite(PIN_LED_Yellow, LOW);
        return;
    }

    float t1, t2, quot;
    t1 = (float)DefaultMemory.PhotoValue[DefaultMemory.PhotoLastIndex].time - (float)DefaultMemory.PhotoValue[(DefaultMemory.PhotoLastIndex + MaximumNumberPhotoValues - 1) % MaximumNumberPhotoValues].time;
    for (int i = 1; i < MaximumNumberPhotoValues - 1; i++)
    {
        t2 = t1;
        t1 = (float)DefaultMemory.PhotoValue[(DefaultMemory.PhotoLastIndex + MaximumNumberPhotoValues - i) % MaximumNumberPhotoValues].time - (float)DefaultMemory.PhotoValue[(DefaultMemory.PhotoLastIndex + MaximumNumberPhotoValues - i - 1) % MaximumNumberPhotoValues].time;
        quot = t2 / t1;
        if (quot < 0.5 || quot > 1.5)
        {
            DefaultApproximator.isValid = false;
            digitalWrite(PIN_LED_Yellow, LOW);
            return;
        }
    }

    DefaultApproximator.Angle = 15 + DefaultMemory.HallValue.value * 180 + (DefaultMemory.PhotoCount - 1) * 30;

    // Geschwindigkeit
    DefaultApproximator.Velocity = ((float)DefaultMemory.PhotoValue[DefaultMemory.PhotoLastIndex].time - (float)DefaultMemory.PhotoValue[(DefaultMemory.PhotoLastIndex + MaximumNumberPhotoValues - 12) % MaximumNumberPhotoValues].time) / 12.0;

    // Geschwindigkeit im gültigen Bereich?
    if (DefaultApproximator.Velocity < 20.83 || DefaultApproximator.Velocity > 833.33) {
        DefaultApproximator.isValid = false;
        digitalWrite(PIN_LED_Yellow, LOW);
        return;
    }

    // Verzögerung
    if (DefaultApproximator.Velocity < VelocityTreshold)
    {
        // Approximation bei schneller Drehung
        DefaultApproximator.Acceleration = ((float)DefaultMemory.PhotoValue[DefaultMemory.PhotoLastIndex].time - (float)DefaultMemory.PhotoValue[(DefaultMemory.PhotoLastIndex + MaximumNumberPhotoValues - 1) % MaximumNumberPhotoValues].time - (float)DefaultMemory.PhotoValue[(DefaultMemory.PhotoLastIndex + MaximumNumberPhotoValues - 11) % MaximumNumberPhotoValues].time + (float)DefaultMemory.PhotoValue[(DefaultMemory.PhotoLastIndex + MaximumNumberPhotoValues - 12) % MaximumNumberPhotoValues].time) / 11.0;
    }
    else
    {
        // Approximation bei langsamer Drehung
        DefaultApproximator.Acceleration = ((float)DefaultMemory.PhotoValue[DefaultMemory.PhotoLastIndex].time + (float)DefaultMemory.PhotoValue[(DefaultMemory.PhotoLastIndex + MaximumNumberPhotoValues - 2) % MaximumNumberPhotoValues].time - 2 * (float)DefaultMemory.PhotoValue[(DefaultMemory.PhotoLastIndex + MaximumNumberPhotoValues - 1) % MaximumNumberPhotoValues].time);
    }
    if (DefaultApproximator.Acceleration < 0)
    {
        DefaultApproximator.Acceleration = 0;
    }

    // fertig
    DefaultApproximator.Time = DefaultMemory.PhotoValue[DefaultMemory.PhotoLastIndex].time;
    DefaultApproximator.isValid = true;
    digitalWrite(PIN_LED_Yellow, HIGH);
    doApproximation = false;
}
///StabilityChercker
boolean validateSpeedUp()
{
    float t1, t2, quot;
    t2 = (float)millis() - (float)DefaultMemory.PhotoValue[DefaultMemory.PhotoLastIndex].time;
    t1 = (float)DefaultMemory.PhotoValue[DefaultMemory.PhotoLastIndex].time - (float)DefaultMemory.PhotoValue[(DefaultMemory.PhotoLastIndex + MaximumNumberPhotoValues - 1) % MaximumNumberPhotoValues].time;
    quot = t2 / t1;
    return quot <= 1.5;
}
///Analyzer
void CalcDropTime()
{
    int timeDelay;
    if (DefaultApproximator.Velocity < VelocityTreshold)
    {
        timeDelay = TimeDelayFast;
    }
    else
    {
        timeDelay = TimeDelaySlow;
    }
    unsigned long n = (12 - (DefaultApproximator.Angle + 15) / 30) % 12;
    unsigned long tmin, current = millis();
    do
    {
        tmin = DefaultApproximator.Time + n * DefaultApproximator.Velocity + DefaultApproximator.Velocity / 2 + (n * (n + 1)) / 2 * DefaultApproximator.Acceleration;
        n += 12;
    } while (tmin < current + timeDelay);
    DefaultApproximator.NextDropTime = tmin - timeDelay;
}
///Analyzer
boolean busyWaitForDrop()
{
    unsigned long current;
    while (true)
    {
        current = millis();
        if (current >= DefaultApproximator.NextDropTime)
        {
            // Abwurfzeitpunkt erreicht
            return true;
        }
        readInputs();
        if (updateMemory())
        {
            // neue Approximation aufgrund neuer Sensorwerte
            approximate();
            if (!DefaultApproximator.isValid)
            {
                return false;
            }
            CalcDropTime();
        }
        else
        {
            if (!validateSpeedUp())
            {
                // der tatsächliche quot-Wert des aktuellen Abschnittes kann nur größer sein
                // plötzlicher Stopp innerhalb eines 30°-Segmentes wird erkannt
                DefaultApproximator.isValid = false;
                digitalWrite(PIN_LED_Yellow, LOW);
                return false;
            }
        }
    }
}
///ServoControl
void drop()
{
    //eigentliche Prozedur
    TheServo.write(15);
    for (int pos = 15; pos <= 20; pos += 1)
    {
        TheServo.write(pos);
        busyDelay(20);
    }

    //zurücksetzen
    busyDelay(100);
    TheServo.write(0);
    busyDelay(100);
    TheServo.write(15);
}
///Analyzer
void busyDelay(unsigned long time)
{
    unsigned long waitUntil = millis() + time;
    while (millis() < waitUntil)
    {
        readInputs();
        updateMemory();
    }
}