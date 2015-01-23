// Calculate temperature from a Vishay-Dale 01T1002F thermistor in a half-bridge
// with a nominal 10k ohm resistor. 
// http://playground.arduino.cc/ComponentLib/Thermistor2
// Schematic:
// [Ground] ---- [10k-Resistor] -------|------- [Thermistor] ---- [+5v]
//                                     |
//                                 Analog Pin 0

int A0value = 0;
double Resistance = 0;
double logR = 0;
double TemperatureK = 0;
double TemperatureC = 0;

void setup() {
 Serial.begin(9600);
 delay(1000);
 Serial.println("Starting"); 
}

void loop() {
  A0value = analogRead(0); // Take a reading from analog channel 0

  // Calculate resistance. Resistance = ((1024/ADC value) - 1) * fixed resistor
  // Note that I have used the measured value of the 
  // fixed resistor instead of its nominal value (10k ohm)
  Resistance = ((1023.0/A0value)-1) * 10020.0; 
  logR = log(Resistance); // calculate natural log of Resistance for use below
  
  // Steinhart-Hart equation:
  // A = 0.0011249, B = 0.00023482, C = 0.000000084976 for Vishay-Dale thermistor 01T1002F
  // T in Kelvin = 1 / (0.0011249 + (0.00023482*logR) + (0.000000084976 * (logR^3)))
  TemperatureK = 1 /(0.0011249 + (0.00023482*logR) + (0.000000084976 * (logR * logR * logR)));
  
  TemperatureC = TemperatureK - 273.15; // Convert to Celsius from Kelvin
  
  // Print out the results
  Serial.print("ADC: ");
  Serial.print(A0value); // The raw analog convertor value 0-1023
  Serial.print(" ");
  Serial.print("Resistance: "); // The calculated resistance of the thermistor
  Serial.print(Resistance);
  Serial.print("  ");
  Serial.print("TempK: "); 
  Serial.print(TemperatureK); // Calculated temperature in Kelvin
  Serial.print("  ");
  Serial.print("TempC: ");
  Serial.println(TemperatureC); // Calculated temperature in Celsius
  delay(1000);
}
