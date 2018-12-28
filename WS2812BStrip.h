#ifndef WS2812BStrip_H
#define WS2812BStrip_H

#include <stdint.h>
namespace WS2812B {
    struct LED {
            uint8_t green;
            uint8_t red;
            uint8_t blue;
            struct LED* next;
            LED() {};
            LED(uint8_t r, uint8_t g, uint8_t b) : red(r), green(g), blue(b) {};
        };
    void initLEDStrip(LED* lights, unsigned int size); //expects lights to be array at least as big as size
    class LEDStrip {

        public:
            LED* start;
            unsigned int size;
            LEDStrip(LED* start, unsigned int size);
            void write(int pin);
            void writeRange(int pin, unsigned int count);
    };
};
#endif