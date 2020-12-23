
#include "TimeEvent.h"


TimeEvent::TimeEvent(int hours, int mins, int seconds, int mode, double temp) {
  this->timer[0] = hours;
  this->timer[1] = mins;
  this->timer[2] = seconds;
  this->timer[3] = mode;
  this->temp = temp;

  init();
}

void TimeEvent::init() {

}

TimeEvent* TimeEvent::reTime(int hours, int mins, int seconds, int mode, double temp) {
  TimeEvent *t = new TimeEvent(hours, mins, seconds, mode, temp);
  //Serial.println("Inside timeevent: ");
  //Serial.println(temp);
  return t;
}

double TimeEvent::getTemperature() {
  return temp;
}

unsigned long TimeEvent::getDelay() {
  int scale = 3600;
  
  unsigned long timeLength = 0;
  for (int i = 0; i < 3; ++i) {
    timeLength += scale * timer[i];
    scale /= 60;
  }

  unsigned long eTime;
  int mode = timer[3];
  /*Serial.println(timer[0]);
  Serial.println(timer[1]);
  Serial.println(timer[2]);
  Serial.println(timer[3]);*/

  if (mode == 0) { //timer mode
    eTime = timeLength * 1000 - millis();
  } else if (mode == 1) { //to to mode
    eTime = timeLength * 1000; //this one needs real time clock tracking
  } else {
    //Serial.print("Bad Mode\n");
  }
  return eTime;
}
