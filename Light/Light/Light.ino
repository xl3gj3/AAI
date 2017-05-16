/* Photocell simple testing sketch. 
 
Connect one end of the photocell to 5V, the other end to Analog 0.
Then connect one end of a 10K resistor from Analog 0 to ground
 
For more information see http://learn.adafruit.com/photocells */
 
int photocellPin1 = 0;     // the cell and 10K pulldown are connected to a0
int photocellPin2 = 0;     // the cell and 10K pulldown are connected to a0
int photocellPin3 = 0;     // the cell and 10K pulldown are connected to a0
int photocellPin4 = 0;     // the cell and 10K pulldown are connected to a0
int photocellReading1;     // the analog reading from the analog resistor divider
int photocellReading2;     // the analog reading from the analog resistor divider
int photocellReading3;     // the analog reading from the analog resistor divider
int photocellReading4;     // the analog reading from the analog resistor divider
int photocell_average;     // sum up the reading and average it 
int LEDpin1 = 3;          // connect Red LED to pin 3 (PWM pin) (white LED)
int LEDpin2 = 10;          // connect Red LED to pin 10 (PWM pin) (white LED)
 
void setup(void) {
  // We'll send debugging information via the Serial monitor
  Serial.begin(9600);   
}
 
void loop(void) {
  photocellReading1 = analogRead(photocellPin1);  
  photocellReading2 = analogRead(photocellPin2);
  photocellReading3 = analogRead(photocellPin3);
  photocellReading4 = analogRead(photocellPin4);
  photocell_average = (photocellReading1 + photocellReading2 + photocellReading3 + photocellReading4)/4; 
  Serial.print("Analog reading = ");
  Serial.print(photocell_average);     // the raw analog reading
 
  // We'll have a few threshholds, qualitatively determined
  if (photocell_average < 300) {
    Serial.println(" - Dark");
    analogWrite(LEDpin1,255);
    analogWrite(LEDpin2,255);
     
  } else if (photocell_average < 400) {
    Serial.println(" - Dim");
    analogWrite(LEDpin1,255);
    analogWrite(LEDpin2,0);
  } else if (photocell_average < 500) {
    analogWrite(LEDpin1,0);
    analogWrite(LEDpin2,0);
    Serial.println(" - Light");
  } else if (photocell_average < 800) {
    analogWrite(LEDpin1,0);
    analogWrite(LEDpin2,0);
    Serial.println(" - Bright");
  } else {
    Serial.println(" - Very bright");
    analogWrite(LEDpin1,0);
    analogWrite(LEDpin2,0);
  }
  delay(100);
}
