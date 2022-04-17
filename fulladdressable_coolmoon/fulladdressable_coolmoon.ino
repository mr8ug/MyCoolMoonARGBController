
//#include "FastLED.h"
#include <Adafruit_NeoPixel.h>
#define NUM_LEDS 48
#define PIN 6

Adafruit_NeoPixel fans = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel cpu_cooler = Adafruit_NeoPixel(16, 4, NEO_GRB + NEO_KHZ800);

//CRGB leds[NUM_LEDS];

//display
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

#include <EEPROM.h>
int effect;
int address = 0;

byte value;
int counterMessage;

byte pallette[10][3] = {
  {byte(200), byte(200), byte(255)}, //blanco 0
  {byte(255), byte(0), byte(0)},//rojo 1
  {byte(255), byte(84), byte(0)},//naranja 2
  {byte(255), byte(255), byte(0)},//amarillo 3
  {byte(0), byte(0), byte(255)},//azul 4
  {byte(43), byte(134), byte(193)},//sky 5
  {byte(0), byte(255), byte(0)},//verde 6
  {byte(0), byte(255), byte(85)},//verde-azulado 7
  {byte(144), byte(0), byte(255)},//morado 8
  {byte(255), byte(0), byte(122)}//pink 9
};

void setup() {
  // put your setup code here, to run once:
  //FastLED.addLeds<WS2812B, PIN, GRB>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  //FastLED.addLeds<WS2812B, 4, GRB>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  //FastLED.setBrightness( 200 );
  fans.begin();
  fans.show();

  cpu_cooler.begin();
  cpu_cooler.show();
  //actualiza al hacer el reset
  value = EEPROM.read(address);
  effect = int(value);
  if (effect < 11 ) {
    value = byte(int(value) + 1);
    EEPROM.update(address, value);
    if (effect == 10) {
      EEPROM.update(address, byte(0));
    }

  }
  counterMessage = 0; //this will show only once the lcd message to avoid data sending to many times.
  lcd.init();
  lcd.backlight();
  lcd.clear();
  //  lcd.setCursor(0, 0);
  //  lcd.print("CoolMoon ARGB");
  //  lcd.setCursor(0, 1);
  //  lcd.print("By MR8UG");
  M_Letter();
  delay(500);
  R_Letter();
  delay(500);
  B_Letter();
  delay(500);
  U_Letter();
  delay(500);
  G_Letter();
  delay(500);

}

void loop() {
  // put your main code here, to run repeatedly:
  //tiro un dado que elija el color random de 0-10 que es la cantidad de colores en mi paleta
  int color = round(random(100) / 10);
  //int color = 0;
  byte r = pallette[color][0];
  byte g = pallette[color][1];
  byte b = pallette[color][2];

  //
  if (effect == 0) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Efecto #0");
    lcd.setCursor(0, 1);
    lcd.print("METEOR RAIN");
    meteorRain(r, g, b, 2, 50, true, 30);
  }
  //
  if (effect == 1) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Efecto #0");
    lcd.setCursor(0, 1);
    lcd.print("BOUNCING BALLS");
    BouncingBalls(r, g, b, 2);
  }
  //
  if (effect == 2) {

    if (counterMessage == 0) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Efecto #2");
      lcd.setCursor(0, 1);
      lcd.print("FIRE");
      counterMessage = 1;
    }

    Fire(25, 60, 25);
  }
  if (effect == 3) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Efecto #3");
    lcd.setCursor(0, 1);
    lcd.print("SNOW SPARKLE");
    SnowSparkle(0x10, 0x10, 0x10, 20, random(100, 500));
  }
  if (effect == 4) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Efecto #4");
    lcd.setCursor(0, 1);
    lcd.print("RAINBOW CYCLE");
    rainbowCycle(10);
  }
  if (effect == 5) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Efecto #5");
    lcd.setCursor(0, 1);
    lcd.print("RAINBOW CYCLE 2");
    rainbowCycle2(5);
  }
  if (effect == 6) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Efecto #6");
    lcd.setCursor(0, 1);
    lcd.print("NEW KITT");
    NewKITT(r, g, b, 4, 40, 50);
  }
  if (effect == 7) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Efecto #7");
    lcd.setCursor(0, 1);
    lcd.print("THEATHER CHASE");
    theaterChaseRainbow(60);
  }
  if (effect == 8) {

    if (counterMessage == 0) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Efecto #8");
      lcd.setCursor(0, 1);
      lcd.print("ICE");
      counterMessage = 1;
    }
    Ice(25, 60, 25);
  }
  if (effect == 9) {

    if (counterMessage == 0) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Efecto #9");
      lcd.setCursor(0, 1);
      lcd.print("FOREST");
      counterMessage = 1;
    }
    Forest(25, 60, 25);
  }

  if (effect == 10) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Efecto #10");
    lcd.setCursor(0, 1);
    lcd.print("RANDOM");
    int randomEffect = round(random(0,70) / 10);
    if (randomEffect == 0) {
      meteorRain(r, g, b, 2, 50, true, 30);
    }
    if (randomEffect == 1) {
      Fire(25, 60, 25);
    }
    if (randomEffect == 2) {
      SnowSparkle(r, g, b, 20, random(100, 500));
    }
    if (randomEffect == 3) {
      rainbowCycle(10);
    }
    if (randomEffect == 4) {
      rainbowCycle2(5);
    }
    if (randomEffect == 5) {
      NewKITT(r, g, b, 4, 40, 50);
    }
    if (randomEffect == 6) {
      Ice(25, 60, 25);
    }
    if (randomEffect == 7) {
      Forest(25, 60, 25);
    }

  }
}

