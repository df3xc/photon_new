
#pragma GCC diagnostic ignored "-Wwrite-strings"

#include "application.h"

bool wifi_on()
{
    int k = 30;
    bool wifiReady = false;

    Serial.printlnf(" turning WiFi on"); 
    WiFi.on();
    WiFi.connect();

    while(k>0)
    {
      delay(250);
      k--;
      wifiReady = WiFi.ready(); 
    }
    Serial.printlnf(" wifi=%s ", (wifiReady ? "connected" : "not connected"));

    if(wifiReady==false)
    {
      Serial.printlnf("### ERROR : could not connect to WiFi"); 
      WiFi.off();     
    }
    Serial.printlnf(" done");
    return(wifiReady);
}

void help ()
{
  Serial.printlnf(" ----- HELP -----");
  Serial.printlnf(" c : connect to cloud");
  Serial.printlnf(" d : disconnect from cloud and WiFi off");  
  Serial.printlnf(" w : WiFi on");   
}

/*---------------------------------------------------------------------
Dispatch command
---------------------------------------------------------------------*/

void dispatchCommand(char c)
{

  switch (c)
  {
  case 'h':
    help();
    break;

  case 'c':   
    Serial.printlnf(" connecting to cloud");
    Particle.connect();
    Serial.printlnf(" done");
    break; 

  case 'd':
    Serial.printlnf(" disconnecting from cloud");  
    Particle.disconnect();
    Serial.printlnf(" WiFi off");    
    WiFi.off();
    Serial.printlnf(" done");
    break; 

  case 'w':
    wifi_on();   
    break;     

  }
}

/*---------------------------------------------------------------------
Dispatch characters from serial port
---------------------------------------------------------------------*/
void serialEvent()
{
  char c = Serial.read();
  dispatchCommand(c);
}
