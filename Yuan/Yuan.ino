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
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), Counter, CHANGE);
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  Serial.begin(115200);
}

void Counter() {
  ThisStateTime = millis();
  Serial.println(state);
  Serial.println(ThisStateTime);
  Serial.println(LastStateTime);
  if(ThisStateTime - LastStateTime > 10){
    state += 1;
    state %= 3;
  }
  LastStateTime = ThisStateTime;
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
  startShow(state);
//  manualAdjust();
}

void startShow(int i) {
  switch(i){
    case 0: colorWipe(strip.Color(0, 0, 0));    // Black/off
            break;
    case 1: rainbow(20);
            break;
    case 2: manualAdjust();
            break;
//    case 3: audioIn();
//            break;
            
  }
}

void audioIn() {
  
  
  while(state == 3){
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
}

void manualAdjust(){
  int rVal = 0;
  int gVal = 0;
  int bVal = 0;
  
  while(state == 2){
    rVal = analogRead(rPin);
    gVal = analogRead(gPin);
    bVal = analogRead(bPin);
    rVal = map(rVal, 0, 1023, 0, 255);
    gVal = map(gVal, 0, 1023, 0, 255);
    bVal = map(bVal, 0, 1023, 0, 255);
//    Serial.println(rVal);
//    Serial.println(gVal);
//    Serial.println(bVal);
    
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

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256 && state==1; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    delay(wait);
  }
}


// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}