void showStrip() {
#ifdef ADAFRUIT_NEOPIXEL_H
  // NeoPixel
  fans.show();
  cpu_cooler.show();
#endif
#ifndef ADAFRUIT_NEOPIXEL_H
  // FastLED
  FastLED.show();
#endif
}

void setPixel(int Pixel, byte red, byte green, byte blue) {

#ifdef ADAFRUIT_NEOPIXEL_H
  // NeoPixel
  fans.setPixelColor(Pixel, fans.Color(red, green, blue));
  if (Pixel <=47 && Pixel >=0){
    cpu_cooler.setPixelColor(Pixel-32, cpu_cooler.Color(red, green, blue));
  }
  
  
#endif
#ifndef ADAFRUIT_NEOPIXEL_H
  // FastLED
  leds[Pixel].r = red;
  leds[Pixel].g = green;
  leds[Pixel].b = blue;
#endif
}

void setPixelStrip(int Pixel, byte red, byte green , byte blue) {
  //NeoPixel

}

void setAll(byte red, byte green, byte blue) {

  for (int i = 0; i < NUM_LEDS; i++ ) {

    setPixel(i, red, green, blue);
  }
  showStrip();
}

//EFFECT 1 METEOR ARGB 2 CLOCKWISE - UNDERCLOCKWISE
void meteorRain(byte red, byte green, byte blue, byte meteorSize, byte meteorTrailDecay, boolean meteorRandomDecay, int SpeedDelay) {
  int remap[48] = {
    9, 10, 11, 12,  13, 14, 15, 0,    1, 24, 23, 22,  21, 20, 19, 18,
    17, 42, 34, 43,  35, 44, 36, 45,  37, 46, 38, 47,  39, 32, 40, 33,
    41, 16, 31, 30,  29, 28, 27, 26,  25, 2, 3, 4,    5, 6, 7, 8



  };
  setAll(0, 0, 0);


  for (int i = NUM_LEDS; i > 0; i--) {


    // fade brightness all LEDs one step
    for (int j = 0; j < NUM_LEDS; j++) {
      if ( (!meteorRandomDecay) || (random(10) > 5) ) {
        fadeToBlack(remap[j], meteorTrailDecay );

      }
    }

    // draw meteor
    for (int j = 0; j < meteorSize; j++) {
      if ( ( i - j < NUM_LEDS) && (i - j >= 0) ) {
        setPixel(remap[i - j], red, green, blue);

      }
    }

    showStrip();
    delay(SpeedDelay);
  }
}

