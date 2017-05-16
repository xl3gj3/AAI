
 #define CH1 7   // Connect Digital Pin 7 on Arduino to CH1 on Relay Module

void setup() {
// initialize serial communication at 9600 bits per second:
Serial.begin(9600);

//Setup all the Arduino Pins
pinMode(CH1, OUTPUT);

//Turn OFF any power to the Relay channels
digitalWrite(CH1,LOW);
delay(2000); //Wait 2 seconds before starting sequence
}

void loop() {
// read the input on analog pin 0:
int sensorValue = analogRead(A0);
int pw_delay = 5000;

if(sensorValue < 200 && sensorValue > 20){
  digitalWrite(CH1, HIGH);
  Serial.print(sensorValue);
  Serial.print("\tWatering \n");
}else{
  digitalWrite(CH1, LOW);
  Serial.print(sensorValue);
    
  if(sensorValue > 800){
    Serial.print("\tSoil is wet, not need to water\n");
  }else if(sensorValue < 20){
    Serial.print("\tSoil sensor is not connect to soil\n");
  }else{
    Serial.print("\tSoil is fine!!!!\n");
  }
  
}

delay(5000);

}
