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
// more the accReadings will be smoothed, but the slower the output will respond to
// the input. Using a constant rather than a normal variable lets us use this
// value to determine the size of the accReadings array.
const int numAccReadings = 30;


int value1; //save analog value
int value2;
int value3;
int lastValue3 = 0;
int xval;
int yval;
int zval;

double roll = 0.00, pitch = 0.00;       //Roll & Pitch are the angles which rotate by the axis X and y

int accel;

int accReadings[numAccReadings];      // the accReadings from the analog input
int readAcc = 0;              // the index of the current reading
int totalAcc = 0;                  // the running totalAcc
int averageAcc = 0;                // the averageAcc

int pitchReadings[numPitchReadings];    
int readPitch = 0;              
int totalPitch = 0;                 
int averagePitch = 0;     

int startVal;                   // start value for calibrating

void setup() {
  // initialize the serial communications:
  Serial.begin(9600);

  for (int thisReading = 0; thisReading < numAccReadings; thisReading++) {
    accReadings[thisReading] = 0;
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
  Serial.print("flex1 ");

  Serial.println(value1);               //Print value
  Serial.print("flex2 ");
  Serial.println(value2);
  int flex3 = map(value3, 87, 79, 0, 1) * 2;
  Serial.print("flex3 ");
  Serial.println(flex3);
  lastValue3 = value3;

  //  accel = sqrt(sq(xval)+sq(yval)+sq(zval));




  double x_Buff = float(xval);
  double y_Buff = float(yval);
  double z_Buff = float(zval);
  pitch = atan2(y_Buff , z_Buff) * 57.3;
  // roll = atan2((- x_Buff) , sqrt(y_Buff * y_Buff + z_Buff * z_Buff)) * 57.3;


// ------------------------------------------------------------ AVG ACCELERATION
  totalAcc = totalAcc - accReadings[readAcc];
  // read from the sensor:
  accReadings[readAcc] = analogRead(xpin);
  // add the reading to the totalAcc:
  totalAcc = totalAcc + accReadings[readAcc];
  // advance to the next position in the array:
  readAcc = readAcc + 1;

  // if we're at the end of the array...
  if (readAcc >= numAccReadings) {
    // ...wrap around to the beginning:
    readAcc = 0;
  }

  // calculate the averageAcc:
  averageAcc = totalAcc / numAccReadings;

// ------------------------------------------------------------ AVG PITCH
  totalPitch = totalPitch - pitchReadings[readPitch];
  // read from the sensor:
  pitchReadings[readPitch] = analogRead(pitch);
  // add the reading to the totalAcc:
  totalPitch = totalPitch + pitchReadings[readPitch];
  // advance to the next position in the array:
  readPitch = readPitch + 1;

  // if we're at the end of the array...
  if (readPitch >= numPitchReadings) {
    // ...wrap around to the beginning:
    readPitch = 0;
  }

  // calculate the averageAcc:
  averagePitch = totalPitch / numPitchReadings;

// ------------------------------------------------------------

  Serial.print("pitch ");
  Serial.println(averagePitch);


  // print the sensor values:
  Serial.print("accel ");
  Serial.println(averageAcc);
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