void fadeToBlack(int ledNo, byte fadeValue) {
#ifdef ADAFRUIT_NEOPIXEL_H
  // NeoPixel
  uint32_t oldColor;
  uint8_t r, g, b;
  int value;

  oldColor = fans.getPixelColor(ledNo);
  r = (oldColor & 0x00ff0000UL) >> 16;
  g = (oldColor & 0x0000ff00UL) >> 8;
  b = (oldColor & 0x000000ffUL);

  r = (r <= 10) ? 0 : (int) r - (r * fadeValue / 256);
  g = (g <= 10) ? 0 : (int) g - (g * fadeValue / 256);
  b = (b <= 10) ? 0 : (int) b - (b * fadeValue / 256);

  fans.setPixelColor(ledNo, r, g, b);
#endif
#ifndef ADAFRUIT_NEOPIXEL_H
  // FastLED
  leds[ledNo].fadeToBlackBy( fadeValue );
#endif
}

//effect 2
void BouncingBalls(byte red, byte green, byte blue, int BallCount) {
  int remap[48] = {
    9, 10, 11, 12,  13, 14, 15, 0, 1, 24, 23, 22, 21, 20, 19, 18,
    17, 42, 34, 43,  35, 44, 36, 45,  37, 46, 38, 47,  39, 32, 40, 33,
    41, 16, 31, 30,  29, 28, 27, 26,  25, 2, 3, 4, 5, 6, 7, 8

  };



  float Gravity = -1.81;
  int StartHeight = 1;

  float Height[BallCount];
  float ImpactVelocityStart = sqrt( -2 * Gravity * StartHeight );
  float ImpactVelocity[BallCount];
  float TimeSinceLastBounce[BallCount];
  int   Position[BallCount];
  long  ClockTimeSinceLastBounce[BallCount];
  float Dampening[BallCount];

  for (int i = 0 ; i < BallCount ; i++) {
    ClockTimeSinceLastBounce[i] = millis();
    Height[i] = StartHeight;
    Position[i] = 0;
    ImpactVelocity[i] = ImpactVelocityStart;
    TimeSinceLastBounce[i] = 0;
    Dampening[i] = 0.90 - float(i) / pow(BallCount, 2);

  }
  int color = round(random(100) / 10);
  //int color = 0;
  byte r = pallette[color][0];
  byte g = pallette[color][1];
  byte b = pallette[color][2];
  while (true) {
    for (int i = 0 ; i < BallCount ; i++) {
      TimeSinceLastBounce[i] =  millis() - ClockTimeSinceLastBounce[i];
      Height[i] = 0.5 * Gravity * pow( TimeSinceLastBounce[i] / 1000 , 2.0 ) + ImpactVelocity[i] * TimeSinceLastBounce[i] / 1000;

      if ( Height[i] < 0 ) {
        Height[i] = 0;
        ImpactVelocity[i] = Dampening[i] * ImpactVelocity[i];
        ClockTimeSinceLastBounce[i] = millis();

        if ( ImpactVelocity[i] < 0.01 ) {
          ImpactVelocity[i] = ImpactVelocityStart;
        }
      }
      Position[i] = round( Height[i] * (NUM_LEDS - 1) / StartHeight);
    }

    for (int i = 0 ; i < BallCount ; i++) {
      setPixel(remap[Position[i]], r, g, b);
    }

    showStrip();
    setAll(0, 0, 0);
  }
}

