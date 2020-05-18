/*
  ADXL3xx

  Reads an Analog Devices ADXL3xx accelerometer and communicates the
  acceleration to the computer. The pins used are designed to be easily
  compatible with the breakout boards from SparkFun, available from:
  http://www.sparkfun.com/commerce/categories.php?c=80

  The circuit:
  - analog 0: accelerometer self test
  - analog 1: z-axis
  - analog 2: y-axis
  - analog 3: x-axis
  - analog 4: ground
  - analog 5: vcc

  created 2 Jul 2008
  by David A. Mellis
  modified 30 Aug 2011
  by Tom Igoe

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/ADXL3xx
*/

// these constants describe the pins. They won't change:
const int groundpin = 18;             // analog input pin 4 -- ground
const int powerpin = 19;              // analog input pin 5 -- voltage
const int xpin = A0;                  // x-axis of the accelerometer
const int ypin = A1;                  // y-axis
const int zpin = A2;                  // z-axis (only on 3-axis models)
const int flexPin1 = A5; //pin A0 to read analog input
const int flexPin2 = A3;
const int flexPin3 = A4;
const int accXPin = A0;


// Define the number of samples to keep track of. The higher the number, the
// more the readings will be smoothed, but the slower the output will respond to
// the input. Using a constant rather than a normal variable lets us use this
// value to determine the size of the readings array.
const int numAccReadings= 30;
const int numPitchReadings= 30;


int value1; //save analog value
int value2;
int value3;
int lastValue3 = 0;
int xval;
int yval;
int zval;
int accel;

int readings[numReadings];      // the readings from the analog input
int readIndex = 0;              // the index of the current reading
int total = 0;                  // the running total
int average = 0;                // the average
int startVal;                   // start value for calibrating

void setup() {
  // initialize the serial communications:
  Serial.begin(9600);

  for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    readings[thisReading] = 0;
  }

  startVal = analogRead(xpin);
}

void loop() {
  xval = analogRead(xpin);
  yval = analogRead(ypin);
  zval = analogRead(zpin);

  value1 = analogRead(flexPin1);         //Read and save analog value from potentiometer
  value2 = analogRead(flexPin2);
  value3 = analogRead(flexPin3);
//  Serial.print("flex1 ");
//
//  Serial.println(value1);               //Print value
//  Serial.print("flex2 ");
//  Serial.println(value2);
//  int flex3 = map(value3, 87, 79, 0, 1) * 2;
//  Serial.print("flex3 ");
//  Serial.println(flex3);
  lastValue3 = value3;

  //  accel = sqrt(sq(xval)+sq(yval)+sq(zval));



  total = total - readings[readIndex];
  // read from the sensor:
  readings[readIndex] = analogRead(xpin);
  // add the reading to the total:
  total = total + readings[readIndex];
  // advance to the next position in the array:
  readIndex = readIndex + 1;

  // if we're at the end of the array...
  if (readIndex >= numReadings) {
    // ...wrap around to the beginning:
    readIndex = 0;
  }

  // calculate the average:
  average = total / numReadings;





  // print the sensor values:
  Serial.print("accel ");
  Serial.println(average - startVal);
  //  // print a tab between values:
  //  Serial.print("\t");
  //  Serial.print(analogRead(ypin));
  //  // print a tab between values:
  //  Serial.print("\t");
  //  Serial.print(analogRead(zpin));
  //  Serial.println();
  // delay before next reading:
  delay(1);
}
