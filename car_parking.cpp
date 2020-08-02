//library for LCD
#include <LiquidCrystal.h>
//setting up pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

//piezo pin
int speaker_pin = 8;

//for ultrasonic sensor
int inches = 0;
int cm = 0;

//min distance between car and wall
int dist = 10;

//pushbutton pins for increasing or decreasing dist
int switch_inc = 6;
int switch_dec = 9;


//function to get distance from ultrasonic sensor
long readUltrasonicDistance(int triggerPin, int echoPin)
{
    pinMode(triggerPin, OUTPUT);  // Clear the trigger
    digitalWrite(triggerPin, LOW);
    delayMicroseconds(2);
    // Sets the trigger pin to HIGH state for 10 microseconds
    digitalWrite(triggerPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(triggerPin, LOW);
    pinMode(echoPin, INPUT);
    // Reads the echo pin, and returns the sound wave travel time in microseconds
    return pulseIn(echoPin, HIGH);
}



void setup()
{
    //output to serial port
    Serial.begin(9600);
    lcd.begin(16, 2);


    //piezo output 
    pinMode(speaker_pin, OUTPUT);

    //output for pushbutton pins
    pinMode(switch_inc, INPUT);
    pinMode(switch_dec, INPUT);

    //debugging setting distance
    //Serial.println("\n\nSet the Distance:");
}

void loop()
{
    //print current dist setting on lcd
    lcd.print("Distance : ");
    lcd.print(dist);
    lcd.print(" cm");
    delay(10);

    //debugging, input distance from serial port
    //if (dist == 0){
    // dist= Serial.parseInt();
    // Serial.print(dist);
    //}


    //if increase button is pressed, dist increases by one
    if (digitalRead(switch_inc) == HIGH)
    	{
     		dist += 1; 
    	}

    //if decrease button is pressed, dist decreases by one
    if (digitalRead(switch_dec) == HIGH)
    	{
      		dist -= 1;
    	}


      // measure the ping time in cm
     cm = 0.01723 * readUltrasonicDistance(7, 7);
      // convert to inches by dividing by 2.54

    //debugging block for serial output
    //===================================================//
      //inches = (cm / 2.54);
      //Serial.print(inches);
      //Serial.print("in, ");
      //Serial.print(cm);
      //Serial.println("cm");
    //====================================================//
	
  
  	delay(100); // Wait for 100 millisecond(s)

  
    //buzzer sound when the distance between car and wall is less 
    //the distance threshold set by us.

    if (cm < dist)
    {
      	tone(speaker_pin, 1000, 1000);
    }

  
    //clear lcd to print updated dist every time
    lcd.clear();

}


