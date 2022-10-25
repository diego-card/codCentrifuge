/*
  Displays on 128 x 64 OLED display
  Uses Adafruit SSD1306 OLED Library
  Uses Adafruit GFX Graphics Library
  
  DroneBot Workshop 2019
  https://dronebotworkshop.com

  SDA = A4 
  SDL = A5
*/

// Include Wire Library for I2C
#include <Wire.h>

// Include Adafruit Graphics & OLED libraries
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Reset pin not used but needed for library
#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);


void setup() {
  // Start Wire library for I2C
  Wire.begin();
  
  // initialize OLED with I2C addr 0x3C
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  
}

void displayLed(){
  // Delay to allow sensor to stabalize
  delay(2000);

  // Clear the display
  display.clearDisplay();
  //Set the color - always use white despite actual display color
  display.setTextColor(WHITE);
  //Set the font size
  display.setTextSize(1);
  //Set the cursor coordinates
  display.setCursor(0,0);
  display.print("Apenas un teste");
  display.setCursor(0,10); 
  display.print("Despacito"); // 21 caracters each line
  display.print("DESPACITO");
  display.setCursor(0,20);
  display.print("Poquito"); 
  display.print("POQUITO");
  display.print("Poquito");
}
void loop() {
  displayLed();
  display.display();
}
