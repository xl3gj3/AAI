/* Photocell simple testing sketch. 
 
Connect one end of the photocell to 5V, the other end to Analog 0.
Then connect one end of a 10K resistor from Analog 0 to ground
 
For more information see http://learn.adafruit.com/photocells */
 /*Sensors*/
 /***light***/
int photocellPin1 = 0;     // the cell and 10K pulldown are connected to a0
int photocellPin2 = 1;     // the cell and 10K pulldown are connected to a1
int photocellPin3 = 2;     // the cell and 10K pulldown are connected to a2
int photocellPin4 = 3;     // the cell and 10K pulldown are connected to a3
int photocellReading1;     // the analog reading from the analog resistor divider
int photocellReading2;     // the analog reading from the analog resistor divider
int photocellReading3;     // the analog reading from the analog resistor divider
int photocellReading4;     // the analog reading from the analog resistor divider
int photocell_average;     // sum up the reading and average it 

/***soil moisture***/
int moisture_1 = 0;
int moisture_2 = 0;
int sensor_1 = 4;// temp decision, will change input pin later
int sensor_2 = 5;
int moisture_avg = 0;

/***water level**/

int water_level_warning_1 = 7; // LED connected to digital pin 7
int water_level_warning_2 = 8; // LED connected to digital pin 8
int level_1 = 9; // 20% level 
int level_2 = 10; // 0% level 

int on_1 = 0;// 20%
int on_2 = 0;// 0%

 /*Output*/
 /***light***/
int LEDpin1 = 2;          // connect White LED to pin 2 (PWM pin) (white LED)
int LEDpin2 = 3;          // connect White LED to pin 3 (PWM pin) (white LED)
int LEDpin3 = 4;          // connect Blue LED to pin 4 (PWM pin) (Blue LED)
int LEDpin4 = 5;          // connect Red LED to pin 5 (PWM pin) (Red LED)
/***water***/
int water_pump = 6;       // connect water pump to pin 6

// parameter for light
int dim_min = 600;
int dim_max = 700;
int moisture_not_connect = 20;
int moisture_standard = 200;

/*flags*/
boolean switch_red_led = false;
boolean switch_blue_led = false;
boolean red_led = false;
boolean blue_led = false;
boolean white_led_1 = false;
boolean white_led_2 = false;

boolean sensor_flag_1 = true;
boolean sensor_flag_2 = true;
boolean watering = false;
boolean manual_pump = false;
boolean water_tank_empty = false;


/*Sensors readings*/
void reading_light_sensors (void){
  photocellReading1 = analogRead(photocellPin1);  
  photocellReading2 = analogRead(photocellPin2);
  photocellReading3 = analogRead(photocellPin3);
  photocellReading4 = analogRead(photocellPin4);
  photocell_average = (photocellReading1 + photocellReading2 + photocellReading3 + photocellReading4)/4; 
}

void reading_moisture_sensors(void){
  moisture_1 = analogRead(sensor_1);
  moisture_2 = analogRead(sensor_2);
  moisture_avg = (moisture_1 + moisture_2)/2;
  }

void update_sensor_data (void){
  reading_light_sensors();
  reading_moisture_sensors();
}
/*light function*/
void light_status (boolean switch_red_led, boolean switch_blue_led) {


  // Different readings from analog will result in different light intensity. The number will be determine more accurately later
  if (photocell_average < dim_min) {
    white_led_1 = true;
    white_led_2 = true;
     
  } else if (photocell_average < dim_max && photocell_average > dim_min) {
    white_led_1 = true;
    white_led_2 = false;
  } else {
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
      digitalWrite(LEDpin4,HIGH);
    }else {
      digitalWrite(LEDpin4,LOW);
      } 
  
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
/*soil moisture*/

void moisture_status_state (){
  if(moisture_1 < moisture_not_connect ){
    sensor_flag_1 = false;
    watering = false;
  } else if(moisture_2 < moisture_not_connect ){
    sensor_flag_2 = false;
    watering = false;
  } else if (water_tank_empty){
    watering = false;     
  } else if(moisture_avg < moisture_standard && moisture_avg > moisture_not_connect){
   watering = true;  
  } else {
    watering = false;
  }
}

void pumping (boolean manual_pump){
  /*Add the condition to consider manaul pump feature first, if manual pump is on, we won't consider any condition for auto mode */
  /**************************************/
  if (!sensor_flag_1 || !sensor_flag_2){
  }
  if (manual_pump){ 
     digitalWrite(water_pump, HIGH);
     delay(2000);
     digitalWrite(water_pump, LOW);
  }else if (watering){
     digitalWrite(water_pump, HIGH);
     delay(2000);
     digitalWrite(water_pump, LOW);        
  }else {
     digitalWrite(water_pump, LOW);
    }
  sensor_flag_1 = true;
  sensor_flag_2 = true;
  watering = false; 
  manual_pump = false; // Reset the flag. We will disable the button on the app for 5 seconds after user push it. so we don't want water pump active when user can not push the button
}
/*water level*/
void water_level_status(){
  on_1 = digitalRead(level_1);   // read the input pin
  on_2 = digitalRead(level_2);   // read the input pin
  Serial.println(on_1);
  Serial.println(on_2);
  if(on_1 == 0){
      digitalWrite(water_level_warning_1,HIGH);
  }else{
      digitalWrite(water_level_warning_1,LOW);
  }
  if(on_2 == 0){
      digitalWrite(water_level_warning_2,HIGH);
      water_tank_empty = true;
  }else{
      digitalWrite(water_level_warning_2,LOW);
      water_tank_empty = false;
  }
  delay(1000);
  
}

/*set up and loop*/
  void setup(void) {
  // We'll send debugging information via the Serial monitor
  Serial.begin(9600);
  pinMode(LEDpin1, OUTPUT);
  pinMode(LEDpin2, OUTPUT);  
  pinMode(LEDpin3, OUTPUT); 
  pinMode(LEDpin4, OUTPUT); 
  pinMode(water_pump, OUTPUT);
  pinMode(water_level_warning_1, OUTPUT);      // sets the digital pin 7 as output
  pinMode(water_level_warning_2, OUTPUT);      // sets the digital pin 8 as output
  pinMode(level_1, INPUT);      // sets the digital pin 9 as input
  pinMode(level_2, INPUT);      // sets the digital pin 10 as input
  }
void loop(void) {
  update_sensor_data();// water level, all sensors data are read in this functions
  //timing issue
  water_level_status();
  moisture_status_state();
  pumping(manual_pump);
  light_status(switch_red_led,switch_blue_led);
  turn_on_white_light();
  turn_on_blue_red_led();
   
}
