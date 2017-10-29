/**
 EasyVR access control demo.
 
  Simple demo showing how to use the EasyVR Shield with Arduino
  to implement an access control system based on voice passwords.
 
  EasyVR wait for user names in group 1 and, if any name 
  is recognized, the system asks for the related password. 
  If the password is recognized the access is granted and 
  a servo is actuated, if not the access is denied.
 
  User names and passwords are trained with the EasyVR Commander.
  Transfer the voice recordings into the EasyVR sound table, then 
  enter and train user names in group 1 and related passwords in group 16.
  Use long names and passwords to increase recognition performance.
  Moreover, for better security set the recognition level to HARDER using the 
  setLevel function. Servo is connected to pin 9. 
  
  With EasyVR Shield, the green LED is ON while the module
  is listening (using pin IO1 of EasyVR).
  Details are displayed on the serial monitor window.

**
  Example code for the EasyVR library v1.0
  Written in 2011 by RoboTech srl for VeeaR <http:://www.veear.eu> 

  To the extent possible under law, the author(s) have dedicated all
  copyright and related and neighboring rights to this software to the 
  public domain worldwide. This software is distributed without any warranty.

  You should have received a copy of the CC0 Public Domain Dedication
  along with this software.
  If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.
*/

#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
  #include "SoftwareSerial.h"
  SoftwareSerial port(12,13);
#else // Arduino 0022 - use modified NewSoftSerial
  #include "WProgram.h"
  #include "NewSoftSerial.h"
  NewSoftSerial port(12,13);
#endif

#include "EasyVR.h"
#include <Servo.h> 

#define SND_Access_denied            1
#define SND_Access_granted           2
#define SND_Hello                    3
#define SND_Please_repeat            4
#define SND_Please_say_your_password 5
#define SND_Please_talk_louder       6


Servo myservo;
EasyVR easyvr(port);
EasyVRBridge bridge;

uint32_t mask = 0;
int8_t group = 0;
uint8_t train = 0;
char name[32];


void setup()
{
  // bridge mode?
  if (bridge.check())
  {
    cli();
    bridge.loop(0, 1, 12, 13);
  }

  Serial.begin(9600);
  port.begin(9600);
  
  myservo.attach(9);
  myservo.write(90);  
  
  if (!easyvr.detect())
  {
    Serial.println("EasyVR not detected!");
    for (;;);
  }
  
  easyvr.setPinOutput(EasyVR::IO1, LOW);
  Serial.println("EasyVR detected!");
  easyvr.setTimeout(5);
  easyvr.setLanguage(EasyVR::ITALIAN);
  
  int16_t count = 0;
  
  
  if (easyvr.getGroupMask(mask)) // get trained user names and passwords
  {
    uint32_t msk = mask;  
    for (group = 0; group <= EasyVR::PASSWORD; ++group, msk >>= 1)
    {
      if (!(msk & 1)) continue;
      if (group == EasyVR::TRIGGER)
        Serial.print("Trigger: ");
      else if (group == EasyVR::PASSWORD)
        Serial.print("Password: ");
      else
      {
        Serial.print("Group ");
        Serial.print(group);
        Serial.print(": ");
      }
      count = easyvr.getCommandCount(group);
      Serial.println(count);
      for (int8_t idx = 0; idx < count; ++idx)
      {
        if (easyvr.dumpCommand(group, idx, name, train))
        {
          Serial.print(idx);
          Serial.print(" = ");
          Serial.print(name);
          Serial.print(", Trained ");
          Serial.print(train, DEC);
          if (!easyvr.isConflict())
            Serial.println(" times, OK");
          else
          {
            int8_t confl = easyvr.getWord();
            if (confl >= 0)
              Serial.print(" times, Similar to Word ");
            else
            {
              confl = easyvr.getCommand();
              Serial.print(" times, Similar to Command ");
            }
            Serial.println(confl);
          }
        }
      }
    }
  }
  easyvr.setLevel(EasyVR::HARDER);
  easyvr.playSound(SND_Hello, EasyVR::VOL_FULL);
}

void loop()
{
  int idx_cmd;	
  int idx_pwd;
  
  easyvr.setPinOutput(EasyVR::IO1, HIGH); // LED on (listening)
  
  Serial.println("Say a name in Group 1");  
  easyvr.recognizeCommand(1); // recognise command in group 1 
  while (!easyvr.hasFinished()); // wait for user name
  
  easyvr.setPinOutput(EasyVR::IO1, LOW); // LED off
 
  idx_cmd = easyvr.getCommand(); // get recognised user name

  if (idx_cmd >= 0) 
  {    
    Serial.print("Name: ");    
    if (easyvr.dumpCommand(1, idx_cmd, name, train))
      Serial.println(name);
    else
      Serial.println();    
    
    easyvr.playSound(SND_Please_say_your_password , EasyVR::VOL_FULL);  // ask for password
    
    easyvr.setPinOutput(EasyVR::IO1, HIGH); // LED on (listening)  
    
    Serial.println("Say the password");    
    easyvr.recognizeCommand(EasyVR::PASSWORD); // set group 16
    while (!easyvr.hasFinished()); // wait for password
  
    easyvr.setPinOutput(EasyVR::IO1, LOW); // LED off    
    
    idx_pwd = easyvr.getCommand(); // get recognised password
    
    if (idx_pwd >= 0)
    {
      Serial.print("Password: ");     
      
      if (easyvr.dumpCommand(EasyVR::PASSWORD, idx_pwd, name, train))
      {
        Serial.print(" = ");
        Serial.println(name);
      }
      else
        Serial.println();      
      
      if ( idx_pwd == idx_cmd) // index of username and password are the same, access granted
      {

        Serial.println("Access granted");
        easyvr.playSound(SND_Access_granted , EasyVR::VOL_FULL);    

        myservo.write(180);	// move servo 
        delay(2500);		// wait a while
        myservo.write(90);	// move servo
      }
      else // index of username and password differ, access is denied
      {
        Serial.println("Access denied");
        easyvr.playSound(SND_Access_denied , EasyVR::VOL_FULL);    
      }
      
    }    
    
    int16_t err = easyvr.getError();
    
    if (easyvr.isTimeout() || (err >= 0)) // password timeout, access is denied
    {
      
      Serial.println("Error, try again...");
      easyvr.playSound(SND_Access_denied , EasyVR::VOL_FULL); 
      
    }
  }
  
  else
  {
    if (easyvr.isTimeout()) 
        Serial.println("Timed out, try again...");
      
    int16_t err = easyvr.getError();
    if (err >= 0)
    {
      Serial.print("Error ");
      Serial.println(err, HEX);          
    }
  }
}



