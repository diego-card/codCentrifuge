int vs =9; // vibration sensor

void setup(){
  pinMode(vs, INPUT_PULLUP); 
  Serial.begin(9600); 

}
void loop(){
  long measurement =vibration();
  delay(0);
  Serial.println(measurement);
}

long vibration(){
  long measurement=pulseIn (vs, HIGH);  //wait for the pin to get HIGH and returns measurement
  return measurement;
}
