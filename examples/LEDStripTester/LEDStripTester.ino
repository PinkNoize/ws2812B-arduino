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
  strip.start=&single;
  single.red=255;
  single.green=0;
  single.blue=0;
  strip.write(LEDSPIN);
  delay(5000);
  single.red=0;
  single.blue=0;
  single.green=255;
  strip.write(LEDSPIN);
  delay(5000);
  single.red=0;
  single.blue=255;
  single.green=0;
  strip.write(LEDSPIN);
  delay(5000);
  strip.start=&lights[0];
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
    strip.write(LEDSPIN);
    strip.start=strip.start->next;
    delay(200);
  }
}
