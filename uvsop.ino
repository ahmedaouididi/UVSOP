// NB!! :this code can be changed according to the real stimulation
#include <LiquidCrystal.h>
LiquidCrystal lcd(7,8,9,10,11,12); // include the library code: lcd 
#define LED_PIN4  7 // pint used to connect the relay
int runTimer = 1; 
int runFor = 1200; // time in seconds
int relayPin=4;
int data = 0;
int inByte = 0;               // incoming serial byte
boolean status_unlock;
int minute,sec;
const int led_red_pin = 10;         // pin used to indicate the activation of the UVC lamps
const int buzzer_pin = 11; // pin used to connect the passive buzzer
const int PIRPin = 8;         // input pin for the PIR sensor
int pirState = LOW;           
int val = 0;                  
void setup()
{pinMode(2, INPUT_PULLUP);
// start serial port at 9600 bps:
 pinMode(buzzerPin, OUTPUT);
   pinMode(relayPin,OUTPUT);
  lcd.begin(16, 2);
Serial.begin(9600);
pinMode(PIRPin, INPUT); // pin mode for the PIR sensor
pinMode(LED_PIN4, OUTPUT); // pin mode for the relay
pinMode(led_red_pin, OUTPUT);// pin mode for the red led
digitalWrite(LED_PIN4, LOW);  
digitalWrite(led_red_pin, LOW);  
pinMode(buzzer_pin, OUTPUT); //pin mode for the passive buzzer
digitalWrite(buzzer_pin, LOW);

status_unlock = false;
sec = 0;
}

void loop()
{  int sensorVal = digitalRead(2);
  if (sensorVal == 1) {
   if(runTimer == 1){ 
      digitalWrite(relayPin,LOW); // relay is OFF during countdown
      /* change to HIGH if you want the relay to be ON while countdowning */
      lcd.clear();
      lcd.print("TIMER=");
      //Start timer
      timer(); 
      val = digitalRead(PIRPin); //variable to storage the state of the PIR sensor
if (val == HIGH) // condition when the PIR sensor doesn't detect a movement 
{
  digitalWrite(LED_PIN4, LOW); // the relay is keeped turned off
  digitalWrite(led_red_pin , LOW);// the red led is keeped turned off 
  }
else // condition when the PIR sensor detects a movement
{
  if (Serial.available() > 0) {
    inByte = Serial.read(); // get incoming byte:
   runTimer = 0;
   lcd.noDisplay();
   delay(250);
   for(int duration = 0; duration < 100; duration ++){
      digitalWrite(buzzerPin, HIGH);
      delayMicroseconds(500);
      digitalWrite(buzzerPin, LOW);
      delayMicroseconds(500);
   } 
   lcd.display();
   delay(250);
}

void timer() {
   for(int timer = runFor;timer > 0; --timer){
   if(timer >= 10) {
      lcd.setCursor(6,0); 
   } else {   
      lcd.setCursor(6,0);
      lcd.print("0");
      lcd.setCursor(7,0);
   }
   lcd.print(timer);
   lcd.print(" SECOND!");
   delay(1000);
   }
   lcd.setCursor(0,0);
   lcd.clear();
   lcd.print(" TIME IS OVER!");  
}
}
if(inByte == 'Q'){
digitalWrite(led_red_pin , HIGH);
digitalWrite(buzzer_pin, HIGH);
delay(200);
digitalWrite(led_red_pin , LOW);
delay(200);
digitalWrite(led_red_pin , HIGH);
digitalWrite(buzzer_pin, HIGH);
delay(200);
digitalWrite(led_red_pin , LOW);
delay(200);
digitalWrite(led_red_pin , HIGH);
digitalWrite(buzzer_pin, HIGH);
delay(200);
digitalWrite(led_red_pin , LOW);
digitalWrite(buzzer_pin, LOW);
delay(200);
digitalWrite(led_red_pin , HIGH);
digitalWrite(buzzer_pin, HIGH);
delay(200);
digitalWrite(led_red_pin , LOW);
digitalWrite(buzzer_pin, LOW);
delay(200);
digitalWrite(led_red_pin , HIGH);
digitalWrite(buzzer_pin, HIGH);
delay(200);
digitalWrite(led_red_pin , LOW);
digitalWrite(buzzer_pin, LOW);
delay(200);
digitalWrite(led_red_pin , HIGH);
digitalWrite(buzzer_pin, HIGH);
delay(1000);
digitalWrite(led_red_pin , LOW);
digitalWrite(buzzer_pin, LOW);
delay(200);
digitalWrite(led_red_pin , HIGH);
digitalWrite(buzzer_pin, HIGH);
delay(3000);
digitalWrite(led_red_pin , LOW);
digitalWrite(buzzer_pin, LOW);
digitalWrite(LED_PIN4, HIGH);        
digitalWrite(led_red_pin , HIGH);// red led is turned on when the relay is activated
Serial.write((byte)'Q'); 
inByte = 0;
}

if(inByte == 'q'){
digitalWrite(LED_PIN4, LOW);        
digitalWrite(led_red_pin , LOW);// red led is turned off when the relay is inactivated
Serial.write((byte)'q'); 
inByte = 0;
if(inByte == 'S'){
Serial.write((byte)'S');
delay(5000);
sec = 0;
}  
}
} 
}
} 


