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
boolean switch_red_led = false;
boolean switch_blue_led = false;
boolean red_led = false;
boolean blue_led = false;
boolean white_led_1 = false;
boolean white_led_2 = false;

void reading_light_sensors (void){
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
}

void update_sensor_data (void){
  reading_light_sensors();
}

void light_status (boolean switch_red_led, boolean switch_blue_led) {


  // Different readings from analog will result in different light intensity. The number will be determine more accurately later
  if (photocell_average < dim_min) {
    Serial.println(" - Dark");
    white_led_1 = true;
    white_led_2 = true;
     
  } else if (photocell_average < dim_max && photocell_average > dim_min) {
    Serial.println(" - Dim");
    white_led_1 = true;
    white_led_2 = false;
  } else {
    Serial.println(" - Light");
    white_led_1 = false;
    white_led_2 = false;
  }
  //This is for the blue and red LED, which will be controll by the app. Using button as the input pretent using app, so we keep sending output
    // 2 variables will be passed into this function to turn on/off blue/red LEDs
  if (switch_red_led){
    red_led = true;
    }else{
      red_led = false;
      }
  if (switch_blue_led){
    blue_led = true; 
    }else{
      blue_led = false;
      }
  delay(100);
}
void turn_on_blue_red_led () {
  if (blue_led){
    digitalWrite(LEDpin3,HIGH);
    }else {
      digitalWrite(LEDpin3,LOW);
      } 
  if (red_led){
      digitalWrite(LEDpin3,HIGH);
    }else {
      digitalWrite(LEDpin3,LOW);
      } 
  
  }
void setup(void) {
  // We'll send debugging information via the Serial monitor
  Serial.begin(9600);
  pinMode(LEDpin1, OUTPUT);
  pinMode(LEDpin2, OUTPUT);  
  pinMode(LEDpin3, OUTPUT); 
  pinMode(LEDpin4, OUTPUT); 
}
 void turn_on_white_light (){
  if (white_led_1 && white_led_2){
    digitalWrite(LEDpin1,HIGH);
    digitalWrite(LEDpin2,HIGH);
    }
    else if (white_led_1){
      digitalWrite(LEDpin1,HIGH);
      digitalWrite(LEDpin2,LOW);
      }
    else{
      digitalWrite(LEDpin1,LOW);
      digitalWrite(LEDpin2,LOW);
      }
  }
void loop(void) {
  update_sensor_data();// water level, all sensors data are read in this functions
  //timing issue
  light_status(switch_red_led,switch_blue_led);
  turn_on_white_light();
  turn_on_blue_red_led();
  




  
}
