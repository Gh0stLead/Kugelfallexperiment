#include <Servo.h>
#include "MainController.h"

/**
   Authors:
   Christian Kühn
   Tobias Roth
   Izabella Szen
*/

MainController* mainController;

void setup() {
  mainController = new MainController();
}

void loop() {
  mainController->eventLoop();
}

