
// these constants describe the pins. They won't change:
const int xpin = A0;                  // x-axis of the accelerometer
const int ypin = A1;                  // y-axis
const int zpin = A2;                  // z-axis
const int flexPin1 = A3;              // flex sensor 1
const int flexPin2 = A4;              // flex sensor 2
const int flexPin3 = A5;              // flex sensor 3

// Define the number of samples to keep track for smoothing acceleration and pitch readings
const int numAccReadings = 30;
const int numPitchReadings = 10;


//save analog values
int flexVal1;
int flexVal2;
int flexVal3;
int xVal;
int yVal;
int zVal;

double roll = 0.00, pitch = 0.00;     //Roll & Pitch are the angles which rotate by the axis X and y

// Variables for smoothing acceleration readings
int accReadings[numAccReadings];      // the acceleration readings from the analog input for axis X
int accIndex = 0;                     // the index of the current reading
int totalAcc = 0;                     // the running total
int averageAcc = 0;                   // the average acceleration

// Variables for smoothing pitch (rotation around side-to-side axis) readings
int pitchReadings[numPitchReadings];      // the pitch readings from the pitch calculation
int pitchIndex = 0;                  // the index of the current reading
int totalPitch = 0;                  // the running total
float averagePitch = 0;                // the average pitch


void setup() {
  // initialize the serial communications:
  Serial.begin(9600);

  // initialize all the readings for acceleration to 0:
  for (int thisReading = 0; thisReading < numAccReadings; thisReading++) {
    accReadings[thisReading] = 0;
  }

  // initialize all the readings for pitch to 0:
  for (int thisReading = 0; thisReading < numPitchReadings; thisReading++) {
    pitchReadings[thisReading] = 0;
  }
}

void loop() {
  // Read and save analog values for accelerometer
  xVal = analogRead(xpin);
  yVal = analogRead(ypin);
  zVal = analogRead(zpin);

  // Read and save analog values for flex sensors
  flexVal1 = analogRead(flexPin1);
  flexVal2 = analogRead(flexPin2);
  flexVal3 = analogRead(flexPin3);

  // ----------------------------------------------------------------------------------------------------- FLEX SENSORS

  // print flex sensor 1 value to serial for reading in Max/MSP
  Serial.print("flex1 ");
  Serial.println(flexVal1);
  // print flex sensor 2 value to serial
  Serial.print("flex2 ");
  Serial.println(flexVal2);

  // map flex sensor 3 value to either 0 or 2
  int flex3Buff = map(flexVal3, 930, 960, 0, 1) * 2;
  // print mapped flex sensor 2 value to serial
  Serial.print("flex3 ");
  Serial.println(flex3Buff);

  // ----------------------------------------------------------------------------------------------------- TILT CALCULATION
  
  // Calculate pitch tilting from accelerometer readings.
  // Code for this calculation is gathered from https://wiki.dfrobot.com/How_to_Use_a_Three-Axis_Accelerometer_for_Tilt_Sensing
  double x_Buff = float(xVal);
  double y_Buff = float(yVal);
  double z_Buff = float(zVal);
  pitch = atan2(y_Buff , z_Buff) * 57.3;
  // roll = atan2((- x_Buff) , sqrt(y_Buff * y_Buff + z_Buff * z_Buff)) * 57.3;       // roll is not used

  // ----------------------------------------------------------------------------------------------------- AVERAGE ACCELERATION
  // Smoothing out values for acceleration by calculating a running average.
  // This code is from an Arduino smoothing tutorial: http://www.arduino.cc/en/Tutorial/Smoothing

  totalAcc = totalAcc - accReadings[accIndex];      // subtract the last reading
  accReadings[accIndex] = analogRead(xpin);         // read from the sensor
  totalAcc = totalAcc + accReadings[accIndex];      // add the reading to the totalAcc
  accIndex = accIndex + 1;                          // advance to the next position in the array

  // if we're at the end of the array...
  if (accIndex >= numAccReadings) {
    accIndex = 0;         // ...wrap around to the beginning
  }

  // calculate the average acceleration:
  averageAcc = totalAcc / numAccReadings;

  // print the average values to serial:
  Serial.print("accel ");
  Serial.println(averageAcc);

  // ----------------------------------------------------------------------------------------------------- AVERAGE PITCH
  // Smoothing out values for pitch tilting by calculating a running average.
  // This code is from an Arduino smoothing tutorial: http://www.arduino.cc/en/Tutorial/Smoothing

  totalPitch = totalPitch - pitchReadings[pitchIndex];    // subtract the last reading
  pitchReadings[pitchIndex] = pitch;                      // read from the sensor
  totalPitch = totalPitch + pitchReadings[pitchIndex];    // add the reading to the total
  pitchIndex = pitchIndex + 1;                            // advance to the next position in the array

  // if we're at the end of the array...
  if (pitchIndex >= numPitchReadings) {
    pitchIndex = 0;         // ...wrap around to the beginning:
  }

  // calculate the average pitch:
  averagePitch = totalPitch / numPitchReadings;

  // print the average values to serial:
  Serial.print("pitch ");
  Serial.println(averagePitch);

  // ---------------------------------------------

  // delay before next reading:
  delay(1);
}
