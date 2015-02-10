// Noisy analog signal


byte analogChannel = 0; // define which pin to read
//*****************************************
// Code to create a circular buffer and running average
const int arrayLength = 32; // This must be a const so it can be used in the next line
int tempInArray[arrayLength]; // define an array to hold last 32 values
word total = 0; // define a variable to hold total of tempInArray values (word = 16-bit unsigned)
word totalAvg = 0; // an integer variable to hold the average ADC value
byte index = 0; // counter to keep track of times through the sampling loop
//******************************************


void setup(){
   Serial.begin(115200);
   
}

void loop() {
  
  tempInArray[index] = analogRead(analogChannel);
  index = index++;
  if (index == arrayLength) {
    index = 0; // reset index 
    total = 0; // First re-zero total value
    for (byte i = 0; i < arrayLength; i++){
     total = total + tempInArray[i]; // tally up the total value of the tempInArray
    }
    totalAvg = total >> 5; // divide by 32 using bitwise right-shift (2^5 = 32)
    totalAvg = map(totalAvg,0,1023,0,80); // re-map the value onto the 0-80 range
    for (int i = 0; i < totalAvg; i++){
      Serial.print("o"); // print a visual representation of signal level
    }
    Serial.println(); // print carriage return
  }
//  delay(5);

}
