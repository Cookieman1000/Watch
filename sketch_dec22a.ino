

/*
 * Description: This sketch codes a watch in Arduino 
 * Authors: Sam and Jason Shenoi 
 */
#include <Time.h>
#include <TimeLib.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <String.h>
#include "functions.h"
#define ACTIVATED LOW
#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

//Create arrays that correspond to the button Pins and states
const int buttonPins[4] = {2,3,4,5};
int btnsStates[4] = {1, 1, 1, 1}; 
int displayType = 0; 
long timeMill = 0;
long sMill = 0;
bool stopStarted = false;
void setup()
{
  Wire.begin();
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);// initialize with the I2C addr 0x3C (for the 128x32)(initializing the display)
  // initialize the pushbutton pin as an input:
  pinMode(buttonPins[0], INPUT);
  digitalWrite(buttonPins[0],HIGH);
  Serial.begin(9600);

  /*
   * Sam's Notes: 
   *  - Have to make sure to set the current time each time you load the application. 
   *  - Possible ways to fix this could be wifi/bluetooth connection to a computer or something that has the correct time
  */
  setTime(10,13,40,22,12,2018);
  timeDisplay();
  display.display();
  
}


/*
 * This function displays the current hour and minute time on the watches face.
 * See above comment to see how it works
 * 
 */
void timeDisplay(){
  DisplayInit(3);
  time_t t = now();
  
  //Add time face to to the home screen 
  AddDisplay( 10, 0, String(hour(t)));
  AddDisplay(55, 0, ":");
  AddDisplay(80, 0, String(minute(t)));
  
  display.setTextSize(2);
  AddDisplay(15,20,"+"); 
  for(int i =25; i< 100; i+=25){
      AddDisplay(i+15, 20, "-");
  }
 
}

void DisplayInit(int txtSize){
   display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(txtSize);
}
void AddDisplay(int w, int h, String txt){
   display.setCursor(w,h);
   display.print(txt);
}

void StopWatch(long milli){
  int secs = milli/1000; 
  DisplayInit(2);
  AddDisplay(0, 0, String(secs));
   display.setTextSize(2);
  AddDisplay(35,20,"+"); 
  for(int i =0; i< 100; i+=25){
      if(i!=25){
        AddDisplay(i+15, 20, "-");
      }
      
  }
  
}
void DisplayPotato(){
  DisplayInit(3);
  AddDisplay( 10, 0, "Potato");
  display.setTextSize(2);
  AddDisplay(65,20,"+"); 
  for(int i =0; i< 100; i+=25){
      if(i!=50){
        AddDisplay(i+15, 20, "-");
      }
      
  }
}

void DisplayHi(){
  DisplayInit(3);
  AddDisplay( 10, 0, "Hi");
  display.setTextSize(2);
  AddDisplay(90,20,"+"); 
  for(int i =0; i< 100; i+=25){
      if(i!=75){
        AddDisplay(i+15, 20, "-");
      }
      
  }
}
void loop()
{
  //Read in Pin 1
  btnsStates[0] = digitalRead(buttonPins[0]);
  btnsStates[2] = digitalRead(buttonPins[2]);

  if(btnsStates[0] == ACTIVATED) {
     displayType = (displayType+1)%4; 
  }
   switch(displayType){
     case 0:   timeDisplay();break;
     case 1:   StopWatch(timeMill);break;
     case 2:   DisplayPotato();break;
     case 3:   DisplayHi();break;
  }


 /* if(btnsStates[2] == ACTIVATED && displayType%4 == 1) {
     if(stopStarted==true){
       //User wants to stop stopwatch 
       timeMill =  millis() - sMill;
       delay(200); 
       timeMill = sMill = 0; 
       stopStarted==false;
     }else{
      //User wants to start stopwatch
      timeMill = sMill =  millis();
       StopWatch(0);
       stopStarted==true;
     }
  }else if(displayType%4 == 1 && stopStarted==true){
     timeMill = millis() - sMill;
     StopWatch(timeMill);
  }*/
  

  display.display();
  
}
