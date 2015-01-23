
byte ADCpin = 0;
int ADCvalue = 0;

void setup(){
 Serial.begin(9600); 
}


void loop() {
  ADCvalue = analogRead(ADCpin);
  
  float voltage = ADCvalue * 5.0;
  voltage = voltage / 1024.0;
  
  Serial.print("voltage = ");
  Serial.print(voltage);
  Serial.print("  ");
  
  // The TMP36 outputs 10mV per degree Celsius, with a 500 mV
  // offset added to all values. 
  float TemperatureC = (voltage - 0.5) * 100;
  Serial.print("TemperatureC = ");
  Serial.println(TemperatureC);
  delay(1000); 
}
