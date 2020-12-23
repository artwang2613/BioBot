#include "EventHandler.h"

ArduinoQueue<TimeEvent*> eventQueue(10, 1000);
ArduinoQueue<TimeEvent*> originalValQueue(10, 1000);


EventHandler::EventHandler(){
}

void EventHandler::init(){
     
}

void EventHandler::setCycleOnOff(int i){
  cycle = i;
}

void EventHandler::addTime(int h, int m, int s, int mode, double temp){

  unsigned long curSysTime = millis();
  /*h += curSysTime/(3600)/1000;
  curSysTime = curSysTime%(3600)/1000;
  m += curSysTime/(60)/1000;
  curSysTime = curSysTime%1000;
  s += curSysTime/(1000);*/

  /*Serial.println("Put in: ");
  Serial.print(h);
  Serial.print(" ");
  Serial.print(m);
  Serial.print(" ");
  Serial.print(s);
  Serial.println(temp);*/
  
  
  //TEMP CODE UNTIL RTC -> Will be replaced
  if(eventQueue.itemCount() == 0){
    eventQueue.enqueue(TimeEvent::reTime(h, m, s, mode, temp));
    originalValQueue.enqueue(TimeEvent::reTime(h, m, s, mode, temp));
  }else{
    TimeEvent* x = eventQueue.getTail();
    eventQueue.enqueue(TimeEvent::reTime(h + x->timer[0], m + x->timer[1], s + x->timer[2], mode, temp));
    originalValQueue.enqueue(TimeEvent::reTime(h, m, s, mode, temp));
  }
}

int EventHandler::convertToHMS(unsigned long val){
  //TODO
}

int EventHandler::getSize(){
  return eventQueue.itemCount();
}

void EventHandler::printQueue(){
  for(int i = 0; i < eventQueue.itemCount();++i){
    TimeEvent* temper = eventQueue.dequeue();
    //Serial.print("S");
    //Serial.print(i);
    //Serial.print(" ");
    //Serial.println(temper->getDelay());
    eventQueue.enqueue(temper);
  }
}



unsigned long EventHandler::getClosestTime(){
  unsigned long minDelay = ULONG_MAX;
  unsigned long curDelay = ULONG_MAX;
  if(eventQueue.itemCount() == 0){
    return minDelay;
  }
  //int minIndex = 0;
  /*for(int i=0; i< eventTimes.size(); i++){ //Remnant code from different interval model
    curDelay = eventTimes[i]->getDelay();
    if(minDelay > curDelay){
      minDelay = curDelay;
      minIndex = i;
    }
  }*/ 
  minDelay = eventQueue.getHead()->getDelay();
  //Serial.print("Delay: \n");
  //Serial.println(minDelay);
  if(minDelay <= 1000 && cycle == 0){
    //Serial.print("Deleted\n");
    eventQueue.dequeue();
  }else if(minDelay <= 1000 && cycle != 0){
    //Serial.println("Re-added\n");
    TimeEvent* x = eventQueue.dequeue();
    TimeEvent* og = originalValQueue.dequeue();
    addTime(og->timer[0], og->timer[1], og->timer[2], og->timer[3], og->temp);
    originalValQueue.enqueue(og);
  }
  return minDelay;
}

double EventHandler::getClosestTemp(){
  //Serial.print("closest temp ");
  //Serial.println(eventQueue.getHead()->temp);
  unsigned long t = getClosestTime();
  return eventQueue.getHead()->temp;
}
