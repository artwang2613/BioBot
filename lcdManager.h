
#include <hd44780.h>
#include <hd44780ioClass/hd44780_pinIO.h>
#include <Arduino.h>
#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include "EventHandler.h"

#endif


class lcdManager{
  private:
    int contrast = 0;
    hd44780_pinIO* screen;
  public:
    lcdManager(int Contrast);
    void init();
    void printSelectedDelay(EventHandler handler);
    void printHome(EventHandler handler);
    void input(EventHandler handler);

};
