/*
  LiquidCrystal Library - Hello World

 Demonstrates the use a 16x2 LCD display.  The LiquidCrystal
 library works with all LCD displays that are compatible with the
 Hitachi HD44780 driver. There are many of them out there, and you
 can usually tell them by the 16-pin interface.

 This sketch prints "Hello World!" to the LCD
 and shows the time.

  The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)

 Library originally added 18 Apr 2008
 by David A. Mellis
 library modified 5 Jul 2009
 by Limor Fried (http://www.ladyada.net)
 example added 9 Jul 2009
 by Tom Igoe
 modified 22 Nov 2010
 by Tom Igoe

 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/LiquidCrystal
 */

// include the library code:
#include <LiquidCrystal.h>
#include<servo.h>
const int button=8;
const int button2=10;
const int buzzer=13;
const int TOUCH_SENSOR_PIN = 7; // Arduino pin connected to touch sensor's pin
const int SERVO_PIN        = 9; // Arduino pin connected to servo motor's pin 
Servo servo; // create servo object to control a servo
// variables will change:
int angle = 0;         // the current angle of servo motor
int lastTouchState;    // the previous state of touch sensor
int currentTouchState; // the current state of touch sensor
int val;
int Val;
int count=0;
int p;
int limit=0;


// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Person count: ");
    Serial.begin(9600);               // initialize serial
  pinMode(TOUCH_SENSOR_PIN, INPUT); // set arduino pin to input mode
  servo.attach(SERVO_PIN);          // attaches the servo on pin 9 to the servo object

  servo.write(angle);
  currentTouchState = digitalRead(TOUCH_SENSOR_PIN);
}

void loop(){
  limit=count;
	//set the buzzer in such a way when the value reaches limit it beeps
  if(limit>=10){
  	tone(buzzer,600);
	//set the cursor to column 12, line 1 and print 'Full'
    lcd.setCursor(12,1);
    lcd.print("Full");
  } 
  else
  {
    noTone(buzzer);
    //set the cursor to column 12, line 1 and print nothing
    lcd.setCursor(12,1);
    lcd.print("    ");
  }
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  //val=digitalRead(button);
  //if(val==HIGH){
  // p=++count;
   // delay(40);
  //}
  //Val=digitalRead(button2);
  //if(Val==HIGH){
  // if(count<=0)
  //  {  
  //  lcd.setCursor(2,1);
  //   lcd.print(0);
  //  }
    
  //  else{
  //  p=--count;
  //  delay(40);
  //  }
  while(limit!=10){
    
    lastTouchState    = currentTouchState;             // save the last state
  currentTouchState = digitalRead(TOUCH_SENSOR_PIN); // read new state

  if(lastTouchState == LOW && currentTouchState == HIGH) {
    Serial.println("The sensor is touched");
    p=++count;
    delay(40);
 

    // change angle of servo motor
    if(angle == 0)
      angle = 90;
    else
    if(angle == 90)
      angle = 0;

    // control servo motor arccoding to the angle
    servo.write(angle);
  }
    else if(lastTouchState == HIGH && currentTouchState == LOW){
      if(angle == 90)
        angle = 0;
      else 
      if(angle == 0)
        angle=90;
    }
  }  
  lcd.setCursor(0,0);
  // print the number of seconds since reset:
  //lcd.print(millis() / 1000);
  lcd.setCursor(1,1);
  if(p<10){
    lcd.print(" ");
  }
  lcd.print(p);
}
 