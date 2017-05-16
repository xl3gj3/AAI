/* ===============================================================
      Project: 4 Channel 5V Relay Module
       Author: Scott C
      Created: 7th Sept 2014
  Arduino IDE: 1.0.5
      Website: http://arduinobasics.blogspot.com.au
  Description: Explore the difference between NC and NO terminals.
================================================================== */

 /* 
  Connect 5V on Arduino to VCC on Relay Module
  Connect GND on Arduino to GND on Relay Module 
  Connect GND on Arduino to the Common Terminal (middle terminal) on Relay Module. */
 
 #define CH1 23   // Connect Digital Pin 8 on Arduino to CH1 on Relay Module
 //#define LEDgreen 4 //Connect Digital Pin 4 on Arduino to Green LED (+ 330 ohm resistor) and then to "NO" terminal on relay module
 //#define LEDyellow 12 //Connect Digital Pin 12 on Arduino to Yellow LED (+ 330 ohm resistor) and then to "NC" terminal on relay module
 
 void setup(){
   //Setup all the Arduino Pins
   pinMode(CH1, OUTPUT);
   //pinMode(CH3, OUTPUT);
   //pinMode(LEDgreen, OUTPUT);
   //pinMode(LEDyellow, OUTPUT);
   
   //Provide power to both LEDs
   //digitalWrite(LEDgreen, HIGH);
   //digitalWrite(LEDyellow, HIGH);
   
   //Turn OFF any power to the Relay channels
   digitalWrite(CH1,LOW);
   //digitalWrite(CH3,LOW);
   delay(2000); //Wait 2 seconds before starting sequence
 }
 
 void loop(){
   digitalWrite(CH1, HIGH);  //Green LED on, Yellow LED off
   delay(10000);
   digitalWrite(CH1, LOW);   //Yellow LED on, Green LED off
   delay(10000);
   /*digitalWrite(CH3, HIGH);  //Relay 3 switches to NO
   delay(1000);
   digitalWrite(CH3,LOW);    //Relay 3 switches to NC
   delay(1000);*/
 }
