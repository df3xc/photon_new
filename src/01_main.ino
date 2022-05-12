
/* Test application : check cloud connect and disconnect */

/* GOAL : APP shall run without cloud connection */

#include <time.h>
#include "02_console.h"
#include "08_database.h"


/* SYSTEM MODE and SYSTEM THREAD 

The application executes Loop() even not connected to Wifi and Cloud.

After wake-up, the system will try to set the last Wifi and Cloud connection
which was set before entering sleep mode

These calls are needed to establish cloud connection:
    WiFi.on();
    WiFi.connect();
    Particle.connect();

*/

SYSTEM_MODE(MANUAL);
SYSTEM_THREAD(ENABLED);

String hwID;
int fast_counter = 0;
int slow_counter = 0;
char timebuffer[50]; // used by webhook / webrequest
char buffer[250];

int utime;

/*---------------------------------------------------------------------
print timestamp to serial port
---------------------------------------------------------------------*/
void timeStamp()
{
  sprintf(timebuffer, " %.2d-%.2d-%d %.2d:%.2d:%.2d ",
          Time.day(),
          Time.month(),
          Time.year(),
          Time.hour(),
          Time.minute(),
          Time.second());

  Serial.print(timebuffer);
  }

void setup()
{
  Serial.begin(115200);
  delay(2000); // Allow board to settle

  // Time.zone(+1); // Winterzeit
  Time.zone(+2); // Sommerzeit

  Serial.printlnf(" ");

  Serial.printlnf(" ");
  Serial.printlnf("----------------------");
  Serial.printlnf("      Welcome 1");
  Serial.printlnf("----------------------");
  hwID = System.deviceID();
  Serial.print("Device HW ID : ");
  Serial.printlnf(hwID);

  timeStamp();

  /* wifi_on() 
     function is bocking call but timeout after 5seconds if WIFI not available 
  */

  timeStamp();
  Serial.printlnf(" try to access WIFI AP"); 

  if (wifi_on()==true) 
  {
    Serial.printlnf(" WIFI is on. Now connecting to cloud");  
    Particle.connect();
   }

  //WiFi.on();
  delay(6000);
  //Particle.connect();  
  timeStamp();
  Serial.printlnf(" continue even if no WIFI and CLOUD"); 

  WriteToDatabase("OLAF", "#### SETUP #### : ");

}

/*---------------------------------------------------------------------
Sleep and Wakeup
---------------------------------------------------------------------*/
void sleep(int minutes)
{
    if (minutes > 120)
    {
      minutes = 120;
    }
  
    Serial.printlnf(" *** PREPARE SLEEP *** ");

    delay(1000);
    WriteToDatabase("OLAF", "#### SLEEP Minutes #### : ", minutes);
    delay(1000);

    utime = Time.now();
 
    System.sleep(D1, RISING, 60 * minutes); // no reset of device after wakeup

    // After WAKE UP to SW continues execution here :
    /* variables survive the sleep mode. Reset them if needed */


    slow_counter = 0;
    fast_counter = 0;

    delay(1000);

    Serial.printlnf(" *** WAKE UP *** ");
    timeStamp();
    Serial.printlnf(" try to access WIFI AP");   

    // if (wifi_on()==true) 
    // {
    //   Serial.printlnf(" WIFI is on. Now connecting to cloud");      
    //   Particle.connect();
    // }
    
    WiFi.on();
    delay(6000);
    Particle.connect();
    delay(5000);

    timeStamp();  
    if (Particle.connected() == false)
        {
          Serial.printlnf("WARNING: not connected to CLOUD after WakeUp");  
        }  
    Serial.printlnf(" continue even if no WIFI and CLOUD");     
    WriteToDatabase("WAKE UP", "#### OLAF WAKE UP ####");

}

void loop()
{

int tsec;
int tnew;

fast_counter++;
delay(100);

utime = Time.now();
tnew = utime + 5;

while ( utime < tnew)
{
    utime = Time.now();
    delay(200);
}

  bool wifiReady;
  bool cloudReady;

  wifiReady = WiFi.ready();
  cloudReady = Particle.connected();

  //if (cloudReady == true) Particle.process();

  slow_counter++;
  Serial.printlnf("Slowcounter %d ",slow_counter);
  timeStamp();
  Serial.printlnf("Here is Olaf ");
  Serial.printlnf(" wifi=%s cloud=%s fast_counter=%d ", (wifiReady ? "on" : "off"), (cloudReady ? "on" : "off"), fast_counter);
  utime = Time.now();
  Serial.printlnf("unix time %d ",utime);
  Serial.printlnf("day of week %d ",Time.weekday());  // North American implementation : Sunday is day number one, Monday is day numer two.

if ((fast_counter % 6) == 0)
    {
    WriteToDatabase ( "olaf",  "status");
    }

if ((fast_counter % 24) == 0)
    {
    sleep(1);
    }

}