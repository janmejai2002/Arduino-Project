//library code for lcd
#include <LiquidCrystal.h>

//setting up pins
const int rs = 9, en = 8, d4 = 5, d5 = 4, d6 = 3, d7 = 2;

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);




//servo motor
#include <Servo.h>
Servo servo_9;
int pos = 0;
//servo motor end

//ultrasonic sensor pin
const int pingPin = 12;

//lcd
signed short seconds;
char timeline[16];

void setup()
{
  
  servo_9.attach(13); //servo pin
  Serial.begin(9600);
  
  pinMode(11,OUTPUT);// led 
  
  //lcd initialize
  lcd.begin(16, 2);
  lcd.print("Time : ");

}

void loop()
{
  
  long duration, cm;
  //Ultrasonic start
  // The PING))) is triggered by a HIGH pulse of 2 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);

  // The same pin is used to read the signal from the PING))): a HIGH
  // pulse whose duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(pingPin, INPUT);
  duration = pulseIn(pingPin, HIGH);

  // convert the time into a distance
  cm = microsecondsToCentimeters(duration);

  // Print the distance
  Serial.print("Distance: ");
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
  // ultrasonic end
  
  
  
  unsigned long currentMillis = millis();
  unsigned long previousMillis = 0;        

 // the servo motor should activate when object is
 //less than 30cm close to the sensor
 if(cm < 30) 
 {
   
    
     unsigned long previousMillis = 0;        // will store last time LCD was updated
     const long interval = 1000;           // interval at which to blink (milliseconds)

   
   	 // sweep the servo from 0 to 180 degrees in steps
     // of 1 degrees
     for (pos = 0; pos <= 180; pos += 1) 
     {
       
       unsigned long forloop_Millis = millis();

       // tell servo to go to position in variable 'pos'
       servo_9.write(pos); 

       //LCD TIMER START
       if (forloop_Millis - previousMillis >= interval)
       {
           previousMillis = forloop_Millis;
           lcd.setCursor(0, 1);
           sprintf(timeline,"%0.2d secs", seconds);
           lcd.print(timeline);
           seconds += 1;
           if(seconds == 21){seconds = 0;} 
       }

       //led buld switch on
       digitalWrite(11,HIGH);

       // wait 20ms for servo to reach the position
       delay(115);

     }

     //switch of the bulb
     digitalWrite(11,LOW);



     //moving servo back to zero
     for (pos = 180; pos >= 0; pos -= 1)
     {
         // tell servo to go to position in variable 'pos'
         servo_9.write(pos);
         // wait 20 ms for servo to reach the position
         delay(20); // Wait for 15 millisecond(s)
     }

  	} //if end
 
  
   delay(100);


}//loop end


//FUNCTIONS 

long microsecondsToCentimeters(long microseconds) {
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds / 29 / 2;
}

