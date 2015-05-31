//laser_jog
//dumb joining of various demos to make stepper-motor jog wheel for z axis
//of cheap lasercutter
//AKA 2015

#include <AccelStepper.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Encoder.h>

#define step_pin_1 A2
#define dir_pin_1 A3

#define MICRO_STEP 8  // microstepping

// Define some steppers and the pins the will use
AccelStepper stepper1(AccelStepper::DRIVER, step_pin_1, dir_pin_1); // Defaults to AccelStepper::FULL4WIRE (4 pins) on 2, 3, 4, 5
//AccelStepper stepper2(AccelStepper::DRIVER, step_pin_1, dir_pin_1);

// PINS
#define OLED_RESET 4
// connect SCL to A5
// connect SDA to A4
// encoder wiring bildr.org/2012/08/rotary-encoder-arduino/
// connect Encoder to digital 5
// connect Encoder to digital 3

Adafruit_SSD1306 display(OLED_RESET);
// Change these two numbers to the pins connected to your encoder.
//   Best Performance: both pins have interrupt capability
//   Good Performance: only the first pin has interrupt capability
//   Low Performance:  neither pin has interrupt capability

Encoder myEnc(3, 5);


#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2
#define LOGO16_GLCD_HEIGHT 16
#define LOGO16_GLCD_WIDTH  16
static unsigned const char PROGMEM logo16_glcd_bmp[] =
{ B00000000, B11000000,
  B00000001, B11000000,
  B00000001, B11000000,
  B00000011, B11100000,
  B11110011, B11100000,
  B11111110, B11111000,
  B01111110, B11111111,
  B00110011, B10011111,
  B00011111, B11111100,
  B00001101, B01110000,
  B00011011, B10100000,
  B00111111, B11100000,
  B00111111, B11110000,
  B01111100, B11110000,
  B01110000, B01110000,
  B00000000, B00110000
};

#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif




void setup()
{
  stepper1.setMaxSpeed(1000.0);
  stepper1.setAcceleration(1000.0);

  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3D (for the 128x64)
  // init done

  display.display(); // show splashscreen
  delay(2000);
  display.clearDisplay();   // clears the screen and buffer

}

long oldPosition  = -999;

void loop()
{
  // encoder update (from 'basic' lib example
  long newPosition = myEnc.read();
  if (newPosition != oldPosition) {
    oldPosition = newPosition;
    Serial.println(newPosition);
//    stepper1.moveTo(newPosition * 40); // this makes 360 in encoder ticks = one rev
// 200 stepper steps per rev  VS  96 encoder steps per rev
    stepper1.moveTo(newPosition * int((200*MICRO_STEP/96))); // this makes 360 in encoder ticks = one rev
  }

  //  stepper1.run();
  updateDisplay(newPosition);
  stepper1.runToPosition();

}