//effect 3
void Fire(int Cooling, int Sparking, int SpeedDelay) {

  static byte heat[NUM_LEDS];
  int cooldown;

  // Step 1.  Cool down every cell a little
  for ( int i = 0; i < NUM_LEDS; i++) {
    cooldown = random(0, ((Cooling * 10) / NUM_LEDS) + 2);

    if (cooldown > heat[i]) {
      heat[i] = 0;
    } else {
      heat[i] = heat[i] - cooldown;
    }
  }

  // Step 2.  Heat from each cell drifts 'up' and diffuses a little
  for ( int k = NUM_LEDS - 1; k >= 2; k--) {
    heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2]) / 3;
  }

  // Step 3.  Randomly ignite new 'sparks' near the bottom
  if ( random(255) < Sparking ) {
    int y = random(7);
    heat[y] = heat[y] + random(160, 255);
    //heat[y] = random(160,255);
  }

  // Step 4.  Convert heat to LED colors
  for ( int j = 0; j < NUM_LEDS; j++) {
    setPixelHeatColor(j, heat[j] );
  }

  showStrip();
  delay(SpeedDelay);
}

void setPixelHeatColor (int Pixel, byte temperature) {
  int remap[48] = {
    9, 8, 10, 7,  11, 6, 12, 5,  13, 4, 14, 3,  15, 2, 0, 1,
    25, 24, 26, 23, 27, 22, 28, 21,  29, 20, 30, 19,  31, 18, 16, 17,
    41, 40, 42, 39, 42, 38, 44, 37, 45, 36, 46, 35, 47, 34, 32, 33
  };
  // Scale 'heat' down from 0-255 to 0-191
  byte t192 = round((temperature / 255.0) * 191);

  // calculate ramp up from
  byte heatramp = t192 & 0x3F; // 0..63
  heatramp <<= 2; // scale up to 0..252

  // figure out which third of the spectrum we're in:
  if ( t192 > 0x80) {                    // hottest
    setPixel(remap[Pixel], 255, 255, heatramp);
  } else if ( t192 > 0x40 ) {            // middle
    setPixel(remap[Pixel], 255, heatramp, 0);
  } else {                               // coolest
    setPixel(remap[Pixel], heatramp, 0, 0);
  }
}

//effect 4
void SnowSparkle(byte red, byte green, byte blue, int SparkleDelay, int SpeedDelay) {
  setAll(red, green, blue);

  int Pixel = random(NUM_LEDS);
  setPixel(Pixel, 0xff, 0xff, 0xff);
  showStrip();
  delay(SparkleDelay);
  for ( int i = 0; i < NUM_LEDS; i++) {
    setPixel(Pixel, red, green, blue);
    delay(50);
    showStrip();
  }

}

//effect 5
void rainbowCycle(int SpeedDelay) {
  int remap[48] = {
    9, 8, 10, 7,  11, 6, 12, 5,  13, 4, 14, 3,  15, 2, 0, 1,
    25, 24, 26, 23, 27, 22, 28, 21,  29, 20, 30, 19,  31, 18, 16, 17,
    41, 40, 42, 39, 42, 38, 44, 37, 45, 36, 46, 35, 47, 34, 32, 33
  };
  byte *c;
  uint16_t i, j;

  for (j = 0; j < 256 * 1; j++) { // 3 cycles of all colors on wheel
    for (i = 0; i < NUM_LEDS; i++) {
      c = Wheel(((i * 256 / NUM_LEDS) + j) & 255);
      setPixel(remap[i], *c, *(c + 1), *(c + 2));
    }
    showStrip();
    delay(SpeedDelay);
  }
}

//effect 6
void rainbowCycle2(int SpeedDelay) {

  int remap[48] = {
    9, 10, 11, 12,  13, 14, 15, 0, 1, 24, 23, 22, 21, 20, 19, 18,
    //17, 42, 43, 44,  45, 46, 47, 32,  33, 34, 35, 36,  37, 38, 39, 40,
    17, 42, 34, 43,  35, 44, 36, 45,  37, 46, 38, 47,  39, 32, 40, 33,
    41, 16, 31, 30,  29, 28, 27, 26,  25, 2, 3, 4, 5, 6, 7, 8

  };
  byte *c;
  uint16_t i, j;

  for (j = 0; j < 256 * 5; j++) { // 3 cycles of all colors on wheel
    for (i = 0; i < NUM_LEDS; i++) {
      c = Wheel(((i * 256 / NUM_LEDS) + j) & 255);
      setPixel(remap[i], *c, *(c + 1), *(c + 2));
    }
    showStrip();
    delay(SpeedDelay);
  }
}

