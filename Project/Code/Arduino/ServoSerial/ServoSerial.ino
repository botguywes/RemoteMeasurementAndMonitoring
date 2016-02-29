// Sweep
// by BARRAGAN <http://barraganstudio.com> 
// This example code is in the public domain.


#include <Servo.h> 

//tilt
#define LEVEL 90
#define DOWN 75

//pan
#define PAN_MIDDLE 90
#define PAN_MAX_LEFT 50
#define PAN_MAX_RIGHT 130

 
Servo myservo;  // create servo object to control a servo 
                // a maximum of eight servo objects can be created 
 
int pos = 0;    // variable to store the servo position 
int new_pos;
 
void setup() 
{ 
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object 
  myservo.write(PAN_MIDDLE);
  
  pos = PAN_MIDDLE;
  
  Serial.begin(9600);
} 
 
 
void loop() 
{   
  if (Serial.available())
  {
    char servoNumber = Serial.read();
    
    new_pos = Serial.parseInt();

    Serial.print("Moving: ");
    Serial.print(new_pos);
    Serial.print(" -> ");
    Serial.println(pos);
    
    if(servoNumber == 's' && new_pos >= PAN_MAX_LEFT && new_pos <= PAN_MAX_RIGHT)
    {
      if (new_pos > pos)
      {
        while (pos < new_pos)
        {
          pos++;
          
          myservo.write(pos);
          delay(50);
          
          Serial.println("up!");
        }
      }
      else if(new_pos < pos)
      {
        while (new_pos < pos)
        {
          pos--;
          
          myservo.write(pos);
          delay(50);
          
          Serial.println("down!");
        }
      }
      
      new_pos = pos;
    }
    else
    {
      Serial.print("Bad input: ");
      Serial.println(servoNumber);
      Serial.println(new_pos);
    }
  } 
} 

