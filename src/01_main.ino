
/* Test application : check cloud connect and disconnect */

/* GOAL : APP shall run without cloud connection */

#include <time.h>

String hwID;
int fast_counter = 0;
int slow_counter = 0;
char timebuffer[50]; // used by webhook / webrequest

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
  Serial.printlnf("      Welcome");
  Serial.printlnf("----------------------");
  hwID = System.deviceID();
  Serial.print("Device HW ID : ");
  Serial.printlnf(hwID);
}

void loop()
{
fast_counter++;

if ((fast_counter % 5000) == 0)
{
    bool wifiReady;
    bool cloudReady;

    wifiReady = WiFi.ready();
    cloudReady = Particle.connected();

    slow_counter++;
    Serial.printlnf("Slowcounter %d ",slow_counter);
    timeStamp();
    Serial.printlnf("Here is Olaf ");

    Serial.printlnf(" wifi=%s cloud=%s fast_counter=%d ", (wifiReady ? "on" : "off"), (cloudReady ? "on" : "off"), fast_counter);

}

}