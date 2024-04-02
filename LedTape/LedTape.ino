#include <FastLED.h>
 
#define numberOfLEDs 60
#define controlPin 5
 
CRGB leds[numberOfLEDs];
 
void setup() { 
    FastLED.addLeds<WS2812B, controlPin, GRB>(leds, numberOfLEDs);
}
 
void loop() { 
    for (int thisLED = 0; thisLED < numberOfLEDs; thisLED++) {
        leds[thisLED].r = 50;
        leds[thisLED].g = 0;
        leds[thisLED].b = 0;
        FastLED.show();
    }
}
