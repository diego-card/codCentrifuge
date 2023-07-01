  //#define VIBRATION_SENSOR_DIGITAL_INPUT_PIN 10
//#define VIBRATION_SENSOR_DIGITAL_OUTPUT_PIN 8

#define VIBRATION_SAMPLE_ARRAY_SIZE 100

// if we 5 or more vibration events over a five second period then a vibration alarm is triggered
#define VIBRATION_EVENTS_ALARM_THRESHOLD_COUNT 5
#define VIBRATION_EVENTS_ALARM_THRESHOLD_PERIOD_MILLIS 5000

unsigned long previousMillis = 0; // variable to store the time of the last analog read
const long interval = 20; // interval at which to read the analog value

long vibrationEvents[VIBRATION_SAMPLE_ARRAY_SIZE];
int vibrationEventIndex;

void setup(){
  Serial.begin(9600);
  
    //pinMode(VIBRATION_SENSOR_DIGITAL_INPUT_PIN, INPUT);
  //pinMode(VIBRATION_SENSOR_DIGITAL_OUTPUT_PIN, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  
  vibrationEventIndex = 0;
  clearVibrationEvents();
}

void loop(){

  // Need to see what value the analog read's should consitute a trigger.
  if(analogRead(A3) == 20){
    long currentMillis = millis();
    addVibrationSample(currentMillis);
    if(isVibrationAlarmTiggered()){
      triggerAlarm();
      Serial.println(String(millis()) + "\t ALARM");
    }
    delay(100); // wait for current vibration shock to subside
  }

  // if(digitalRead(VIBRATION_SENSOR_DIGITAL_INPUT_PIN) == HIGH){
  //   long currentMillis = millis();
  //   addVibrationSample(currentMillis);
  //   if(isVibrationAlarmTiggered()){
  //     triggerAlarm();
  //     Serial.println(String(millis()) + "\t ALARM");
  //   }
  //   delay(100); // wait for current vibration shock to subside
  // }
}

void addVibrationSample(long vibrationMillis){
   vibrationEvents[vibrationEventIndex++] = vibrationMillis;
   if(vibrationEventIndex >= VIBRATION_SAMPLE_ARRAY_SIZE){
     vibrationEventIndex = 0; // wrap vibration sample index around when we get to end of sample array
   }
}

boolean triggerAlarm(){
  //digitalWrite(VIBRATION_SENSOR_DIGITAL_OUTPUT_PIN, HIGH);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);
  //digitalWrite(VIBRATION_SENSOR_DIGITAL_OUTPUT_PIN, LOW);
  digitalWrite(LED_BUILTIN, LOW);
  clearVibrationEvents();
}

void clearVibrationEvents(){
  for(int i = 0; i < VIBRATION_SAMPLE_ARRAY_SIZE ; ++i){
    vibrationEvents[i] = -1;
  }
}

boolean isVibrationAlarmTiggered(){
  long thresholdMillis = millis() - VIBRATION_EVENTS_ALARM_THRESHOLD_PERIOD_MILLIS;
  if(thresholdMillis < 0) thresholdMillis = 0;
  int numVibrationsSinceThreshold = 0;
  for(int i = 0; i < VIBRATION_SAMPLE_ARRAY_SIZE ; ++i){
    if(vibrationEvents[i] >= thresholdMillis){
      ++numVibrationsSinceThreshold;
    }
  }
  
  Serial.println(String(millis()) + "\t# events: " + String(numVibrationsSinceThreshold));
  boolean alarmTriggered = false;
  if(numVibrationsSinceThreshold >= VIBRATION_EVENTS_ALARM_THRESHOLD_COUNT){
    alarmTriggered = true;
  }
  
  return alarmTriggered;
}