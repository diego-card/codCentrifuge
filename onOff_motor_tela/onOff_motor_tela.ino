// Pra testar o motor ligando direto na placa com arduino como energia: Positivo(+) = 5v, in1 = 5v, in2 = GND.

// Include hbridge library
#include <MX1508.h>
// Include Wire Library for I2C
#include <Wire.h>

// Include Adafruit Graphics & OLED libraries
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
// SDA = A4, SDL = A5

// Reset pin not used but needed for library
#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

#define PINA 9
#define PINB 10
#define NUMPWM 2

int button = 2;
int status = false;

MX1508 motorA(PINA,PINB, FAST_DECAY, NUMPWM);

void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(button, INPUT_PULLUP);
  
  // Start Wire library for I2C
  Wire.begin();

  // initialize OLED with I2C addr 0x3C
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  
  Serial.begin(9600);
}

void displayLed(){
  // Delay to allow sensor to stabalize
  delay(500);

  // Clear the display
  display.clearDisplay();
  //Set the color - always use white despite actual display color
  display.setTextColor(WHITE);
  //Set the font size
  display.setTextSize(1);
  //Set the cursor coordinates
  display.setCursor(0,0);
  display.print("Aperte p/ on/off");
  
}

void loop() {
  // put your main code here, to run repeatedly:
  displayLed();
  display.display();
  static unsigned long lastMilli = 0;
  static bool cwDirection = true; // assume initial direction(positive pwm) is clockwise
  static int pwm = 1;
  
    if (digitalRead(button) == true) {
      status = !status;
      digitalWrite(LED_BUILTIN, status); // turn the LED on (HIGH is the voltage level)
      if (status == true){
        motorA.stopMotor();
      } else {
        motorA.motorGo(100);
      }
    } while (digitalRead(button) == true);
    delay(100);

 //motorA.motorGo(100);
  
}
