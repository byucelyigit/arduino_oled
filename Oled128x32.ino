/*
-- Aşağıdaki kod Mega'ya yüklendiğinde düzgün bir şekilde grafik ve yazılar
-- gösterildi. Ek olarak step motor da çalıştı.


*/

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <X113647Stepper.h>

static const int STEPS_PER_REVOLUTION = 32 * 64;

static const int PIN_IN1_BLUE         = 8;
static const int PIN_IN2_PINK         = 9;
static const int PIN_IN3_YELLOW       = 10;
static const int PIN_IN4_ORANGE       = 11;

// initialize the stepper library
tardate::X113647Stepper myStepper(
  STEPS_PER_REVOLUTION,
  PIN_IN1_BLUE, PIN_IN2_PINK, PIN_IN3_YELLOW, PIN_IN4_ORANGE
);


#define OLED_RESET 4
const int button1Pin = 2;

Adafruit_SSD1306 display(OLED_RESET);

#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2


#define LOGO16_GLCD_HEIGHT 32
#define LOGO16_GLCD_WIDTH  16 
static const unsigned char PROGMEM logo16_glcd_bmp[] =
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
  B00000000, B00110000 };

#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

void setup()   {                
  Serial.begin(9600);

  pinMode(button1Pin, INPUT_PULLUP);

  // set the speed in rpm:
  myStepper.setSpeed(16);


  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x32)
  // init done
  
  // Show image buffer on the display hardware.
  // Since the buffer is intialized with an Adafruit splashscreen
  // internally, this will display the splashscreen.
  display.display();
  delay(2000);

  // Clear the buffer.
  display.clearDisplay();

  
  
  
  // text display tests
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(15,0);
  display.println("21:45:18");
  display.println("");
  display.println("06:30");
  display.setTextSize(1);
  display.println("Ready");
  /*
  display.setCursor(0,1);
  display.println("A: 06:30");
  display.setCursor(0,2);
  */
  
  display.display();
  
  
}


void loop() {
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(15,0);
  int buttonState = digitalRead(button1Pin);

  Serial.println(buttonState);
  // Show the state of pushbutton on serial monitor
  // check if the pushbutton is pressed.
  // if it is, the buttonState is HIGH:
    display.clearDisplay();
  if (buttonState == 1) {
    // turn LED on:
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(15,0);
    display.println("Pin 2 Pressed");

    
  } else {
    // turn LED off:
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(15,0);
    display.println("                 ");
    myStepper.step(-32);

  }  
  display.display();

  // step one revolution in one direction:
  //myStepper.step(1);
  //delay(200);

  // step one revolution in the other direction:
  //myStepper.step(-STEPS_PER_REVOLUTION/2);
  //delay(1000);


}






