// Noisy analog signal


byte analogChannel = 0; // define which pin to read
int analogVal = 0;



void setup(){
   Serial.begin(115200);
   
}

void loop() {
  
  analogVal = analogRead(analogChannel);

  analogVal = map(analogVal,0,1023,0,80); // re-map the value onto the 0-80 range
  for (int i = 0; i < analogVal; i++){
      Serial.print("o"); // print a visual representation of signal level
  }
  Serial.println(); // print carriage return
  delay(5);


}
