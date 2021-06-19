// code for an attiny89 controlled led strip for arcade marquee
// chopped buttoncycler.ino example file from AdafruitNeopixel library
// code and design for Attiny85
// button with 1k resistor to pin 4 then to ground
// led with appropriate resistor to pin 3
// strip to pin 2 

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

#define BUTTON_PIN   4
#define LED_PIN   4
#define PIXEL_PIN    2 
#define PIXEL_COUNT 37  // Number of NeoPixels

Adafruit_NeoPixel strip(PIXEL_COUNT, PIXEL_PIN, NEO_GRB + NEO_KHZ800);

boolean oldState = HIGH;
int     mode     = 0;    // Currently-active animation mode, 0-9

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  strip.begin(); // Initialize NeoPixel strip object (REQUIRED)
  strip.show();  // Initialize all pixels to 'off'
  ledToWhite(128, 1);    // White full
}

void loop() {
  // Get current button state.
  boolean newState = digitalRead(BUTTON_PIN);

  // Check if state changed from high to low (button press).
  if((newState == LOW) && (oldState == HIGH)) {
    // Short delay to debounce button.
    delay(20);
    // Check if button is still low after debounce.
    newState = digitalRead(BUTTON_PIN);
    if(newState == LOW) {      // Yes, still low
      if(++mode > 4) mode = 0; // Advance to next mode, wrap around after #8
      switch(mode) {           // Start the new animation...
        case 0:
          ledToWhite(255, 1);    // White full
          break;
        case 1:
          ledToWhite(192, 1);    // white 3/4
          break;
        case 2:
          ledToWhite(128, 1);    // white 1/2
          break;
        case 3:
          ledToWhite(64, 1);    // white 1/4
          break;
        case 4:
          ledToWhite(0, 1);    // off
          break;      
      }
    }
  }

  // Set the last-read button state to the old state.
  oldState = newState;
}

void ledToWhite(int intensity, int wait) {
  colorWipe(strip.Color(intensity, intensity, intensity), wait);
}

// Fill strip pixels one after another with a color. Strip is NOT cleared
// first; anything there will be covered pixel by pixel. Pass in color
// (as a single 'packed' 32-bit value, which you can get by calling
// strip.Color(red, green, blue) as shown in the loop() function above),
// and a delay time (in milliseconds) between pixels.
void colorWipe(uint32_t color, int wait) {
  for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip...
    strip.setPixelColor(i, color);         //  Set pixel's color (in RAM)
    strip.show();                          //  Update strip to match
    delay(wait);                           //  Pause for a moment
  }
}