byte * Wheel(byte WheelPos) {
  static byte c[3];

  if (WheelPos < 85) {
    c[0] = WheelPos * 3;
    c[1] = 255 - WheelPos * 3;
    c[2] = 0;
  } else if (WheelPos < 170) {
    WheelPos -= 85;
    c[0] = 255 - WheelPos * 3;
    c[1] = 0;
    c[2] = WheelPos * 3;
  } else {
    WheelPos -= 170;
    c[0] = 0;
    c[1] = WheelPos * 3;
    c[2] = 255 - WheelPos * 3;
  }

  return c;
}


void NewKITT(byte red, byte green, byte blue, int EyeSize, int SpeedDelay, int ReturnDelay) {
  RightToLeft(red, green, blue, EyeSize, SpeedDelay, ReturnDelay);
  LeftToRight(red, green, blue, EyeSize, SpeedDelay, ReturnDelay);
  OutsideToCenter(red, green, blue, EyeSize, SpeedDelay, ReturnDelay);
  CenterToOutside(red, green, blue, EyeSize, SpeedDelay, ReturnDelay);
  LeftToRight(red, green, blue, EyeSize, SpeedDelay, ReturnDelay);
  RightToLeft(red, green, blue, EyeSize, SpeedDelay, ReturnDelay);
  OutsideToCenter(red, green, blue, EyeSize, SpeedDelay, ReturnDelay);
  CenterToOutside(red, green, blue, EyeSize, SpeedDelay, ReturnDelay);
}

void CenterToOutside(byte red, byte green, byte blue, int EyeSize, int SpeedDelay, int ReturnDelay) {
  int remap[48] = {
    9, 10, 11, 12,  13, 14, 15, 0, 1, 24, 23, 22, 21, 20, 19, 18,
    17, 42, 34, 43,  35, 44, 36, 45,  37, 46, 38, 47,  39, 32, 40, 33,
    41, 16, 31, 30,  29, 28, 27, 26,  25, 2, 3, 4, 5, 6, 7, 8

  };
  for (int i = ((NUM_LEDS - EyeSize) / 2); i > 0; i--) {
    setAll(0, 0, 0);

    setPixel(remap[i], red / 10, green / 10, blue / 10);
    for (int j = 1; j <= EyeSize; j++) {
      setPixel(remap[i + j], red, green, blue);
    }
    setPixel(remap[i + EyeSize + 1], red / 10, green / 10, blue / 10);

    setPixel(remap[NUM_LEDS - i], red / 10, green / 10, blue / 10);
    for (int j = 1; j <= EyeSize; j++) {
      setPixel(remap[NUM_LEDS - i - j], red, green, blue);
    }
    setPixel(remap[NUM_LEDS - i - EyeSize - 1], red / 10, green / 10, blue / 10);

    showStrip();
    delay(SpeedDelay);
  }
  delay(ReturnDelay);
}

void OutsideToCenter(byte red, byte green, byte blue, int EyeSize, int SpeedDelay, int ReturnDelay) {
  int remap[48] = {
    9, 10, 11, 12,  13, 14, 15, 0, 1, 24, 23, 22, 21, 20, 19, 18,
    17, 42, 34, 43,  35, 44, 36, 45,  37, 46, 38, 47,  39, 32, 40, 33,
    41, 16, 31, 30,  29, 28, 27, 26,  25, 2, 3, 4, 5, 6, 7, 8

  };
  for (int i = 0; i <= ((NUM_LEDS - EyeSize) / 2); i++) {
    setAll(0, 0, 0);

    setPixel(remap[i], red / 10, green / 10, blue / 10);
    for (int j = 1; j <= EyeSize; j++) {
      setPixel(remap[i + j], red, green, blue);
    }
    setPixel(remap[i + EyeSize + 1], red / 10, green / 10, blue / 10);

    setPixel(remap[NUM_LEDS - i], red / 10, green / 10, blue / 10);
    for (int j = 1; j <= EyeSize; j++) {
      setPixel(remap[NUM_LEDS - i - j], red, green, blue);
    }
    setPixel(remap[NUM_LEDS - i - EyeSize - 1], red / 10, green / 10, blue / 10);

    showStrip();
    delay(SpeedDelay);
  }
  delay(ReturnDelay);
}

