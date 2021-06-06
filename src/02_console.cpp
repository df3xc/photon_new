
#pragma GCC diagnostic ignored "-Wwrite-strings"

#include "application.h"

void help ()
{
 Serial.printlnf(" ----- HELP -----");
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
