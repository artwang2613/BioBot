#include <dht11.h>

#include <Arduino.h>
#include <PID_v1.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include "EventHandler.h"

#endif

class TempController{
  private:
    double input = 0;
    double output = 0;
    double setPoint = 0;
    double temp;
    double error = 0;

    int pidCalcTimer = 0;
    int tempPin;
    int padPin;
    int padPower;
    PID* controller;
    OneWire* wire;
    DallasTemperature* tempSensor;

   
    
  public:
    TempController(int tPin, int pPin);
    void init();
    void control(EventHandler hdl);
    void cycle(EventHandler hdl);
    void plotResponse();
};
