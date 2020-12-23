#include"TempController.h"

TempController::TempController(int tPin, int pPin) {
  tempPin = tPin;
  padPin = pPin;
  wire = new OneWire(tPin);
  //pinMode(A5, INPUT);
  tempSensor = new DallasTemperature(wire);
  controller = new PID(&input, &output, &setPoint, 10, 1, 0, DIRECT);
  init();
}

void TempController::init() {
  tempSensor->begin();
  controller->SetMode(AUTOMATIC);
  controller->SetOutputLimits(125, 255);
}

void TempController::control(EventHandler hdlr) {
  //Serial.println("Start Control:");
  tempSensor->requestTemperatures();
  input = tempSensor->getTempCByIndex(0); //TODO get it to cycle
  delay(100);
  setPoint = hdlr.getClosestTemp();
  //input = (double) DHT11.temperature; //TODO make sure to sample less so there is no drift

  error = input - setPoint;
  if (error > 0.2) {
    output = 50;
  } else {
    if (error > -3 && error <= -1) {
      controller->SetTunings(3, 0.025, 0);
      controller->SetOutputLimits(90, 140);
    }
    if (error > -1 && error <= 0.2) {
      controller->SetTunings(3, 0.025, 0);
      controller->SetOutputLimits(90, 129);
    }
    controller->Compute();
  }
  /*Serial.print("    Error: ");
  Serial.println(error);
  Serial.print("    Setpoint: ");
  Serial.println(setPoint);
  Serial.print("    Output: ");
  Serial.println(output);*/
  Serial.print(hdlr.getClosestTime());
  Serial.print(",");
  Serial.println(input);

  analogWrite(padPin, output);
}
