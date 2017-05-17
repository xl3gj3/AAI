
#include <OneWire.h>
#include <LiquidCrystal.h>
  
int DS18S20_Pin = 26; //DS18S20 Signal pin on digital 2
//Temperature chip i/o
OneWire ds(DS18S20_Pin); // on digital pin 2
// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(19, 18, 27, 28, 29, 30);

#define CH1 7   // Connect Digital Pin 7 on Arduino to CH1 on Relay Module   water pump
#define CH2 8   // Connect Digital Pin 8 on Arduino to CH2 on Relay Module   white LED1
#define CH3 9   // Connect Digital Pin 9 on Arduino to CH3 on Relay Module   white LED2
#define CH4 10  // Connect Digital Pin 10 on Arduino to CH4 on Relay Module  red LED
#define CH5 11  // Connect Digital Pin 11 on Arduino to CH5 on Relay Module  blue LED
#define CH6 12  // Connect Digital Pin 12 on Arduino to CH6 on Relay Module  Heater
#define CH7 13  // Connect Digital Pin 13 on Arduino to CH7 on Relay Module  Cooler
#define CH8 14  // Connect Digital Pin 14 on Arduino to CH8 on Relay Module  Humidity fan
//#define CH9 15  // Connect Digital Pin 15 on Arduino to CH9 on Relay Module  temperature fan

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  //Setup all the Arduino Pins
  pinMode(CH1, OUTPUT);  pinMode(CH2, OUTPUT);
  pinMode(CH3, OUTPUT);  pinMode(CH4, OUTPUT);
  pinMode(CH5, OUTPUT);  pinMode(CH6, OUTPUT);
  pinMode(CH7, OUTPUT);  pinMode(CH8, OUTPUT);

  //Turn OFF any power to the Relay channels
  digitalWrite(CH1,LOW);  digitalWrite(CH2,LOW);
  digitalWrite(CH3,LOW);  digitalWrite(CH4,LOW);
  digitalWrite(CH5,LOW);  digitalWrite(CH6,LOW);
  digitalWrite(CH7,LOW);  digitalWrite(CH8,LOW);  
   
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  Serial.println("Welcome to Gaia! :)");
  lcd.print("Hello!");

  delay(500); //Wait 2 seconds before starting sequence
}

void loop() {
  // read the input on analog pin 0:
  int LightSen1 = analogRead(A0);  int LightSen2 = analogRead(A1);
  int LightSen3 = analogRead(A2);  int LightSen4 = analogRead(A3);
  int SoilSen1 = analogRead(A4);   int SoilSen2 = analogRead(A5);
  int HumiditySen = analogRead(A6);
  float temperature = getTemp();
  int pw_delay = 5000;

   // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 1);
  // print the number of seconds since reset:
  Serial.print("Temperature = ");
  Serial.print(temperature);
  lcd.print(temperature);
    
  WateringSystem(SoilSen1);
  //delay(500);
  LightingSystem(LightSen1);  
  //delay(500);
}

//-------------SYSTEM FUNCTIONS-----------
void LightingSystem(int photocellReading) {
//  photocellReading = analogRead(photocellPin);   
  Serial.print("\nLight Reading = ");
  Serial.print(photocellReading);     // the raw analog reading
 
  // We'll have a few threshholds, qualitatively determined
  if (photocellReading < 300) {
    Serial.println(" - Dark");
    lcd.setCursor(6,1);
    lcd.print("Dark     ");
    digitalWrite(CH2,HIGH);
    digitalWrite(CH3,HIGH);
     
  } else if (photocellReading < 400) {
    Serial.println(" - Dim");
    lcd.setCursor(6,1);
    lcd.print("Dim      ");
    digitalWrite(CH2,HIGH);
    digitalWrite(CH3,LOW);
  } else if (photocellReading < 500) {
    digitalWrite(CH2,LOW);
    digitalWrite(CH3,LOW);
    Serial.println(" - Light");
    lcd.setCursor(6,1);
    lcd.print("Light    ");
  } else if (photocellReading < 800) {
    digitalWrite(CH2,LOW);
    digitalWrite(CH3,LOW);
    Serial.println(" - Bright");
    lcd.setCursor(6,1);
    lcd.print("Bright   ");
  } else {
    Serial.println(" - Very bright");
    lcd.setCursor(6,1);
    lcd.print("V Bright");
    digitalWrite(CH2,LOW);
    digitalWrite(CH3,LOW);
  }

}

void WateringSystem(int sensorValue) {
  Serial.print("\nSoil sensor: ");
  Serial.print(sensorValue);
  if(sensorValue < 200 && sensorValue > 50){
    digitalWrite(CH1, HIGH);
    Serial.print("\tWatering \n");
    lcd.setCursor(7,0);
    lcd.print("Watering  ");
    delay(2000);
    digitalWrite(CH1, LOW);
  }else{
    lcd.setCursor(7,0);
    lcd.print("N Watering");
    if(sensorValue > 800){
      Serial.print("\tSoil is wet, not need to water\n");
    }else if(sensorValue < 50){
      Serial.print("\tSoil sensor is not connect to soil\n");
    }else{
      Serial.print("\tSoil is fine!!!!\n");
    }
}
//delay(5000);
}

float getTemp(){
 //returns the temperature from one DS18S20 in DEG Celsius

 byte data[12];
 byte addr[8];

 if ( !ds.search(addr)) {
   //no more sensors on chain, reset search
   ds.reset_search();
   return -1000;
 }
  if ( OneWire::crc8( addr, 7) != addr[7]) {
   Serial.println("CRC is not valid!");
   return -1000;
 }

 if ( addr[0] != 0x10 && addr[0] != 0x28) {
   Serial.print("Device is not recognized");
   return -1000;
 }

 ds.reset();
 ds.select(addr);
 ds.write(0x44,1); // start conversion, with parasite power on at the end
 
 delay(750); // Wait for temperature conversion to complete

 byte present = ds.reset();
 ds.select(addr);  
 ds.write(0xBE); // Read Scratchpad

 
 for (int i = 0; i < 9; i++) { // we need 9 bytes
  data[i] = ds.read();
 }
 
 ds.reset_search();
 
 byte MSB = data[1];
 byte LSB = data[0];

 float tempRead = ((MSB << 8) | LSB); //using two's compliment
 float TemperatureSum = tempRead / 16;
 
 return TemperatureSum;
 
}