void LeftToRight(byte red, byte green, byte blue, int EyeSize, int SpeedDelay, int ReturnDelay) {
  int remap[48] = {
    9, 10, 11, 12,  13, 14, 15, 0, 1, 24, 23, 22, 21, 20, 19, 18,
    17, 42, 34, 43,  35, 44, 36, 45,  37, 46, 38, 47,  39, 32, 40, 33,
    41, 16, 31, 30,  29, 28, 27, 26,  25, 2, 3, 4, 5, 6, 7, 8

  };
  for (int i = 0; i < NUM_LEDS - EyeSize - 2; i++) {
    setAll(0, 0, 0);
    setPixel(remap[i], red / 10, green / 10, blue / 10);
    for (int j = 1; j <= EyeSize; j++) {
      setPixel(remap[i + j], red, green, blue);
    }
    setPixel(remap[i + EyeSize + 1], red / 10, green / 10, blue / 10);
    showStrip();
    delay(SpeedDelay);
  }
  delay(ReturnDelay);
}

void RightToLeft(byte red, byte green, byte blue, int EyeSize, int SpeedDelay, int ReturnDelay) {
  int remap[48] = {
    9, 10, 11, 12,  13, 14, 15, 0, 1, 24, 23, 22, 21, 20, 19, 18,
    17, 42, 34, 43,  35, 44, 36, 45,  37, 46, 38, 47,  39, 32, 40, 33,
    41, 16, 31, 30,  29, 28, 27, 26,  25, 2, 3, 4, 5, 6, 7, 8

  };
  for (int i = NUM_LEDS - EyeSize - 2; i > 0; i--) {
    setAll(0, 0, 0);
    setPixel(remap[i], red / 10, green / 10, blue / 10);
    for (int j = 1; j <= EyeSize; j++) {
      setPixel(remap[i + j], red, green, blue);
    }
    setPixel(remap[i + EyeSize + 1], red / 10, green / 10, blue / 10);
    showStrip();
    delay(SpeedDelay);
  }
  delay(ReturnDelay);
}

//effect 7
void theaterChaseRainbow(int SpeedDelay) {
  byte *c;

  for (int j = 0; j < 256; j++) {   // cycle all 256 colors in the wheel
    for (int q = 0; q < 3; q++) {
      for (int i = 0; i < NUM_LEDS; i = i + 3) {
        c = Wheel( (i + j) % 255);
        setPixel(i + q, *c, *(c + 1), *(c + 2)); //turn every third pixel on
      }
      showStrip();

      delay(SpeedDelay);

      for (int i = 0; i < NUM_LEDS; i = i + 3) {
        setPixel(i + q, 0, 0, 0);    //turn every third pixel off
      }
    }
  }
}


//effect 8
void Ice(int Cooling, int Sparking, int SpeedDelay) {

  static byte heat[NUM_LEDS];
  int cooldown;

  // Step 1.  Cool down every cell a little
  for ( int i = 0; i < NUM_LEDS; i++) {
    cooldown = random(0, ((Cooling * 10) / NUM_LEDS) + 2);

    if (cooldown > heat[i]) {
      heat[i] = 0;
    } else {
      heat[i] = heat[i] - cooldown;
    }
  }

  // Step 2.  Heat from each cell drifts 'up' and diffuses a little
  for ( int k = NUM_LEDS - 1; k >= 2; k--) {
    heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2]) / 3;
  }

  // Step 3.  Randomly ignite new 'sparks' near the bottom
  if ( random(255) < Sparking ) {
    int y = random(7);
    heat[y] = heat[y] + random(160, 255);
    //heat[y] = random(160,255);
  }

  // Step 4.  Convert heat to LED colors
  for ( int j = 0; j < NUM_LEDS; j++) {
    setPixelIceColor(j, heat[j] );
  }

  showStrip();
  delay(SpeedDelay);
}

