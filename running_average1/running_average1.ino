// running_average1
// A simple example of using an array in RAM to make a circular buffer
// and calculate a running average to smooth out noise in the signal
// A new sample is taken every 20 milliseconds, but a new average 
// value is only calculated every second, and output to the serial 
// monitor. 

// You can input a voltage to Analog Pin 0 to change the measured
// value. 



byte analogChannel = 0; // define which pin to read
long newtick = 0; // used to keep track of millis() value
long oldtick = 0; // used to keep track of millis() value
long serialtick = 0;
byte LED = 13; // Define which pin has the LED attached

//*****************************************
// Code to create a circular buffer and running average
const int arrayLength = 32; // This must be a const so it can be used in the next line
int tempInArray[arrayLength]; // define an array to hold last 32 values
word total = 0; // define a variable to hold total of tempInArray values (word = 16-bit unsigned)
word totalAvg = 0; // an integer variable to hold the average ADC value
byte index = 0; // counter to keep track of times through the sampling loop
//******************************************


void setup() {
 Serial.begin(115200);
 delay(500);
 Serial.println("Starting"); 
 pinMode(LED,OUTPUT); // Set the LED pin as an output
 
}

void loop() {
  
  newtick = millis(); // read the millisecond timer value once per cycle
  
  // If more than 10 milliseconds have elapsed since oldtick was
  // last updated (the difference between newtick and oldtick >= 10)
  // then take a new analog reading
  if (newtick - oldtick >= 20) {
   oldtick = newtick; // update oldtick value
   tempInArray[index] = analogRead(analogChannel); // Take a reading from analog channel 
   index = index++; // increment index
   if (index == arrayLength) {
     index = 0; // reset index 
    }
    digitalWrite(LED,!(digitalRead(LED)));
  }
  
  // If more than 1000 milliseconds have elapsed since serialtick 
  // was last updated (the difference between newtick and serialtick >=1000)
  // then output a new reading to the Serial monitor
  if (newtick - serialtick >= 1000) {
    serialtick = newtick; // Update serialtick now
    // Tally up the total value of the data points in the tempInArray
    total = 0; // First re-zero total value
    for (byte i = 0; i < arrayLength; i++){
     total = total + tempInArray[i]; 
    }
    totalAvg = total >> 5; // divide by 32 using bitwise right-shift (2^5 = 32). 
    // Alternatively, you can do the above operation like so:
    // totalAvg = total / 32; //integer division, drops all remainders
    Serial.print(totalAvg); // The average ADC value (0 to 1023)
    Serial.print("\t");
    float voltage = totalAvg * (5.0 / 1023.0);
    Serial.println(voltage);
    
  }

}
