# Arduino Library for WS2812B LED Strips
[Based off pololu-led-strip-arduino](https://github.com/pololu/pololu-led-strip-arduino)

## Summary

This is a library for the Arduino for controlling WS2812B LED strips

## Supported Platforms

This library currently supports any board based on the ATmega168,
ATmega328P, ATmega32U4, or ATmega2560 which runs at 8 MHz, 16 MHz, or
20 MHz.

## Getting Started

### Hardware

The LED strip's input connector has two pins that should be connected
to the Arduino.  The LED strip's ground will need to be connected to
one of the Arduino's GND pins, and the LED strip's signal input line
will be need to be connected to one of the Arduino's I/O lines.  The
example sketch assumes the signal line is connected to pin 5.

You will also need to connect a suitable power supply to the LED strip
using one of the power connectors.  The power supply must be at the
right voltage and provide enough current to meet the LED strip's
requirements.

### Software

You can manually install the library:

1. Download the
   [latest version from GitHub](https://github.com/PinkNoize/ws2812B-arduino).
2. Drag the "ws2812B-arduino" folder into the "libraries" directory inside your
   Arduino sketchbook directory. You can view your sketchbook location by
   opening the "File" menu and selecting "Preferences" in the Arduino IDE. If
   there is not already a "libraries" folder in that location, you should make
   the folder yourself.
3. After installing the library, restart the Arduino IDE.

## Example

An example sketch is available that shows how to use the
library. You can access it from the Arduino IDE by opening the
"File" menu, selecting "Examples", and then selecting "ws2812B-arduino". If
you cannot find the example, the library was probably installed
incorrectly and you should retry the installation instructions above.

## Timing Details

~~This library takes about 1.1 ms to update 30 LEDs (1 meter).~~  The LED
strips use a high speed one-wire protocol with relatively strict
timing requirements, so this library disables interrupts to ensure
reliable color transmission.  Unfortunately, disabling the interrupts
causes problems in other libraries that uses interrupts, such as the
`Serial` library and the functions like `millis()` that keep track of
time.

## Documentation

### LED

The library defines a type named `LED` which can be used to represent individual LEDs in the strip. The type is defined like this:

    typedef struct LED {
            uint8_t green;
            uint8_t red;
            uint8_t blue;
            struct LED* next;
            LED() {};
            LED(uint8_t r, uint8_t g, uint8_t b) : red(r), green(g), blue(b) {};
        };

The fields `red`, `green`, and `blue` are numbers between 0 and 255
and represent the brightness of the red, green, and blue color
components respectively.
The field `next` represents the next LED in the LED strip.

### LEDStrip

The library defines a class named `LEDStrip`.

This class has no default constructor and should be initialized with the following constructor:

- `LEDStrip(LED* start, unsigned int size)` <br> Creates an LEDStrip object.  The `start` parameter should be a pointer to a linked list of LED objects.  The `size` parameter is the number of LEDs in the strip.

- `void write(unsigned char pin)`
<br> Writes the colors pointed by the `start` attribute of the LEDStrip object to the LED strip.  The `pin` parameter is an unsigned char should be the number of the Arduino pin that the LED strip's data input line is connected to.  For ATmega2560-based boards such as the Arduino Mega,
only the following pins are usable: 0&ndash;5, 10&ndash;13,
18&ndash;41, and 50&ndash;61 (ports A through G).

- `void writeRange(unsigned char pin, unsigned int count)`
<br> Writes the number of colors specified by `count` at the `start` attribute of the LEDStrip object to the LED strip.  The `pin` parameter follows the same constraints as above.