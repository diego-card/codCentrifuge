int vs =9; // vibration sensor
int buzz = 11;

void setup(){
  pinMode(buzz, OUTPUT);
  pinMode(vs, INPUT);
  Serial.begin(9600); 

}
void loop(){
  long measurement =vibration();
  delay(50);
  Serial.println(measurement);
  if(measurement > 2000){
    tone(buzz, 450);
    delay(500);
    noTone(buzz);
    delay(500);
  }
    
}

long vibration(){
  long measurement=pulseIn (vs, HIGH);  //wait for the pin to get HIGH and returns measurement
  return measurement;
}