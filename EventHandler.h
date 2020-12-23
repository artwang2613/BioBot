#include <ArduinoQueue.h>
#include <limits.h>
#include "TimeEvent.h"
#include <Arduino.h>

class EventHandler{

  public:
    int cycle = 0;
    EventHandler();
    void init();
    void addTime(int h, int m, int s, int mode, double temp);
    unsigned long getClosestTime();
    int convertToHMS(unsigned long val);
    int getSize();
    void setCycleOnOff(int i);
    void clearQueue();
    double getClosestTemp();
    void printQueue();
};
