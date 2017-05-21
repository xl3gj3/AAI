int ledPin1 = 6; // LED connected to digital pin 13
int ledPin2 = 7; // LED connected to digital pin 13
int level_1 = 3; // 20% level 
int level_2 = 4; // 0% level 

int on_1 = 0;
int on_2 = 0;
void setup()
{
  Serial.begin(9600);
  delay(500);//Delay to let system boot
  pinMode(ledPin1, OUTPUT);      // sets the digital pin 13 as output
  pinMode(ledPin2, OUTPUT);      // sets the digital pin 13 as output
  pinMode(level_1, INPUT);      // sets the digital pin 7 as input
  pinMode(level_2, INPUT);      // sets the digital pin 7 as input
}
void water_level_status(){
  on_1 = digitalRead(level_1);   // read the input pin
  on_2 = digitalRead(level_2);   // read the input pin
  Serial.println(on_1);
  Serial.println(on_2);
  if(on_1 == 0){
      digitalWrite(ledPin1,HIGH);
  }else{
      digitalWrite(ledPin1,LOW);
  }
  if(on_2 == 0){
      digitalWrite(ledPin2,HIGH);
  }else{
      digitalWrite(ledPin2,LOW);
  }
  delay(1000);
  
}
void loop()
{
  water_level_status();
  
}
