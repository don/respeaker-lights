/**
 * ReSpeaker Arduino (atmega32u4) is a SPI slave receives commands as strings and controls the NeoPixel lights.
 * 
 * SPI slave based on SeeedStudio from https://github.com/respeaker/spi_bridge/blob/master/arduino_32u4_spi_slave.ino
 */

#include <SPI.h>

// Use the NeoPixel library rather than through ReSpeaker
// can't include <respeaker.h> due to ISR conflict
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIXEL_PIN      11
#define NUMPIXELS      12
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIXEL_PIN, NEO_GRB + NEO_KHZ800);

char spi_buf[64];
volatile byte spi_buf_index = 0;
volatile byte spi_event = 0;

uint32_t lastColor = pixels.Color(0,0,255);
uint32_t red = pixels.Color(255,0,0);
uint32_t orange = pixels.Color(255,127,0);
uint32_t green = pixels.Color(0,255,0);
uint32_t blue = pixels.Color(0,0,255);
uint32_t yellow = pixels.Color(255,255,0);
uint32_t purple = pixels.Color(128,0,128);
uint32_t pink = pixels.Color(215,72,148);
uint32_t turquoise = pixels.Color(64,224,208);
uint32_t magenta = pixels.Color(255,0,255);
uint32_t white = pixels.Color(255,255,255);
uint32_t black = pixels.Color(0,0,0);

void setup (void)
{
  Serial.begin(57600);
  Serial1.begin(57600);

  spi_slave_init();
  pixels.begin();
  pixels.setBrightness(10);
}

void spi_slave_init()
{
  pinMode(MOSI, INPUT);
  pinMode(MISO, OUTPUT);
  pinMode(SCK, INPUT);
  pinMode(SS, INPUT);

  // enable SPI slave mode
  SPCR |= _BV(SPE);

  SPI.attachInterrupt();
}

// SPI interrupt handler
ISR (SPI_STC_vect)
{
  char c = SPDR;  // read SPI Data Register
  if (spi_buf_index >= sizeof(spi_buf)) {
    spi_buf_index = 0;
  }

  if ('\n' == c) {
    spi_event = 1;
    spi_buf[spi_buf_index] = '\0';
  } else {
    spi_buf[spi_buf_index] = c;
    spi_buf_index++;
  }
}

void loop (void)
{
  // USB to UART
  while (Serial1.available() && Serial.availableForWrite()) {
    Serial.write((char)Serial1.read());
  }
  while (Serial.available() && Serial1.availableForWrite()) {
    Serial1.write((char)Serial.read());
  }

  if (spi_event) {
    spi_event = 0;
    spi_buf_index = 0;
    Serial.print("spi rx:");
    Serial.println(spi_buf);

    String command = String(spi_buf);
    Serial.print("Command is ");
    Serial.println(command);

    if (command == "red") {
      showColor(red);
    } else if (command == "orange") {
      showColor(orange);
    } else if (command == "green") {
      showColor(green);
    } else if (command == "blue") {
      showColor(blue);
    } else if (command == "yellow") {
      showColor(yellow);
    } else if (command == "purple") {
      showColor(purple);
    } else if (command == "white") {
      showColor(white);
    } else if (command == "pink") {
      showColor(pink);
    } else if (command == "turquoise") {
      showColor(turquoise);
    } else if (command == "magenta") {
      showColor(magenta);
    } else if (command == "brighter") {
      brighter();
    } else if (command == "brightness up") {
      brighter();
    } else if (command == "brightness down") {
      dimmer();
    } else if (command == "on") {
      lightsOn();
    } else if (command == "off") {
      lightsOff();
    } else {
      Serial.print("I don't understand ");
      Serial.println(command);
    }
  }
    
}

void lightsOff() {
  for (int i = 0; i < NUMPIXELS; i++) {
    pixels.setPixelColor(i, black);
  }
  pixels.show();

}

void lightsOn() {
  showColor(lastColor);
}

void brighter() {
  uint8_t brightness = pixels.getBrightness();
  if (brightness >= 205) {
    brightness = 255;
  } else {
    brightness += 50;    
  }
  Serial.print("Setting brightness to ");
  Serial.println(brightness);
  pixels.setBrightness(brightness);
  pixels.show();
}

void dimmer() {
  uint8_t brightness = pixels.getBrightness();
  if (brightness <= 50) {
    brightness = 5;
  } else {
    brightness -= 50;    
  }
  Serial.print("Setting brightness to ");
  Serial.println(brightness);
  pixels.setBrightness(brightness);
  pixels.show();
}

void showColor(uint32_t color) {
  lastColor = color;
  for (int i = 0; i < NUMPIXELS; i++) {
    pixels.setPixelColor(i, color);
  }
  pixels.show();
}

