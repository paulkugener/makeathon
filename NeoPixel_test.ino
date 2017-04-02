#include <Adafruit_NeoPixel.h>

#define PIN 6
#define LENGTH 5

Adafruit_NeoPixel strip = Adafruit_NeoPixel(LENGTH, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  // put your setup code here, to run once:
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  strip.setBrightness(255);
}

void loop() {
  // put your main code here, to run repeatedly:
  for (int i=0; i < LENGTH; i++){
      strip.setPixelColor(i, (int)random(0, 256), (int)random(0, 256), (int)random(0, 256));
   }
   strip.show();
  delay(1000);
}