void setPixelIceColor (int Pixel, byte temperature) {
  int remap[48] = {
    9, 8, 10, 7,  11, 6, 12, 5,  13, 4, 14, 3,  15, 2, 0, 1,
    25, 24, 26, 23, 27, 22, 28, 21,  29, 20, 30, 19,  31, 18, 16, 17,
    41, 40, 42, 39, 42, 38, 44, 37, 45, 36, 46, 35, 47, 34, 32, 33
  };
  // Scale 'heat' down from 0-255 to 0-191
  byte t192 = round((temperature / 255.0) * 191);

  // calculate ramp up from
  byte heatramp = t192 & 0x3F; // 0..63
  heatramp <<= 2; // scale up to 0..252

  // figure out which third of the spectrum we're in:
  if ( t192 > 0x80) {                    // hottest
    setPixel(remap[Pixel], heatramp, 255, 255 );
  } else if ( t192 > 0x40 ) {            // middle
    setPixel(remap[Pixel], 0, heatramp, 255);
  } else {                               // coolest
    setPixel(remap[Pixel], 0, 0, heatramp);
  }
}

//effect 8
void Forest(int Cooling, int Sparking, int SpeedDelay) {

  static byte heat[NUM_LEDS];
  int cooldown;

  // Step 1.  Cool down every cell a little
  for ( int i = 0; i < NUM_LEDS; i++) {
    cooldown = random(0, ((Cooling * 10) / NUM_LEDS) + 2);

    if (cooldown > heat[i]) {
      heat[i] = 0;
    } else {
      heat[i] = heat[i] - cooldown;
    }
  }

  // Step 2.  Heat from each cell drifts 'up' and diffuses a little
  for ( int k = NUM_LEDS - 1; k >= 2; k--) {
    heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2]) / 3;
  }

  // Step 3.  Randomly ignite new 'sparks' near the bottom
  if ( random(255) < Sparking ) {
    int y = random(7);
    heat[y] = heat[y] + random(160, 255);
    //heat[y] = random(160,255);
  }

  // Step 4.  Convert heat to LED colors
  for ( int j = 0; j < NUM_LEDS; j++) {
    setPixelForestColor(j, heat[j] );
  }

  showStrip();
  delay(SpeedDelay);
}

void setPixelForestColor (int Pixel, byte temperature) {
  int remap[48] = {
    9, 8, 10, 7,  11, 6, 12, 5,  13, 4, 14, 3,  15, 2, 0, 1,
    25, 24, 26, 23, 27, 22, 28, 21,  29, 20, 30, 19,  31, 18, 16, 17,
    41, 40, 42, 39, 42, 38, 44, 37, 45, 36, 46, 35, 47, 34, 32, 33
  };
  // Scale 'heat' down from 0-255 to 0-191
  byte t192 = round((temperature / 255.0) * 191);

  // calculate ramp up from
  byte heatramp = t192 & 0x3F; // 0..63
  heatramp <<= 2; // scale up to 0..252

  // figure out which third of the spectrum we're in:
  if ( t192 > 0x80) {                    // hottest
    setPixel(remap[Pixel], 255 , 255, heatramp );
  } else if ( t192 > 0x40 ) {            // middle
    setPixel(remap[Pixel], 0, 255, heatramp);
  } else {                               // coolest
    setPixel(remap[Pixel], 0, heatramp, 0 );
  }
}

void M_Letter() {
  lcd.clear();
  byte image04[8] = {B11000, B11100, B11110, B11010, B11011, B11011, B11001, B11001};
  byte image20[8] = {B11000, B11000, B11000, B11000, B11000, B11000, B11000, B11000};
  byte image05[8] = {B00011, B00111, B01111, B01011, B11011, B11011, B10011, B10011};
  byte image21[8] = {B00011, B00011, B00011, B00011, B00011, B00011, B00011, B00011};

  lcd.createChar(0, image04);
  lcd.createChar(1, image20);
  lcd.createChar(2, image05);
  lcd.createChar(3, image21);

  lcd.setCursor(3, 0);
  lcd.write(byte(0));
  lcd.setCursor(3, 1);
  lcd.write(byte(1));
  lcd.setCursor(4, 0);
  lcd.write(byte(2));
  lcd.setCursor(4, 1);
  lcd.write(byte(3));
}

