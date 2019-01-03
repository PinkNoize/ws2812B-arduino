#ifndef WS2812BStrip_C
#define WS2812BStrip_C

#include "WS2812BStrip.h"
#include <Arduino.h>

#if !(F_CPU == 8000000 || F_CPU == 16000000 || F_CPU == 20000000)
#error "On an AVR, this version of the PololuLedStrip library only supports 8, 16 and 20 MHz."
#endif

#if defined(__AVR_ATmega32U4__)
  // ATmega32U4-based boards such as the Arduino Leonardo

  const unsigned char pinBit[] =
  {
    2, 3, 1, 0, 4, 6, 7, 6,  // Pins 0-7
    4, 5, 6, 7, 6, 7,        // Pins 8-13
    3, 1, 2, 0,              // Pins 14-17
    7, 6, 5, 4, 1, 0,        // Pins 18-23
    4, 7, 4, 5, 6, 6,        // Pins 24-29
  };

  const unsigned char pinAddr[] =
  {
    _SFR_IO_ADDR(PORTD),
    _SFR_IO_ADDR(PORTD),
    _SFR_IO_ADDR(PORTD),
    _SFR_IO_ADDR(PORTD),
    _SFR_IO_ADDR(PORTD),
    _SFR_IO_ADDR(PORTC),
    _SFR_IO_ADDR(PORTD),
    _SFR_IO_ADDR(PORTE),

    _SFR_IO_ADDR(PORTB),
    _SFR_IO_ADDR(PORTB),
    _SFR_IO_ADDR(PORTB),
    _SFR_IO_ADDR(PORTB),
    _SFR_IO_ADDR(PORTD),
    _SFR_IO_ADDR(PORTC),

    _SFR_IO_ADDR(PORTB),
    _SFR_IO_ADDR(PORTB),
    _SFR_IO_ADDR(PORTB),
    _SFR_IO_ADDR(PORTB),

    _SFR_IO_ADDR(PORTF),
    _SFR_IO_ADDR(PORTF),
    _SFR_IO_ADDR(PORTF),
    _SFR_IO_ADDR(PORTF),
    _SFR_IO_ADDR(PORTF),
    _SFR_IO_ADDR(PORTF),

    _SFR_IO_ADDR(PORTD),
    _SFR_IO_ADDR(PORTD),
    _SFR_IO_ADDR(PORTB),
    _SFR_IO_ADDR(PORTB),
    _SFR_IO_ADDR(PORTB),
    _SFR_IO_ADDR(PORTD),
  };

  #elif defined(__AVR__) && !defined(NUM_DIGITAL_PINS) || NUM_DIGITAL_PINS == 20
  // ATmega168/328-based boards such as the Arduino Uno or Baby Orangutan B-328

  const unsigned char pinBit[] =
  {
    0, 1, 2, 3, 4, 5, 6, 7,  // PORTD
    0, 1, 2, 3, 4, 5,        // PORTB
    0, 1, 2, 3, 4, 5, 6,     // PORTC
  };

  const unsigned char pinAddr[] =
  {
    _SFR_IO_ADDR(PORTD),
    _SFR_IO_ADDR(PORTD),
    _SFR_IO_ADDR(PORTD),
    _SFR_IO_ADDR(PORTD),
    _SFR_IO_ADDR(PORTD),
    _SFR_IO_ADDR(PORTD),
    _SFR_IO_ADDR(PORTD),
    _SFR_IO_ADDR(PORTD),
    _SFR_IO_ADDR(PORTB),
    _SFR_IO_ADDR(PORTB),
    _SFR_IO_ADDR(PORTB),
    _SFR_IO_ADDR(PORTB),
    _SFR_IO_ADDR(PORTB),
    _SFR_IO_ADDR(PORTB),
    _SFR_IO_ADDR(PORTC),
    _SFR_IO_ADDR(PORTC),
    _SFR_IO_ADDR(PORTC),
    _SFR_IO_ADDR(PORTC),
    _SFR_IO_ADDR(PORTC),
    _SFR_IO_ADDR(PORTC),
    _SFR_IO_ADDR(PORTC),
  };

  #elif defined(__AVR__) && NUM_DIGITAL_PINS == 70
  // ATmega2560-based boards such as the Arduino Mega 2560

  const unsigned char pinBit[] =
  {
    0, 1, 4, 5, 5, 3, 3, 4, 5, 6,
    4, 5, 6, 7, 1, 0, 1, 0, 3, 2,
    1, 0, 0, 1, 2, 3, 4, 5, 6, 7,
    7, 6, 5, 4, 3, 2, 1, 0, 7, 2,
    1, 0, 7, 6, 5, 4, 3, 2, 1, 0,
    3, 2, 1, 0, 0, 1, 2, 3, 4, 5,
    6, 7, 0, 1, 2, 3, 4, 5, 6, 7,
  };

  const unsigned char pinAddr[] =
  {
    _SFR_IO_ADDR(PORTE),
    _SFR_IO_ADDR(PORTE),
    _SFR_IO_ADDR(PORTE),
    _SFR_IO_ADDR(PORTE),
    _SFR_IO_ADDR(PORTG),
    _SFR_IO_ADDR(PORTE),
    _SFR_IO_ADDR(PORTH),
    _SFR_IO_ADDR(PORTH),
    _SFR_IO_ADDR(PORTH),
    _SFR_IO_ADDR(PORTH),
    _SFR_IO_ADDR(PORTB),
    _SFR_IO_ADDR(PORTB),
    _SFR_IO_ADDR(PORTB),
    _SFR_IO_ADDR(PORTB),
    _SFR_IO_ADDR(PORTJ),
    _SFR_IO_ADDR(PORTJ),
    _SFR_IO_ADDR(PORTH),
    _SFR_IO_ADDR(PORTH),
    _SFR_IO_ADDR(PORTD),
    _SFR_IO_ADDR(PORTD),
    _SFR_IO_ADDR(PORTD),
    _SFR_IO_ADDR(PORTD),
    _SFR_IO_ADDR(PORTA),
    _SFR_IO_ADDR(PORTA),
    _SFR_IO_ADDR(PORTA),
    _SFR_IO_ADDR(PORTA),
    _SFR_IO_ADDR(PORTA),
    _SFR_IO_ADDR(PORTA),
    _SFR_IO_ADDR(PORTA),
    _SFR_IO_ADDR(PORTA),
    _SFR_IO_ADDR(PORTC),
    _SFR_IO_ADDR(PORTC),
    _SFR_IO_ADDR(PORTC),
    _SFR_IO_ADDR(PORTC),
    _SFR_IO_ADDR(PORTC),
    _SFR_IO_ADDR(PORTC),
    _SFR_IO_ADDR(PORTC),
    _SFR_IO_ADDR(PORTC),
    _SFR_IO_ADDR(PORTD),
    _SFR_IO_ADDR(PORTG),
    _SFR_IO_ADDR(PORTG),
    _SFR_IO_ADDR(PORTG),
    _SFR_IO_ADDR(PORTL),
    _SFR_IO_ADDR(PORTL),
    _SFR_IO_ADDR(PORTL),
    _SFR_IO_ADDR(PORTL),
    _SFR_IO_ADDR(PORTL),
    _SFR_IO_ADDR(PORTL),
    _SFR_IO_ADDR(PORTL),
    _SFR_IO_ADDR(PORTL),
    _SFR_IO_ADDR(PORTB),
    _SFR_IO_ADDR(PORTB),
    _SFR_IO_ADDR(PORTB),
    _SFR_IO_ADDR(PORTB),
    _SFR_IO_ADDR(PORTF),
    _SFR_IO_ADDR(PORTF),
    _SFR_IO_ADDR(PORTF),
    _SFR_IO_ADDR(PORTF),
    _SFR_IO_ADDR(PORTF),
    _SFR_IO_ADDR(PORTF),
    _SFR_IO_ADDR(PORTF),
    _SFR_IO_ADDR(PORTF),
    _SFR_IO_ADDR(PORTK),
    _SFR_IO_ADDR(PORTK),
    _SFR_IO_ADDR(PORTK),
    _SFR_IO_ADDR(PORTK),
    _SFR_IO_ADDR(PORTK),
    _SFR_IO_ADDR(PORTK),
    _SFR_IO_ADDR(PORTK),
    _SFR_IO_ADDR(PORTK),
  };

