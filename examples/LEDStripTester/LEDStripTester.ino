/*
  LEDStripTester

  Flashes a strip of WS2812B LEDs through several different patterns
  demonstrating several ways to manipulate the LEDs

*/
#include <WS2812BStrip.h>
#include <Arduino.h>
#define LEDSPIN 5
#define LEDSIZE 60

using namespace WS2812B;

LED lights[LEDSIZE];
LED single;
LEDStrip strip(lights,LEDSIZE);
int stackTop;
void setup() {
  initLEDStrip(lights, LEDSIZE);
  single.next=&single;
}

void loop() {
  //display a single color
  strip.start=&single;
  //display red
  single.red=255;
  single.green=0;
  single.blue=0;
  strip.write(LEDSPIN);
  delay(1000);
  //display green
  single.red=0;
  single.blue=0;
  single.green=255;
  strip.write(LEDSPIN);
  delay(1000);
  //display blue
  single.red=0;
  single.blue=255;
  single.green=0;
  strip.write(LEDSPIN);
  delay(1000);
  //display moving lights
  strip.start=&lights[0];
  //create spaced out LED pattern
  for(int i=0;i<LEDSIZE;i+=15) {
    for(int t=0;t<15;t++) {
      if(t<4) {
        lights[i+t].red=200;
        lights[i+t].green=0;
        lights[i+t].blue=100;
      }
      else {
        lights[i+t].red=55;
        lights[i+t].green=255;
        lights[i+t].blue=155;
      }
    }
  }
  for(int i=200;i>=0;i--) {
    //write current pattern
    strip.write(LEDSPIN);
    //increment starting LED to create moving LED effect
    strip.start=strip.start->next;
    delay(50);
  }
  //create stacking LED effect
  //set all LEDs to green
  for(int i=0;i<LEDSIZE;i++) {
    lights[i].red=55;
    lights[i].green=255;
    lights[i].blue=155;
  }
  strip.write(LEDSPIN);
  stackTop=0;
  strip.start=&lights[0];
  //stack LEDs starting from the top to the top of the stack
  while(stackTop<LEDSIZE) {
    for(int q=LEDSIZE-2;q>=stackTop;q--) {
      //set LED to pink
      lights[q+1].red=200;
      lights[q+1].green=0;
      lights[q+1].blue=100;
      strip.write(LEDSPIN);
      delay(5);
      //reset LED to green
      lights[q+1].red=55;
      lights[q+1].green=255;
      lights[q+1].blue=155;
      //set next LED to pink
      lights[q].red=200;
      lights[q].green=0;
      lights[q].blue=100;
      strip.write(LEDSPIN);
      delay(20);
    }
    //make sure top of stack is pink
    lights[stackTop].red=200;
    lights[stackTop].green=0;
    lights[stackTop].blue=100;
    stackTop++;
  }
  delay(1000);
}