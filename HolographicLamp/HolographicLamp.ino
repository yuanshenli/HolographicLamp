// This is a demonstration on how to use an input device to trigger changes on your neo pixels.
// You should wire a momentary push button to connect from ground to a digital IO pin.  When you
// press the button it will change to a new pixel animation.  Note that you need to press the
// button once to start the first animation!

#include <Adafruit_NeoPixel.h>

#define BUTTON_PIN   22    // Digital IO pin connected to the button.  This will be
                          // driven with a pull-up resistor so the switch should
                          // pull the pin to ground momentarily.  On a high -> low
                          // transition the button press logic will execute.

#define PIXEL_PIN    6    // Digital IO pin connected to the NeoPixels.
#define rPin 17
#define gPin 18
#define bPin 19

#define PIXEL_COUNT 8

// Parameter 1 = number of pixels in strip,  neopixel stick has 8
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_RGB     Pixels are wired for RGB bitstream
//   NEO_GRB     Pixels are wired for GRB bitstream, correct for neopixel stick
//   NEO_KHZ400  400 KHz bitstream (e.g. FLORA pixels)
//   NEO_KHZ800  800 KHz bitstream (e.g. High Density LED strip), correct for neopixel stick
Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN, NEO_GRB + NEO_KHZ800);

bool oldState = HIGH;
int showType = 0;
int state = 0;
int LastStateTime = millis();
static int ThisStateTime = millis();
void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(rPin, INPUT_PULLUP);
  pinMode(gPin, INPUT_PULLUP);
  pinMode(bPin, INPUT_PULLUP);
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  Serial.begin(115200);
}

int clear() {
  while(Serial.peek() == ' ' || Serial.peek() == '\r') {
    Serial.read();
  }
  return Serial.available();
}

int getInt(int& x) {
  char next_char = Serial.peek();
  if (next_char == '\n') {
//    Serial.println("hit enter, reset!");
    return -1;
  } else {
    x = Serial.parseInt();
    return 0;
  }
}

void loop() {
  if (clear()>0) {
      if (Serial.peek() == '\n') {
        Serial.read();
        return;
       }
      Serial.println("loop");
      int rVal, gVal, bVal;

      rVal = Serial.parseInt(); // 0 to 255
      if(getInt(gVal)) return; // 0 to 255
      if(getInt(bVal)) return; // 0 to 255
    
      colorWipe(strip.Color(rVal, gVal, bVal));
    
    }
}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
  }
}
//
//void setIndividualColor(uint16_t i, uint32_t c) {
//  if (i >= strip.numPixels) {
//    return;
//  }
//  strip.setPixelColor(i, c);
//  strip.show();
//}

