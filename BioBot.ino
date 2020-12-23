#include <hd44780.h>
#include <hd44780ioClass/hd44780_pinIO.h> 
#include <SPI.h>
#include <WiFiNINA.h>

#include <limits.h>

#include "TempController.h"
#include "lcdManager.h"

const int motor = 10; //LED connected to digital pin 10
const int tPin = 13;
const int heatPin = 8;
unsigned long cur = 0;

byte mac[6];  

IPAddress ipComp(172, 30, 92, 214);
IPAddress ipLocal(72, 19, 73, 224);
IPAddress ipMask(255, 255, 252, 0);
IPAddress ipDNS(128, 119, 148, 167);
IPAddress ipGate(72, 19, 72, 1);


char ssid[] = "UMASS-DEVICES";
char pass[] = "GoUMass!";
/*
char ssid[] = "eduroam3";
char user[] = "artwang";
char pass[] = "Confused8888!";
*/

String hostName = "www.google.com";
int status = WL_IDLE_STATUS; 
int pingResult;

WiFiServer server(80);

EventHandler handler = EventHandler();
TempController thermostat = TempController(tPin, heatPin);
lcdManager lcd = lcdManager(75);

void setup(){
  Serial.begin(9600);
  pinMode(motor, OUTPUT); //sets the digital pin as output
  pinMode(heatPin, OUTPUT);
 
  //handler.init();
  handler.setCycleOnOff(1);
  lcd.init();
  lcd.input(handler);
  /* WiFi.macAddress(mac);
  Serial.print("MAC: ");
  Serial.print(mac[5],HEX);
  Serial.print(":");
  Serial.print(mac[4],HEX);
  Serial.print(":");
  Serial.print(mac[3],HEX);
  Serial.print(":");
  Serial.print(mac[2],HEX);
  Serial.print(":");
  Serial.print(mac[1],HEX);
  Serial.print(":");
  Serial.println(mac[0],HEX);*/
  /*startWifi();
  IPAddress ip2 = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip2);
  Serial.print("Subnet Mask: ");
  Serial.println(WiFi.subnetMask());
  Serial.print("Gateway IP: ");
  Serial.println(WiFi.gatewayIP());
  Serial.print("DNS: ");
  Serial.println("ddns.umass.edu");*/
}

void loop(){
  /*WiFiClient client = server.available();   //listen for incoming clients
  Serial.println("Looking for Client");
  if (client) {                             
    Serial.println("new client");           
    String currentLine = "";                
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        if (c == '\n' && currentLineIsBlank) {
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close"); 
          client.println("Refresh: 5"); 
          client.println();
          client.println("<!DOCTYPE HTML>");
          client.println("<html>");
          //send data to website, create option to download as csv over internet
          client.println("</html>");
          break;
        }
        if (c == '\n') {
          currentLineIsBlank = true;
        } else if (c != '\r') {
          currentLineIsBlank = false;
        }
      }
    }
    client.stop();
    Serial.println("client disonnected");
  }*/
  thermostat.control(handler);
  /*if(cur <= 8){
    pump();
  }*/
  if(cur != ULONG_MAX){
    lcd.printSelectedDelay(handler);
  }else{
    lcd.printHome(handler);
  }
}


void startWifi(){
  while ( status != WL_CONNECTED) {
    Serial.print("Attempting to connect to WPA SSID: ");
    Serial.println(ssid);
    //status = WiFi.beginEnterprise(ssid, user, pass);
    status = WiFi.begin(ssid, pass);
    delay(5000);
  }
  Serial.println("You're connected to the network");
  Serial.print("Pinging ");
  Serial.print(hostName);
  Serial.print(": ");
  pingResult = WiFi.ping(hostName);
  if (pingResult >= 0) {
    Serial.print("SUCCESS! RTT = ");
    Serial.print(pingResult);
    Serial.println(" ms");
  } else {
    Serial.print("FAILED! Error code: ");
    Serial.println(pingResult);
  }
  Serial.print("Pinging ");
  Serial.print("Local Computer");
  Serial.print(": ");
  pingResult = WiFi.ping(ipLocal);
  if (pingResult >= 0) {
    Serial.print("SUCCESS! RTT = ");
    Serial.print(pingResult);
    Serial.println(" ms");
  } else {  //This one fails on UMASS-DEVICES, laptop can ping arduino but not the other way around, debugging
    Serial.print("FAILED! Error code: "); 
    Serial.println(pingResult);
  }
  server.begin();
}

void pump(){
  Serial.print("on");
  digitalWrite(motor,HIGH); //on
  delay(5000);
  Serial.print("off");
  
  digitalWrite(motor,LOW);
}
