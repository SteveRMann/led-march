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