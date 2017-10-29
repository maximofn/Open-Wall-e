//#include "Arduino.h"
//#include "SoftwareSerial.h"
//SoftwareSerial port(12, 13);

//#include "EasyVR.h"

//EasyVR easyvr(port);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  while (!Serial)
  {
    // wait for serial port to connect. Needed for native USB port only
  }
  Serial.println("Inicio EasyVRTest");

  // initialize EasyVR  
  /*while (!easyvr.detect())
  {
    //println(F("EasyVR not detected!"));
    delay(100);
  }*/

}

void loop() {
  // put your main code here, to run repeatedly:

}
