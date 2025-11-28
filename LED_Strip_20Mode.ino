#include <Adafruit_NeoPixel.h>

// Konfigurasi LED Strip
#define LED_PIN     6       // pin data led
#define LED_COUNT   11      // jumlah led sesuaikan kebutuhan
#define BRIGHTNESS  100
#define BUTTON_PIN  2      // pin untuk tombol ganti mode (opsional)

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

// Variabel mode
int currentMode = 0;
const int totalModes = 20;       // total mode
unsigned long lastModeChange = 0;
const long modeInterval = 15000;    // ganti mode otomatis tiap 15 detik

void setup() {
  Serial.begin(9600);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  
  strip.begin();
  strip.show();
  strip.setBrightness(BRIGHTNESS);
  
  Serial.println("=== LED Strip WS2812B - Multi Mode By: Haris Sfx` ===");
  Serial.println("Total Mode: 20");
  Serial.println("Mode akan berganti otomatis atau tekan tombol");
}

void loop() {

  if (digitalRead(BUTTON_PIN) == LOW) {
    currentMode = (currentMode + 1) % totalModes;
    Serial.print("Mode: ");
    Serial.println(currentMode);
    delay(300); 
  }
  
  if (millis() - lastModeChange > modeInterval) {
    currentMode = (currentMode + 1) % totalModes;
    lastModeChange = millis();
    Serial.print("Auto Mode: ");
    Serial.println(currentMode);
  }
  
  runMode(currentMode);
}

// ========== MODE SELECTOR ==========
void runMode(int mode) {
  switch(mode) {
    case 0: colorWipe(strip.Color(255, 0, 0), 100); break;
    case 1: rainbow(20); break;
    case 2: rainbowCycle(20); break;
    case 3: theaterChase(strip.Color(127, 127, 127), 50); break;
    case 4: fadeInOut(255, 0, 0, 10); break;
    case 5: colorBounce(strip.Color(255, 255, 0), 80); break;
    case 6: sparkle(255, 255, 255, 50); break;
    case 7: fireEffect(55); break;
    case 8: meteorRain(255, 0, 255, 10, 64, true, 30); break;
    case 9: twinkle(255, 255, 0, 10, 100, false); break;
    case 10: runningLights(255, 0, 0, 50); break;
    case 11: colorChase(strip.Color(0, 255, 255), 100); break;
    case 12: breathingEffect(0, 255, 0); break;
    case 13: policeStrobe(40); break;
    case 14: rainbowPulse(20); break;
    case 15: larsonScanner(255, 0, 0, 50); break;
    case 16: colorWaves(50); break;
    case 17: randomBurst(); break;
    case 18: dualColorChase(strip.Color(255, 0, 0), strip.Color(0, 0, 255), 80); break;
    case 19: stroboscope(255, 255, 255, 10, 50, 1000); break;
  }
}

// ========== EFEK DASAR ==========

void colorWipe(uint32_t color, int wait) {
  for(int i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, color);
    strip.show();
    delay(wait);
  }
}

void rainbow(int wait) {
  for(long firstPixelHue = 0; firstPixelHue < 65536; firstPixelHue += 256) {
    for(int i = 0; i < strip.numPixels(); i++) {
      int pixelHue = firstPixelHue + (i * 65536L / strip.numPixels());
      strip.setPixelColor(i, strip.gamma32(strip.ColorHSV(pixelHue)));
    }
    strip.show();
    delay(wait);
  }
}

