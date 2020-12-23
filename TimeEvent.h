
#include <Arduino.h>

class TimeEvent{
  private:
    
  public:
    int timer[4];
    double temp;
    TimeEvent(int hours, int mins, int seconds, int mode, double temp);
    static TimeEvent* reTime(int hours, int mins, int seconds, int mode, double temp);
    void init();
    unsigned long getDelay();
    double getTemperature();

};
