// Sensor: Waterproof Thermistor NTC 10K
// (Analog Pin + Resistor 10k(GND)) + 5v
#include <Thermistor.h> //INCLUSÃO DA BIBLIOTECA
 
Thermistor temp(2); //VARIÁVEL DO TIPO THERMISTOR, INDICANDO O PINO ANALÓGICO (A2) EM QUE O SENSOR ESTÁ CONECTADO

void setup() {
  Serial.begin(9600); //INICIALIZA A SERIAL
  delay(1000); //INTERVALO DE 1 SEGUNDO
}
void loop() {
  int temperature = temp.getTemp(); //VARIÁVEL DO TIPO INTEIRO QUE RECEBE O VALOR DE TEMPERATURA CALCULADO PELA BIBLIOTECA
  Serial.print("Temperatura: "); //IMPRIME O TEXTO NO MONITOR SERIAL
  Serial.print(temperature); //IMPRIME NO MONITOR SERIAL A TEMPERATURA MEDIDA
  Serial.println("*C"); //IMPRIME O TEXTO NO MONITOR SERIAL
  delay(1000); //INTERVALO DE 1 SEGUNDO
}





// https://blogmasterwalkershop.com.br/arduino/como-usar-com-arduino-termistor-ntc-10k-sensor-de-temperatura
