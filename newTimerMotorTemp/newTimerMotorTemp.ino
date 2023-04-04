#include <Thermistor.h>
Thermistor temp(0); //VARIÁVEL DO TIPO THERMISTOR, INDICANDO O PINO ANALÓGICO (A2) EM QUE O SENSOR ESTÁ CONECTADO
// Include Wire Library for I2C
#include <Wire.h>

// hbridge
#include <MX1508.h>

#define PINA 9
#define PINB 10
#define NUMPWM 2

MX1508 motorA(PINA,PINB, FAST_DECAY, NUMPWM);

// Include Adafruit Graphics & OLED libraries
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Fonts/FreeMonoBold9pt7b.h>

// Reset pin not used but needed for library
#define OLED_RESET 12
Adafruit_SSD1306 display(OLED_RESET);

#include "Countimer.h"
Countimer tdown;
#include <EEPROM.h>                   // Include the EEPROM library for reading and writing to non-volatile memory

#define bt_select 4                  // Define the pin number for the select button
#define bt_mode 3                    // Define the pin number for the mode button
#define bt_up 2                      // Define the pin number for the up button

int time_s = 0;
int time_m = 0;
int time_h = 0;

int set = 0;
int flag1 = 0, flag2 = 0;

int relay = 5;

bool running = false;

void setup() {
  EEPROM.write(1, 0);
  EEPROM.write(2, 0);
  EEPROM.write(3, 0);

  Wire.begin();
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  Serial.begin(9600);

  pinMode(bt_mode, INPUT_PULLUP);
  pinMode(bt_up, INPUT_PULLUP);
  pinMode(bt_select, INPUT_PULLUP);
  pinMode(relay, OUTPUT);

  // Necessary for the display
  display.setTextColor(WHITE);

  display.clearDisplay();
  // display.setCursor(0, 0);
  // display.print("Countdown  Timer");
  // Set the timer interval to 999 milliseconds and assign the print_time function as the callback function
  tdown.setInterval(print_time, 999);
  eeprom_read();
  delay(1000);
  display.display();
}

void print_time() {
  time_s = time_s-1;

  if(time_s<0){
    time_s=59; 
    time_m = time_m-1;
  }
  if(time_m<0){
    time_m=59;
    time_h = time_h-1;
  }
}

void tdownComplete() {
  motorA.stopMotor();
  Serial.print("ok");
}

//tdown.stop();
bool perigo = false;

void loop() {
  //motor
  static unsigned long lastMilli = 0;
  static bool cwDirection = true; // assume initial direction(positive pwm) is clockwise
  static int pwm = 1;

  tdown.run();

  int temperature = temp.getTemp();
  // Serial.print(temperature);
  //display.clearDisplay();
  if(temperature > 30){
    motorA.stopMotor();
    display.clearDisplay();
    display.setFont(NULL);
    display.setTextSize(1);
    display.setCursor(0, 0);
    display.print("DESLIGUE A CENTRIFUGA");
    display.setTextSize(2);
    display.setCursor(0, 10);
    display.print("QUENTE:");
    display.setCursor(90, 10);
    display.print(temperature);
    display.setCursor(115, 10);
    display.print("C");
    Serial.print("Danger!");
    perigo = true;
  }

  if(perigo == false){
    if (digitalRead(bt_mode) == 0) {
      if (flag1 == 0 && flag2 == 0) {
        flag1 = 1;
        set = set + 1;
        if (set > 3) { set = 0; }
        delay(100);
      }
    } else {
      flag1 = 0;
    }

    if (digitalRead(bt_up) == 0) {
      if (set == 0) {
        tdown.start();
        flag2 = 1;
      }
      if (set == 1) { time_s++; }
      if (set == 2) { time_m++; }
      if (set == 3) { time_h++; }
      if (time_s > 59) { time_s = 0; }
      if (time_m > 59) { time_m = 0; }
      if (time_h > 99) { time_h = 0; }
      if (set > 0) { eeprom_write(); }
      delay(25);
    }

    // if (digitalRead(bt_down) == 0) {
    //   if (set == 0) {
    //     tdown.stop();
    //     flag2 = 0;
    //   }
    //   if (set == 1) { time_s--; }
    //   if (set == 2) { time_m--; }
    //   if (set == 3) { time_h--; }
    //   if (time_s < 0) { time_s = 59; }
    //   if (time_m < 0) { time_m = 59; }
    //   if (time_h < 0) { time_h = 99; }
    //   if (set > 0) { eeprom_write(); }
    //   delay(200);
    // }

    if (digitalRead(bt_select) == 0) {
      // flag2 = 1;
      // eeprom_read();
      // digitalWrite(relay, HIGH);
      // tdown.restart();
      // tdown.start();
      
      if(running == false) {
        flag2 = 1;  
        // eeprom_read();
        // digitalWrite(relay, HIGH);
        tdown.start();

        motorA.motorGo(100);

        running = !running;
      } else {
        // flag2 = 1;  
        // eeprom_read();
        // digitalWrite(relay, LOW);
        tdown.pause();
        
        motorA.stopMotor();

        running = !running;
      }
    }

    // display.fillRect(0, 10, 128, 8, BLACK);

    if (set == 0) {
      display.clearDisplay();
      display.setFont(NULL); //Reseting font
      display.setCursor(0, 0);
      display.print("Temperatura:");
      display.setCursor(80, 0);
      display.print(temperature);
      display.print("C");
      display.setCursor(0, 10);
      display.print("Aperte para mudar");
    }
    if (set == 1) {
      display.clearDisplay();
      display.setFont(NULL);
      display.setCursor(0, 0);
      display.print("Temperatura:");
      display.setCursor(80, 0);
      display.print(temperature);
      display.print("C");
      display.setCursor(0, 10);
      display.print("Definir Segundos");
    }
    if (set == 2) {
      display.clearDisplay();
      display.setFont(NULL);
      display.setCursor(0, 0);
      display.print("Temperatura:");
      display.setCursor(80, 0);
      display.print(temperature);
      display.print("C");
      display.setCursor(0, 10); 
      display.print("Definir Minutos"); 
    }
    if (set == 3) {
      display.clearDisplay();
      display.setFont(NULL);
      display.setCursor(0, 0);
      display.print("Temperatura:");
      display.setCursor(80, 0);
      display.print(temperature);
      display.print("C");
      display.setCursor(0, 10);
      display.print("Definir Horas");
    }

    display.setCursor(20, 25);
    display.setFont(&FreeMonoBold9pt7b);
    if (time_h <= 9) { display.print("0"); }
    display.print(time_h);
    display.print(":");
    if (time_m <= 9) { display.print("0"); }
    display.print(time_m);
    display.print(":");
    if (time_s <= 9) { display.print("0"); }
    display.print(time_s);
    display.print("   ");

    if (time_s == 0 && time_m == 0 && time_h == 0 && flag2 == 1) {
      flag2 = 0;
      tdown.stop();
      digitalWrite(relay, LOW);
      tdownComplete();
    }

    if (flag2 == 1) {
      digitalWrite(relay, HIGH);
    } else {
      digitalWrite(relay, LOW);
    }
  }

  delay(1);
  display.display();
}

void eeprom_write() {
  EEPROM.write(1, time_s);
  EEPROM.write(2, time_m);
  EEPROM.write(3, time_h);
}

void eeprom_read() {
  time_s = EEPROM.read(1);
  time_m = EEPROM.read(2);
  time_h = EEPROM.read(3);
}
