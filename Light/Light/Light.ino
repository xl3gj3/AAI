/* Photocell simple testing sketch. 
 
Connect one end of the photocell to 5V, the other end to Analog 0.
Then connect one end of a 10K resistor from Analog 0 to ground
 
For more information see http://learn.adafruit.com/photocells */
 
int photocellPin1 = 0;     // the cell and 10K pulldown are connected to a0
int photocellPin2 = 1;     // the cell and 10K pulldown are connected to a0
int photocellPin3 = 2;     // the cell and 10K pulldown are connected to a0
int photocellPin4 = 3;     // the cell and 10K pulldown are connected to a0
int photocellReading1;     // the analog reading from the analog resistor divider
int photocellReading2;     // the analog reading from the analog resistor divider
int photocellReading3;     // the analog reading from the analog resistor divider
int photocellReading4;     // the analog reading from the analog resistor divider
int photocell_average;     // sum up the reading and average it 
int LEDpin1 = 2;          // connect Red LED to pin 2 (PWM pin) (white LED)
int LEDpin2 = 3;          // connect Red LED to pin 3 (PWM pin) (white LED)
int LEDpin3 = 4;          // connect Red LED to pin 2 (PWM pin) (white LED)
int LEDpin4 = 5;          // connect Red LED to pin 3 (PWM pin) (white LED)
// parameter for light
int dim_min = 600;
int dim_max = 700;

void light (void) {
  photocellReading1 = analogRead(photocellPin1);  
  photocellReading2 = analogRead(photocellPin2);
  photocellReading3 = analogRead(photocellPin3);
  photocellReading4 = analogRead(photocellPin4);
  photocell_average = (photocellReading1 + photocellReading2 + photocellReading3 + photocellReading4)/4; 
  //Below is debugging msgs.
  Serial.print("Analog1 reading = ");
  Serial.print(photocellReading1);     // the raw analog reading
  Serial.print("\n");
  Serial.print("Analog2 reading = ");
  Serial.print(photocellReading2);     // the raw analog reading
  Serial.print("\n");
  Serial.print("Analog3 reading = ");
  Serial.print(photocellReading3);     // the raw analog reading
  Serial.print("\n");
  Serial.print("Analog4 reading = ");
  Serial.print(photocellReading4);     // the raw analog reading
  Serial.print("\n");
  Serial.print("Analog_avg reading = ");
  Serial.print(photocell_average);     // the raw analog reading
  Serial.print("\n");
  // Different readings from analog will result in different light intensity. The number will be determine more accurately later
  if (photocell_average < dim_min) {
    Serial.println(" - Dark");
    digitalWrite(LEDpin1,HIGH);
    digitalWrite(LEDpin2,HIGH);
     
  } else if (photocell_average < dim_max && photocell_average > dim_min) {
    Serial.println(" - Dim");
    digitalWrite(LEDpin1,HIGH);
    digitalWrite(LEDpin2,LOW);
  } else {
    Serial.println(" - Light");
    digitalWrite(LEDpin1,LOW);
    digitalWrite(LEDpin2,LOW);
  }
  //This is for the blue and red LED, which will be controll by the app. Using button as the input pretent using app, so we keep sending output
    // 2 variables will be passed into this function to turn on/off blue/red LEDs
  digitalWrite(LEDpin3,HIGH);
  delay(100);
}
void setup(void) {
  // We'll send debugging information via the Serial monitor
  Serial.begin(9600);
  pinMode(LEDpin1, OUTPUT);
  pinMode(LEDpin2, OUTPUT);  
  pinMode(LEDpin3, OUTPUT); 
}
 
void loop(void) {
  update_sensor_data();// water level, all sensors data are read in this functions
  //timing issue
  light();





  
}
