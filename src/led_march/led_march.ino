/*
  LED March — one LED at a time walks down a WS28xx strip
  --------------------------------------------------------
  Library: FastLED
  Board:   any (Uno/Nano/ESP8266/ESP32/etc.) — set LED_PIN for your wiring

  Behavior (repeats forever):
    1. Light START_LED
    2. Every STEP_MS, turn the current LED off and light the next one
    3. After the last LED (NUM_LEDS - 1), go dark for RESTART_PAUSE_MS,
       then start again at START_LED

  Non-blocking millis()-based, so it can live alongside other code in loop().
*/

#include <FastLED.h>

// ------------------------------ USER TUNABLES ------------------------------

#define LED_PIN           D5          // data pin driving the strip
#define LED_TYPE          WS2812B     // e.g. WS2811, WS2812, WS2812B, SK6812...
#define COLOR_ORDER       GRB         // swap if colors look wrong (e.g. RGB)
#define BRIGHTNESS        20          // global brightness, 0-255

#define NUM_LEDS          20          // total LEDs on the string
#define START_LED         0           // first LED of the march (0-based)

#define STEP_MS           100         // ms each LED stays lit before moving on
#define RESTART_PAUSE_MS  100         // dark pause after the last LED, before repeating

#define MARCH_COLOR       CRGB::Blue  // color of the marching LED

// -----------------------------------------------------------------------------

CRGB leds[NUM_LEDS];

int currentLed = START_LED;
bool pausing = false;
unsigned long lastStepTime = 0;

void setup() {
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
  FastLED.clear(true);

  leds[currentLed] = MARCH_COLOR;
  FastLED.show();
  lastStepTime = millis();
}

void loop() {
  unsigned long now = millis();

  if (pausing) {
    if (now - lastStepTime >= RESTART_PAUSE_MS) {
      pausing = false;
      currentLed = START_LED;
      leds[currentLed] = MARCH_COLOR;
      FastLED.show();
      lastStepTime = now;
    }
    return;
  }

  if (now - lastStepTime < STEP_MS) return;
  lastStepTime = now;

  leds[currentLed] = CRGB::Black;   // turn off the current LED
  currentLed++;

  if (currentLed >= NUM_LEDS) {     // ran off the end: go dark and pause
    pausing = true;
  } else {
    leds[currentLed] = MARCH_COLOR; // light the next one
  }

  FastLED.show();
}