void R_Letter() {
  lcd.clear();
  byte image06[8] = {B11111, B11111, B11000, B11000, B11000, B11000, B11000, B11001};
  byte image22[8] = {B11001, B11001, B11001, B11000, B11000, B11000, B11000, B11000};
  byte image07[8] = {B11110, B11111, B00011, B00011, B00011, B00011, B00111, B11110};
  byte image23[8] = {B10000, B10000, B11000, B11100, B01100, B01110, B00111, B00011};

  lcd.createChar(0, image06);
  lcd.createChar(1, image22);
  lcd.createChar(2, image07);
  lcd.createChar(3, image23);

  lcd.setCursor(5, 0);
  lcd.write(byte(0));
  lcd.setCursor(5, 1);
  lcd.write(byte(1));
  lcd.setCursor(6, 0);
  lcd.write(byte(2));
  lcd.setCursor(6, 1);
  lcd.write(byte(3));

}


void B_Letter() {
  lcd.clear();

  byte image08[8] = {B00111, B01111, B11110, B11100, B11100, B11110, B01111, B00111};
  byte image09[8] = {B11100, B11110, B01111, B00111, B00111, B01111, B11110, B11100};
  byte image24[8] = {B00111, B01111, B11110, B11100, B11100, B11110, B01111, B00111};
  byte image25[8] = {B11100, B11110, B01111, B00111, B00111, B01111, B11110, B11100};

  lcd.createChar(0, image08);
  lcd.createChar(1, image09);
  lcd.createChar(2, image24);
  lcd.createChar(3, image25);

  lcd.setCursor(7, 0);
  lcd.write(byte(0));
  lcd.setCursor(8, 0);
  lcd.write(byte(1));
  lcd.setCursor(7, 1);
  lcd.write(byte(2));
  lcd.setCursor(8, 1);
  lcd.write(byte(3));

}


void U_Letter() {

  lcd.clear();

  byte image10[8] = {B11000, B11000, B11000, B11000, B11000, B11000, B11000, B11000};
  byte image26[8] = {B11000, B11000, B11000, B11000, B11000, B01100, B00111, B00011};
  byte image27[8] = {B00011, B00011, B00011, B00011, B00011, B00110, B11100, B11000};
  byte image11[8] = {B00011, B00011, B00011, B00011, B00011, B00011, B00011, B00011};

  lcd.createChar(0, image10);
  lcd.createChar(1, image26);
  lcd.createChar(2, image27);
  lcd.createChar(3, image11);

  lcd.setCursor(9, 0);
  lcd.write(byte(0));
  lcd.setCursor(9, 1);
  lcd.write(byte(1));
  lcd.setCursor(10, 1);
  lcd.write(byte(2));
  lcd.setCursor(10, 0);
  lcd.write(byte(3));
}


void G_Letter() {
  lcd.clear();

  byte image12[8] = {B00111, B01111, B11000, B11000, B11000, B11000, B11000, B11001};
  byte image28[8] = {B11001, B11001, B11000, B11000, B11000, B11000, B01111, B00111};
  byte image29[8] = {B11111, B10011, B00011, B00011, B00011, B00011, B11110, B11100};
  byte image13[8] = {B11100, B11110, B00011, B00000, B00000, B00000, B00000, B11110};

  lcd.createChar(0, image12);
  lcd.createChar(1, image28);
  lcd.createChar(2, image29);
  lcd.createChar(3, image13);

  lcd.setCursor(11, 0);
  lcd.write(byte(0));
  lcd.setCursor(11, 1);
  lcd.write(byte(1));
  lcd.setCursor(12, 1);
  lcd.write(byte(2));
  lcd.setCursor(12, 0);
  lcd.write(byte(3));

}
