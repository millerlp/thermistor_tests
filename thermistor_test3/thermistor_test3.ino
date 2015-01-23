// Calculate temperature from a Vishay-Dale 01T1002F thermistor in a half-bridge
// with a nominal 10k ohm resistor. 
// http://playground.arduino.cc/ComponentLib/Thermistor2
// Schematic:
// [Ground] ---- [10k-Resistor] -------|------- [Thermistor] ---- [+5v]
//                                     |
//                                 Analog Pin 0

// Include a LED and ~560ohm resistor wired to pin D2
// Schematic:
// [D2] ---- LED ---- /\/\/\ ---- [Ground]
//                    560ohm

int A0value = 0;
double Resistance = 0;
double logR = 0;
double TemperatureK = 0;
double TemperatureC = 0;

//*****************************************
// Added code to create a circular buffer and running average
const int arrayLength = 10; // This must be a const so it can be used in the next line
int tempInArray[arrayLength]; // define an array to hold last 10 values
unsigned int total = 0; // define a variable to hold total of tempInArray values
float totalAvg = 0; // a floating point (decimal) variable to hold the average ADC value
byte index = 0; // counter to keep track of times through the main loop
//******************************************

//********
int LED = 2;
float threshhold = 27.0;
//********

void setup() {
 Serial.begin(9600);
 delay(1000);
 Serial.println("Starting"); 
 pinMode(LED, OUTPUT);
}

void loop() {
  //******************************************************************
  //******************************************************************
  // Added code to implement the running average
  
  if (index == arrayLength) {
     index = 0; // reset index 
  }
  A0value = analogRead(0); // Take a reading from analog channel 0
  tempInArray[index] = A0value; // write the analog reading to the array
  
  total = 0; // reset total value
  for (byte i = 0; i < arrayLength; i++) {
     total = total + tempInArray[i]; // add each value of tempInArray to total
     Serial.print(" ");
     Serial.println(tempInArray[i]);
  }
  // Calculate the average ADC value by dividing total by the number of readings
  // Note the cast to float so that the result of the division is a decimal number
  totalAvg = (float)total / arrayLength;
  //******************************************************************
  //******************************************************************
  
  // Calculate resistance. Resistance = ((1024/ADC value) - 1) * fixed resistor
  // Note that I have used the measured value of the 
  // fixed resistor instead of its nominal value (10k ohm)
  Resistance = ((1023.0/totalAvg)-1) * 10020.0; 
  logR = log(Resistance); // calculate natural log of Resistance for use below
  
  // Steinhart-Hart equation:
  // A = 0.0011249, B = 0.00023482, C = 0.000000084976 for Vishay-Dale thermistor 01T1002F
  // T in Kelvin = 1 / (0.0011249 + (0.00023482*logR) + (0.000000084976 * (logR^3)))
  TemperatureK = 1 /(0.0011249 + (0.00023482*logR) + (0.000000084976 * (logR * logR * logR)));
  
  TemperatureC = TemperatureK - 273.15; // Convert to Celsius from Kelvin
  
  if (TemperatureC > threshhold) {
      digitalWrite(LED, HIGH);
  } else {
     digitalWrite(LED, LOW); 
  }
  
  // Print out the results
  Serial.print(index);
  Serial.print(" ");
  Serial.print("ADC: ");
  Serial.print(A0value); // The most recent raw analog convertor value 0-1023
  Serial.print(" ");
  Serial.print("ADC average: ");
  Serial.print(totalAvg); // The running average ADC value
  Serial.print("  ");
  Serial.print("Resistance: "); // The calculated resistance of the thermistor
  Serial.print(Resistance);
  Serial.print("  ");
  Serial.print("TempC: ");
  Serial.println(TemperatureC); // Calculated temperature in Celsius
  delay(1000);

  index = index + 1; // increment the index for this run through the main loop 
}
