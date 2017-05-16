//lcd pot resistance
//middle to peg under screw- 8.8k, V0 & pwr
//middle to other peg- 1.3k, gnd & V0

#include <OneWire.h>
#include <LiquidCrystal.h>

int DS18S20_Pin = 26; //DS18S20 Signal pin on digital 2

//Temperature chip i/o
OneWire ds(DS18S20_Pin); // on digital pin 2
// initialize the library with the numbers of the interface pins
//LiquidCrystal lcd(0, 1, 27, 28, 29, 30);
LiquidCrystal lcd(19, 18, 27, 28, 29, 30);

#define CH1 7   // Connect Digital Pin 7 on Arduino to CH1 on Relay Module   water pump

void setup() {
  Serial.begin(9600);
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("fucking temp");
  Serial.print("GO TO HELL");

  //Setup all the Arduino Pins
  pinMode(CH1, OUTPUT);

  //Turn OFF any power to the Relay channels
  digitalWrite(CH1,LOW);

  delay(2000);
}

void loop() {
  int SoilSen1 = analogRead(A4);
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 1);
  // print the number of seconds since reset:
  float temperature = getTemp();
  lcd.print(temperature);
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
