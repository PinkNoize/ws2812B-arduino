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
  delay(5000);
  //display green
  single.red=0;
  single.blue=0;
  single.green=255;
  strip.write(LEDSPIN);
  delay(5000);
  //display blue
  single.red=0;
  single.blue=255;
  single.green=0;
  strip.write(LEDSPIN);
  delay(5000);
  //display moving lights
  strip.start=&lights[0];
  //create spaced out LED pattern
  for(int i=0;i<LEDSIZE;i++) {
    if(i % 4 == 0) {
      lights[i].red=238;
      lights[i].green=130;
      lights[i].blue=238;
    }
    else {
      lights[i].red=0;
      lights[i].green=0;
      lights[i].blue=0;
    }
  }
  for(int i=1000;i>=0;i--) {
    //write current pattern
    strip.write(LEDSPIN);
    //increment starting LED to create moving LED effect
    strip.start=strip.start->next;
    delay(200);
  }
}
