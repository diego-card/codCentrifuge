/*
  Displays on 128 x 64 OLED display
  Uses Adafruit SSD1306 OLED Library
  Uses Adafruit GFX Graphics Library
  
  DroneBot Workshop 2019
  https://dronebotworkshop.com

  SDA = A4 
  SCL = A5
*/

// Include Wire Library for I2C
#include <Wire.h>

// Include Adafruit Graphics & OLED libraries
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Reset pin not used but needed for library
#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

// Other Variables
int downButton = 2;
int upButton = 3;
int menu = 1;


void setup() {
  // Start Wire library for I2C
  Wire.begin();

  // initialize OLED with I2C addr 0x3C
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();

  pinMode(downButton, INPUT_PULLUP);
  updateMenu();
}

void loop() {
  
  if(!digitalRead(downButton)){
    menu++;
    updateMenu();
    delay(100);
    while(!digitalRead(downButton));
  }
  if (!digitalRead(upButton)){
    menu--;
    updateMenu();
    delay(100);
    while(!digitalRead(upButton));
  }
  
}

void updateMenu(){
  switch(menu){
    case 0:
      menu = 1;
      break;
     case 1:
      header();
      display.setCursor(0,0);
      display.print("Menu Inicial");
      display.setCursor(0,10);
      display.print(">MenuItem1");
      display.setCursor(0,20);
      display.print(" MenuItem2");
      refresh();
      break;
     case 2:
      header();
      display.setCursor(0,0);
      display.print("Menu Inicial");
      display.setCursor(0,10);
      display.print(" MenuItem1");
      display.setCursor(0,20);
      display.print(">MenuItem2");
      refresh();
      break;
     case 3:
      header();
      display.setCursor(0,0);
      display.print("Menu Inicial");
      display.setCursor(0,10);
      display.print(">MenuItem3");
      display.setCursor(0,20);
      display.print(" MenuItem4");
      refresh();
      break;
     case 4:
      header();
      display.setCursor(0,0);
      display.print("Menu Inicial");
      display.setCursor(0,10);
      display.print(" MenuItem3");
      display.setCursor(0,20);
      display.print(">MenuItem4");
      refresh();
      break;
     case 5:
      menu = 1;
      break;
  }
}

void header(){
  //Set the font size
  display.setTextSize(1);
  //Set the color - always use white despite actual display color
  display.setTextColor(WHITE);
}
void refresh(){
  // Start display
  display.display();
  delay(00);
  display.clearDisplay();
}