#endif

WS2812B::LEDStrip::LEDStrip(LED* start, unsigned int size) : start(start), size(size) {};

void WS2812B::LEDStrip::writeRange(int pin, unsigned int count) {
    LED* colors=this->start;
    digitalWrite(pin,LOW);
    pinMode(pin,OUTPUT);
    cli();      //disable interrupts
    //Sends LEDS count times
    while(count--) {
        //Sends a color to a single LED
        //increments 'colors' pointer to colors->next
        asm volatile(
            "ld __tmp_reg__, %a0+\n"        // Read the green component and leave pointer at red
            "rcall send_led_strip_byte%=\n" // Send green component
            "ld __tmp_reg__, %a0+\n"        // Read the red component and leave pointer at blue
            "rcall send_led_strip_byte%=\n" // Send red component
            "ld __tmp_reg__, %a0\n"         // Read the blue component
            "rcall send_led_strip_byte%=\n" // Send blue component
            "rjmp led_strip_asm_end%=\n"    //Jump past the assembly subroutines.
            
            // send_led_strip_byte subroutine:  Sends a byte to the LED strip.
            "send_led_strip_byte%=:\n"
            "rcall send_led_strip_bit%=\n"  // Send most-significant bit (bit 7).
            "rcall send_led_strip_bit%=\n"
            "rcall send_led_strip_bit%=\n"
            "rcall send_led_strip_bit%=\n"
            "rcall send_led_strip_bit%=\n"
            "rcall send_led_strip_bit%=\n"
            "rcall send_led_strip_bit%=\n"
            "rcall send_led_strip_bit%=\n"  // Send least-significant bit (bit 0).
            "ret\n"

            // send_led_strip_bit subroutine:  Sends single bit to the LED strip by driving the data line
            // high for some time.  The amount of time the line is high depends on whether the bit is 0 or 1,
            // but this function always takes the same time (2 us).
            "send_led_strip_bit%=:\n"
    #if F_CPU == 8000000
            "rol __tmp_reg__\n"                      // Rotate left through carry.
    #endif
            "sbi %[port], %[pin]\n"                           // Drive the line high.
    #if F_CPU != 8000000
            "rol __tmp_reg__\n"                      // Rotate left through carry.
    #endif

    #if F_CPU == 16000000
            "nop\n" "nop\n"
    #elif F_CPU == 20000000
            "nop\n" "nop\n" "nop\n" "nop\n"
    #endif

            "brcs .+2\n"
            "cbi %[port], %[pin]\n"              // If the bit to send is 0, drive the line low now.

    #if F_CPU == 8000000
            "nop\n" "nop\n"
    #elif F_CPU == 16000000
            "nop\n" "nop\n" "nop\n" "nop\n" "nop\n"
    #elif F_CPU == 20000000
            "nop\n" "nop\n" "nop\n" "nop\n" "nop\n"
            "nop\n" "nop\n"
    #endif
            "brcc .+2\n" "cbi %[port], %[pin]\n"              // If the bit to send is 1, drive the line low now.
            "ret\n"
            "led_strip_asm_end%=:"
            :
            : [col] "z" (colors),        
            [port] "I" (pinAddr[pin]),   // %2 is the port register (e.g. PORTC)
            [pin]  "I" (pinBit[pin])     // %3 is the pin number (0-8)
        );
        colors=colors->next;
    }
    sei();      //re-enable interrupts
}

void WS2812B::LEDStrip::write(int pin) {
    this->writeRange(pin, this->size);
}

void WS2812B::initLEDStrip(LED* lights, unsigned int size) {
    for(int i=size-1;i>=0;i--) {
        //create circular linked list of LEDs
        lights[i].next=&lights[(i+1)%size];
    }
}

#endif