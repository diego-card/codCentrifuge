// Pra testar o motor ligando direto na placa com arduino como energia: Positivo(+) = 5v, in1 = 5v, in2 = GND.
#include <MX1508.h>

#define PINA 9
#define PINB 10
#define NUMPWM 2

int vs =8; // vibration sensor
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
  pinMode(vs, INPUT); 
  Serial.begin(115200);
}
/*
 * Ramp up to pwm = 100, by increasing pwm by 1 every 50 millisecond. 
 * then ramp down to pwm = -100, by decreasing pwm every 50 millisecond.
 * positive value pwm results in forward direction.
 * negative value pwm results in opposite direction. 
 */
void loop() {
  // put your main code here, to run repeatedly:
  static unsigned long lastMilli = 0;
  static bool cwDirection = true; // assume initial direction(positive pwm) is clockwise
  static int pwm = 1;
  
  /*if(millis()-lastMilli > 50){ // every 50 millisecond
      if (cwDirection && pwm++ > 100 ) {  
        cwDirection = false;
      } else if (!cwDirection && pwm-- < -100) {
        cwDirection =  true;
      } 
    motorA.motorGo(pwm);
    lastMilli = millis();
    Serial.println(motorA.getPWM()); // we can just print pwm but just showing that member function getPWM() works.
  }*/

 //comment everything else and use this
 //motorA.motorGo(100);

  long measurement =vibration();
  delay(50);
  Serial.println(measurement);

  if(on == true){
    motorA.motorGo(100);
    if(measurement > 2000){
      motorA.stopMotor();
      on = false;
    }
  } else if(measurement > 2000){
    on = true;
  }
  
}
long vibration(){
  long measurement=pulseIn (vs, HIGH);  //wait for the pin to get HIGH and returns measurement
  return measurement;
}