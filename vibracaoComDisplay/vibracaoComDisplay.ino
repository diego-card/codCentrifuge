// Include Wire Library for I2C
#include <Wire.h>

// Include Adafruit Graphics & OLED libraries
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Reset pin not used but needed for library
#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

// SDA = A4, sdl = A5
int vs =8; // vibration sensor
long measurement = 0;

void setup(){
  pinMode(vs, INPUT); 
  Serial.begin(9600);
  // Start Wire library for I2C
  Wire.begin();
  
  // initialize OLED with I2C addr 0x3C
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);

}

long vibration(){
   
   return pulseIn (vs, HIGH);  //wait for the pin to get HIGH and returns measurement
  
}

void displayVibracao() {
  measurement =vibration();
  delay(500);

  // Clear the display
  display.clearDisplay();
  //Set the color - always use white despite actual display color
  display.setTextColor(WHITE);
  //Set the font size
  display.setTextSize(1);
  //Set the cursor coordinates
  display.setCursor(0,0);
  display.print("Vibracao Atual:");
  display.setCursor(0, 10);
  display.print(measurement);

}

void loop(){
  measurement =vibration();
  delay(50);
  Serial.println(measurement);
  displayVibracao();
  display.display();
}
