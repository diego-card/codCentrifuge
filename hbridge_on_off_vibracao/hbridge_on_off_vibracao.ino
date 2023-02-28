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

int vs =8; // vibration sensor
long measurement = 0;
boolean on = true;

// MX1508 schematics(in Chinese) can be found here at: http://sales.dzsc.com/486222.html
/*
 * MX1508(uint8_t pinIN1, uint8_t pinIN2, DecayMode decayMode, NumOfPwmPins numPWM);
 * DecayMode must be FAST_DECAY or SLOW_DECAY,
 * NumOfPwmPins, either use 1 or 2 pwm. 
 * I recommend using 2 pwm pins per motor so spinning motor forward and backward gives similar response.
 * if using 1 pwm pin, make sure its pinIN1, then set pinIN2 to any digital pin. I dont recommend this setting because 
 * we need to use FAST_DECAY in one direction and SLOW_DECAY for the other direction.  
 */
MX1508 motorA(PINA,PINB, FAST_DECAY, NUMPWM);

void setup() {
  // Start Wire library for I2C
  Wire.begin();

  // initialize OLED with I2C addr 0x3C
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);

  //Vibration
  pinMode(vs, INPUT); 
  Serial.begin(9600);
}

long vibration(){
  return pulseIn (vs, HIGH);  //wait for the pin to get HIGH and returns measurement
}

void displayLed(){
  measurement =vibration();
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
  display.print("Vibre para on/off");
  display.setCursor(0,10);
  display.print("Vibracao atual:");
  display.print(measurement);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  displayLed();
  display.display();
  static unsigned long lastMilli = 0;
  static bool cwDirection = true; // assume initial direction(positive pwm) is clockwise
  static int pwm = 1;

  measurement =vibration();
  delay(10);
  Serial.println(measurement);

  if(on == true){
    motorA.motorGo(100);
    if(measurement > 5000){
      motorA.stopMotor();
      on = false;
    }
  } else if(measurement > 5000){
    on = true;
  }

 //motorA.motorGo(100);
  
}
