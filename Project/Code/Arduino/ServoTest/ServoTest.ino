// Sweep
// by BARRAGAN <http://barraganstudio.com> 
// This example code is in the public domain.


#include <Servo.h> 

//tilt
#define LEVEL 90
#define DOWN 75

//pan
#define MIDDLE 90
#define ALL_LEFT 50
#define ALL_RIGHT 130

 
Servo myservo;  // create servo object to control a servo 
                // a maximum of eight servo objects can be created 
 
int pos = 0;    // variable to store the servo position 
 
void setup() 
{ 
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object 
} 
 
 
void loop() 
{ 
  //myservo.write(130);
  
  
  for(pos = 50; pos < 130; pos += 1)  // goes from 0 degrees to 180 degrees 
  {                                  // in steps of 1 degree 
    myservo.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(50);                       // waits 15ms for the servo to reach the position 
  } 
  for(pos = 130; pos>=50; pos-=1)     // goes from 180 degrees to 0 degrees 
  {                                
    myservo.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(50);                       // waits 15ms for the servo to reach the position 
  } 
  
  
} 
