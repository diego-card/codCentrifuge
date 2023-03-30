// Include Wire Library for I2C
#include <Wire.h>

// Include Adafruit Graphics & OLED libraries
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Reset pin not used but needed for library
#define OLED_RESET 12
Adafruit_SSD1306 display(OLED_RESET);

#include "Countimer.h"               //https://github.com/inflop/Countimer
Countimer tdown;
#include <EEPROM.h>

// #define bt_mode A3
// #define bt_up A2
// #define bt_down A1
// #define bt_select A0

#define bt_select 4
#define bt_mode 3 
#define bt_up 2 

int time_s = 0;
int time_m = 0;
int time_h = 0;

int set = 0;
int flag1 = 0, flag2 = 0;

int relay = 5;

void setup() {
  EEPROM.write(1, 0);
  EEPROM.write(2, 0);
  EEPROM.write(3, 0);

  Wire.begin();
  // initialize OLED with I2C addr 0x3C
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);

  Serial.begin(9600);

  pinMode(bt_mode, INPUT_PULLUP);
  pinMode(bt_up, INPUT_PULLUP);
  // pinMode(bt_down, INPUT_PULLUP);
  pinMode(bt_select, INPUT_PULLUP);

  pinMode(relay, OUTPUT);

  display.setTextColor(WHITE);

  display.clearDisplay();
  display.setCursor(0, 0);
  display.print("Countdown  Timer");
  tdown.setInterval(print_time, 999);
  eeprom_read();
  delay(1000);
  // display.clearDisplay();
  display.display();
}

void print_time() {
  time_s = time_s - 1;
  if (time_s < 0) {
    time_s = 59;
    time_m = time_m - 1;
  }
  if (time_m < 0) {
    time_m = 59;
    time_h = time_h - 1;
  }
}

void tdownComplete() {
  Serial.print("ok");
}

//tdown.stop();

void loop() {
  tdown.run();

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
    delay(200);
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
    flag2 = 1;
    eeprom_read();
    digitalWrite(relay, HIGH);
    tdown.restart();
    tdown.start();
  }

  // display.fillRect(0, 10, 128, 8, BLACK);

  if (set == 0) {
    display.clearDisplay();
    display.setCursor(0, 10);
    display.print("      Timer     ");
  }
  if (set == 1) {
    display.clearDisplay();
    display.setCursor(0, 10);
    display.print("  Set Timer SS  ");
  }
  if (set == 2) {
    display.clearDisplay();
    display.setCursor(0, 10); 
    display.print("  Set Timer MM  "); 
  }
  if (set == 3) {
    display.clearDisplay();
    display.setCursor(0, 10);
    display.print("  Set Timer HH  ");
  }

  display.setCursor(4, 20);
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