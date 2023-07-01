// (Analog Pin + Resistor 10k(GND)) + 5v

#include <Thermistor.h> //INCLUSÃO DA BIBLIOTECA

Thermistor temp(2); //VARIÁVEL DO TIPO THERMISTOR, INDICANDO O PINO ANALÓGICO (A2) EM QUE O SENSOR ESTÁ CONECTADO

// Variables for Measured Voltage and Calculated Current
double Vout = 0;
double Current = 0;

// Constants for Scale Factor
// Use one that matches your version of ACS712

//const double scale_factor = 0.185; // 5A
//const double scale_factor = 0.1; // 20A
const double scale_factor = 0.066; // 30A

// Constants for A/D converter resolution
// Arduino has 10-bit ADC, so 1024 possible values
// Reference voltage is 5V if not using AREF external reference
// Zero point is half of Reference Voltage

const double vRef = 5.00;
const double resConvert = 1024;
double resADC = vRef/resConvert;
double zeroPoint = vRef/2;

void setup() {
  Serial.begin(9600);
}

void loop() {
  int temperature = temp.getTemp();

  // Vout is read 1000 Times for precision
  for(int i = 0; i < 1000; i++) {
    Vout = (Vout + (resADC * analogRead(A1)));   
    delay(1);
  }
  
  // Get Vout in mv
  Vout = Vout /1000;
  
  // Convert Vout into Current using Scale Factor
  Current = (Vout - zeroPoint)/ scale_factor;                

  //Serial.print("Vout = ");
  Serial.print(Vout,2);
  Serial.print(",");
  //Serial.print("\t Current = ");
  Serial.print(Current,2);
  Serial.print(",");
  Serial.println(temperature);
  delay(100); 
}