void rainbowCycle(int wait) {
  for(int j = 0; j < 256; j++) {
    for(int i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i * 256 / strip.numPixels() + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

void theaterChase(uint32_t color, int wait) {
  for(int a = 0; a < 10; a++) {
    for(int b = 0; b < 3; b++) {
      strip.clear();
      for(int c = b; c < strip.numPixels(); c += 3) {
        strip.setPixelColor(c, color);
      }
      strip.show();
      delay(wait);
    }
  }
}

void fadeInOut(int red, int green, int blue, int wait) {
  for(int k = 0; k < 256; k++) {
    int r = (k/256.0) * red;
    int g = (k/256.0) * green;
    int b = (k/256.0) * blue;
    setAll(r, g, b);
    strip.show();
    delay(wait);
  }
  for(int k = 255; k >= 0; k--) {
    int r = (k/256.0) * red;
    int g = (k/256.0) * green;
    int b = (k/256.0) * blue;
    setAll(r, g, b);
    strip.show();
    delay(wait);
  }
}

void colorBounce(uint32_t color, int wait) {
  for(int i = 0; i < strip.numPixels(); i++) {
    strip.clear();
    strip.setPixelColor(i, color);
    strip.show();
    delay(wait);
  }
  for(int i = strip.numPixels()-1; i >= 0; i--) {
    strip.clear();
    strip.setPixelColor(i, color);
    strip.show();
    delay(wait);
  }
}

void sparkle(int red, int green, int blue, int wait) {
  for(int i = 0; i < 20; i++) {
    int pixel = random(strip.numPixels());
    strip.setPixelColor(pixel, red, green, blue);
    strip.show();
    delay(wait);
    strip.setPixelColor(pixel, 0, 0, 0);
  }
}

void fireEffect(int wait) {
  for(int i = 0; i < 50; i++) {
    for(int j = 0; j < strip.numPixels(); j++) {
      int flicker = random(0, 150);
      strip.setPixelColor(j, 255, flicker, 0);
    }
    strip.show();
    delay(wait);
  }
}

void meteorRain(byte red, byte green, byte blue, byte meteorSize, byte meteorTrailDecay, boolean meteorRandomDecay, int wait) {
  setAll(0, 0, 0);
  
  for(int i = 0; i < strip.numPixels() + strip.numPixels(); i++) {

    for(int j = 0; j < strip.numPixels(); j++) {
      if(!meteorRandomDecay || random(10) > 5) {
        fadeToBlack(j, meteorTrailDecay);
      }
    }
    
    for(int j = 0; j < meteorSize; j++) {
      if(i-j < strip.numPixels() && i-j >= 0) {
        strip.setPixelColor(i-j, red, green, blue);
      }
    }
    strip.show();
    delay(wait);
  }
}

void twinkle(int red, int green, int blue, int count, int wait, boolean onlyOne) {
  setAll(0, 0, 0);
  
  for(int i = 0; i < count; i++) {
    strip.setPixelColor(random(strip.numPixels()), red, green, blue);
    strip.show();
    delay(wait);
    if(onlyOne) {
      setAll(0, 0, 0);
    }
  }
  delay(wait);
}

void runningLights(byte red, byte green, byte blue, int wait) {
  int position = 0;
  
  for(int j = 0; j < strip.numPixels() * 2; j++) {
    position++;
    for(int i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, ((sin(i + position) * 127 + 128)/255) * red,
                             ((sin(i + position) * 127 + 128)/255) * green,
                             ((sin(i + position) * 127 + 128)/255) * blue);
    }
    strip.show();
    delay(wait);
  }
}

void colorChase(uint32_t color, int wait) {
  for(int i = 0; i < strip.numPixels() + 4; i++) {
    strip.setPixelColor(i, color);
    if(i >= 4) strip.setPixelColor(i-4, 0);
    strip.show();
    delay(wait);
  }
}

void breathingEffect(int red, int green, int blue) {
  for(int i = 0; i < 2; i++) {
    for(int j = 0; j < 256; j++) {
      setAll((j/256.0)*red, (j/256.0)*green, (j/256.0)*blue);
      strip.show();
      delay(5);
    }
    for(int j = 255; j >= 0; j--) {
      setAll((j/256.0)*red, (j/256.0)*green, (j/256.0)*blue);
      strip.show();
      delay(5);
    }
  }
}

void policeStrobe(int wait) {
  for(int i = 0; i < 5; i++) {
    // Merah
    for(int j = 0; j < strip.numPixels()/2; j++) {
      strip.setPixelColor(j, 255, 0, 0);
    }
    strip.show();
    delay(wait);
    setAll(0, 0, 0);
    strip.show();
    delay(wait);
  }
  
  for(int i = 0; i < 5; i++) {
    // Biru
    for(int j = strip.numPixels()/2; j < strip.numPixels(); j++) {
      strip.setPixelColor(j, 0, 0, 255);
    }
    strip.show();
    delay(wait);
    setAll(0, 0, 0);
    strip.show();
    delay(wait);
  }
}

void rainbowPulse(int wait) {
  for(int j = 0; j < 256; j++) {
    for(int i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

void larsonScanner(byte red, byte green, byte blue, int wait) {
  for(int i = 0; i < strip.numPixels() - 1; i++) {
    strip.clear();
    strip.setPixelColor(i, red/10, green/10, blue/10);
    strip.setPixelColor(i+1, red, green, blue);
    strip.setPixelColor(i+2, red/10, green/10, blue/10);
    strip.show();
    delay(wait);
  }
  
  for(int i = strip.numPixels() - 2; i > 0; i--) {
    strip.clear();
    strip.setPixelColor(i, red/10, green/10, blue/10);
    strip.setPixelColor(i+1, red, green, blue);
    strip.setPixelColor(i+2, red/10, green/10, blue/10);
    strip.show();
    delay(wait);
  }
}

void colorWaves(int wait) {
  for(int j = 0; j < 256 * 2; j++) {
    for(int i = 0; i < strip.numPixels(); i++) {
      byte colorIndex = (i * 256 / strip.numPixels()) + j;
      strip.setPixelColor(i, Wheel(colorIndex));
    }
    strip.show();
    delay(wait);
  }
}

void randomBurst() {
  for(int i = 0; i < 10; i++) {
    setAll(random(255), random(255), random(255));
    strip.show();
    delay(100);
    setAll(0, 0, 0);
    strip.show();
    delay(100);
  }
}

void dualColorChase(uint32_t color1, uint32_t color2, int wait) {
  for(int i = 0; i < strip.numPixels(); i++) {
    strip.clear();
    strip.setPixelColor(i, color1);
    strip.setPixelColor(strip.numPixels() - i - 1, color2);
    strip.show();
    delay(wait);
  }
}

void stroboscope(byte red, byte green, byte blue, int strobeCount, int flashDelay, int endPause) {
  for(int j = 0; j < strobeCount; j++) {
    setAll(red, green, blue);
    strip.show();
    delay(flashDelay);
    setAll(0, 0, 0);
    strip.show();
    delay(flashDelay);
  }
  delay(endPause);
}

void setAll(int red, int green, int blue) {
  for(int i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, strip.Color(red, green, blue));
  }
}

void fadeToBlack(int ledNo, byte fadeValue) {
  uint32_t oldColor = strip.getPixelColor(ledNo);
  uint8_t r = (oldColor >> 16) & 0xFF;
  uint8_t g = (oldColor >> 8) & 0xFF;
  uint8_t b = oldColor & 0xFF;

  r = (r <= 10) ? 0 : (int)r - (r * fadeValue / 256);
  g = (g <= 10) ? 0 : (int)g - (g * fadeValue / 256);
  b = (b <= 10) ? 0 : (int)b - (b * fadeValue / 256);

  strip.setPixelColor(ledNo, r, g, b);
}

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
