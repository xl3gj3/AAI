#include <Time.h>
#include <TimeLib.h>



 #define CH1 7   // Connect Digital Pin 7 on Arduino to CH1 on Relay Module
int moisture_1 = 0;
int moisture_2 = 0;
int sensor_1 = 0;// temp decision, will change input pin later
int sensor_2 = 1;
int moisture_avg = 0;

boolean sensor_flag_1 = true;
boolean sensor_flag_2 = true;
boolean watering = false;

void setup() {
// initialize serial communication at 9600 bits per second:
Serial.begin(9600);

//Setup all the Arduino Pins
pinMode(CH1, OUTPUT);

//Turn OFF any power to the Relay channels
digitalWrite(CH1,LOW);
delay(2000); //Wait 2 seconds before starting sequence

}

void reading_moisture_sensors(void){
  moisture_1 = analogRead(sensor_1);
  moisture_2 = analogRead(sensor_2);
  Serial.print(moisture_1);
  Serial.print("above is sensor 1\n");
  Serial.print(moisture_2);
  Serial.print("above is sensor 2\n");
  moisture_avg = (moisture_1 + moisture_2)/2;
  }
void update_sensor_data(void){
  reading_moisture_sensors();
}

void moisture_status_state (){
  if(moisture_1 < 20 ){
    Serial.print("\tSoil sensor 1 is not connect to soil\n");
    sensor_flag_1 = false;
    watering = false;
  } else if(moisture_2 < 20 ){
    Serial.print("\tSoil sensor 2 is not connect to soil\n");
    sensor_flag_2 = false;
    watering = false;
  }
  else if(moisture_avg < 200 && moisture_avg > 20){
   Serial.print(moisture_avg);
   Serial.print("\tWatering \n");
   watering = true;  
  }  else{
    digitalWrite(CH1, LOW); 
    if(moisture_avg > 800){
      Serial.print("\tSoil is wet, not need to water\n");
      watering = false;
    }else{
      Serial.print("\tSoil is fine!!!!\n");
      watering = false;
    }
  }
}

void pumping (){

  if (!sensor_flag_1 || !sensor_flag_2){
      Serial.print("\tOne of the Soil sensors is not connect to soil\n");
  }

  if (watering){
       digitalWrite(CH1, HIGH);
       delay(2000);
       digitalWrite(CH1, LOW);        
  }else {
     digitalWrite(CH1, LOW);
    }
  sensor_flag_1 = true;
  sensor_flag_2 = true;
  watering = false;
}
void loop() {
// read the input on analog pin 0:
  update_sensor_data();
  moisture_status_state();
  pumping();
  delay(1000);
}

