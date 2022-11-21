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
#include <Fonts/Picopixel.h>

// Reset pin not used but needed for library
#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

// OneButton Library
#include <OneButton.h>

#define BUTTON_PIN 2

/**
 * Initialize a new OneButton instance for a button
 * connected to digital pin 4 and GND, which is active low
 * and uses the internal pull-up resistor.
 */

OneButton btn = OneButton(
  BUTTON_PIN,  // Input pin for the button
  true,        // Button is active LOW
  true         // Enable internal pull-up resistor
);

// Other Variables
int menu = 1;
bool voltar = false;


void setup() {
  Serial.begin(9600);
  // Start Wire library for I2C
  Wire.begin();

  // Onebutton functions
  btn.attachDoubleClick([](){
    Serial.println("Double Pressed!");
  });

  btn.attachLongPressStart([](){
    Serial.println("Long Pressed");
  });

  // initialize OLED with I2C addr 0x3C
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();

  //pinMode(downButton, INPUT_PULLUP);
  updateMenu();
}

void loop() {
  //For Onebutton to work
  btn.tick();
  
  btn.attachClick([](){
    Serial.println("One click");
    menu++;
    updateMenu();
    delay(100);
    //while(!digitalRead(downButton));
  });

  btn.attachLongPressStart([](){
    Serial.println("Long press");
    executeAction();
    //updateMenu();
    delay(100);
  });

  btn.attachDoubleClick([](){  
    if(menu <= 5){
      menu = 1;
      updateMenu();
      delay(100);
     } else if(menu >= 20){
      menu = 2;
      updateMenu();
      delay(100);
     }
  });  
}

void updateMenu(){
  switch(menu){
    case 0:
      menu = 1;
      break;
     case 1:
      header();
      display.setCursor(0,0);
      display.print("Clique para Continuar");
      display.setFont(&Picopixel);
      display.setCursor(0,13);
      display.print("1 CLICK ---------> N A V E G A R");
      display.setCursor(0,21.5);
      display.print("2 CLICKS --------> V O L T A R");
      display.setCursor(0,30);
      display.print("CLICK LONGO -----> S E L E C I O N A R");
      refresh();
      break;
     case 2:
      header();
      display.setCursor(0,0);
      display.print("Menu Inicial");
      display.setCursor(0,10);
      display.print(">Iniciar Centrifuga");
      display.setCursor(0,20);
      display.print(" MenuItem2");
      refresh();
      break;
     case 3:
      header();
      display.setCursor(0,0);
      display.print("Menu Inicial");
      display.setCursor(0,10);
      display.print(" Iniciar Centrifuga");
      display.setCursor(0,20);
      display.print(">MenuItem2");
      refresh();
      break;
     case 4:
      header();
      display.setCursor(0,0);
      display.print("Menu Inicial");
      display.setCursor(0,10);
      display.print(" MenuItem2");
      display.setCursor(0,20);
      display.print(">MenuItem3");
      refresh();
      break;
     case 5:
      menu = 1;
      break;
     case 20:
      header();
      display.setCursor(0,0);
      display.print("Ligar Centrifuga");
      display.setCursor(0,10);
      display.print("Aperte para ligar, ou");
      display.setCursor(0,20);
      display.print("denovo para desligar;");
      refresh();
      break;
     case 21:
      header();
      display.setCursor(0,10);
      display.print(" Item1 do Menu 1");
      display.setCursor(0,20);
      display.print(">Item2 do Menu 1");
      refresh();
      break;
     case 22:
      menu = 20;
      updateMenu();
      break;
  }
}

//Actions
void executeAction() {
  switch (menu) {
    case 2:
      menu = 20;
      updateMenu();
      break;
    case 3:
      action3();
      break;
    case 4:
      action4();
      break;
     case 20:
      //Coisa do motor
      /*
      btn.attachLongPressStart([](){
      Serial.println("Long Pressed");
      if (ligado == false){
        Serial.println("Desligado!");
        ligado = true;
      } else{
        Serial.println("Ligado!");
        ligado = false;
        }
      });
      */
  }
}

void action3() {
  display.setCursor(0,10);
  display.print(">Executing #2");
  refresh();
  delay(1500);
}
void action4() {
  display.setCursor(0,10);
  display.print(">Executing #3");
  refresh();
  delay(2000);
}


void header(){
  display.setFont(NULL);
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
