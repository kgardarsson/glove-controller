/* How to use a flex sensor/resistro - Arduino Tutorial
   Fade an LED with a flex sensor
   More info: http://www.ardumotive.com/how-to-use-a-flex-sensor-en.html
   Dev: Michalis Vasilakis // Date: 9/7/2015 // www.ardumotive.com  */
   

//Constants:
const int ledPin = 3;   //pin 3 has PWM funtion
const int flexPin1 = A5; //pin A0 to read analog input
const int flexPin2 = A3;
const int flexPin3 = A4;
const int accXPin = A0;


//Variables:
int value1; //save analog value
int value2;
int value3;
int accXValue;

void setup(){
  pinMode(ledPin, OUTPUT);  //Set pin 3 as 'output'
  Serial.begin(9600);       //Begin serial communication
}

void loop(){
  value1 = analogRead(flexPin1);         //Read and save analog value from potentiometer
  value2 = analogRead(flexPin2);
  value3 = analogRead(flexPin3);
  accXValue = analogRead(accXPin);
  Serial.print("flex1 ");
  Serial.println(value1);               //Print value
  Serial.print("flex2 ");
  Serial.println(value2); 
  Serial.print("flex3 ");
  Serial.println(value3);
  Serial.print("accX ");
  Serial.println(accXValue);

  
 // value1 = map(value1, 700, 900, 0, 255);//Map value 0-1023 to 0-255 (PWM)
 // analogWrite(ledPin, value1);          //Send PWM value to led
 // delay(100);                          //Small delay
}
