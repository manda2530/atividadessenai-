#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

Adafruit_NeoPixel ledRGB (1, 48, NEO_GRB); // quantidade de led, pino, tipo

int r = 0;
int g = 0;
int b = 0;

void setup() 
{
  ledRGB.begin();
  ledRGB.setBrightness(255); // 0 ~ 255 intensidade de brilho

  ledRGB.setPixelColor(0,ledRGB.Color(0, 0, 0));
  ledRGB.show();
}

void loop() 
{
   ledRGB.setPixelColor(0,ledRGB.Color(r, g, b));
  ledRGB.show();
   
}
