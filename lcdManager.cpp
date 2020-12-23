#include "lcdManager.h";

lcdManager::lcdManager(int Contrast){
  contrast = Contrast;
  screen = new hd44780_pinIO(12, 11, 5, 4, 3, 2);
}

void lcdManager::init(){
  analogWrite(6,contrast);
  screen->begin(16, 2);
}


void lcdManager::printHome(EventHandler handler){
  screen->clear();
  screen->setCursor(0, 0);
  screen->print("There are ");
  screen->print(handler.getSize());
  screen->print(" tasks left");
}
void lcdManager::printSelectedDelay(EventHandler handler){//TODO add selection function using buttons or something
  screen->clear();
  screen->setCursor(0, 0);
  screen->print("Time till next pump.");
   
  screen->setCursor(0, 1);
  
  if(handler.getClosestTime()/1000){
    
  }
  screen->print(handler.getClosestTime()/1000);
}

void lcdManager::input(EventHandler handler){
  handler.addTime(0, 15, 0, 0, 38);
  handler.addTime(0, 15, 0, 0, 36);
  //handler.addTime(0, 6, 0, 0, 30);
}
