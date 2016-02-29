#include <Servo.h> 

//#define DEBUG

//tilt
#define TILT_LEVEL 90
#define TILT_MAX_DOWN 75

//pan
#define PAN_MIDDLE 90
#define PAN_MAX_LEFT 50
#define PAN_MAX_RIGHT 130

 
Servo panServo;  // create servo object to control a servo 
Servo tiltServo;
 
int pan_pos;    // variable to store the servo position 
int tilt_pos;
int new_pos;

char command;
 
void setup() 
{ 
  panServo.attach(5);  // attaches the servo on pin 9 to the servo object 
  panServo.write(PAN_MIDDLE);
  
  tiltServo.attach(6);
  tiltServo.write(TILT_LEVEL);  
  
  pan_pos = panServo.read();
  tilt_pos = tiltServo.read();
  
  Serial.begin(9600);
} 
 
 
void loop() 
{   
  if (Serial.available())
  {
    //get command (i.e. read laser, move pan-tilt)
    command = Serial.read();
    
    //if there is a number trailing, then get that too
    new_pos = Serial.parseInt();
    
    if(command == 'p')
    {
      // we want to move the pan servo
      
      if(new_pos >= PAN_MAX_LEFT && new_pos <= PAN_MAX_RIGHT)
      {
        #ifdef DEBUG
        Serial.print("Moving Pan Servo: ");
        Serial.print(new_pos);
        Serial.print(" -> ");
        Serial.println(pan_pos);
        #endif
        
        if (new_pos > pan_pos)
        {
          while (pan_pos < new_pos)
          {
            pan_pos++;
            
            panServo.write(pan_pos);
            delay(50);
            
            #ifdef DEBUG
            Serial.println("right!");
            #endif
          }
        }
        else if(new_pos < pan_pos)
        {
          while (new_pos < pan_pos)
          {
            pan_pos--;
            
            panServo.write(pan_pos);
            delay(50);
            
            #ifdef DEBUG
            Serial.println("left!");
            #endif
          }
        }
        
        new_pos = panServo.read();
      }
      else
      {
        #ifdef DEBUG
        Serial.println("===== Bad Pan Servo input =====");
        Serial.print(" - Servo: ");
        Serial.println(command);
        Serial.print(" - Position: ");
        Serial.println(new_pos);
        #endif
      }
    } 
    else if(command == 't')
    {
      // We want to move the tilt servo
      
      if(new_pos >= TILT_MAX_DOWN && new_pos <= TILT_LEVEL)
        {
          if (new_pos > tilt_pos)
          {
            while (tilt_pos < new_pos)
            {
              tilt_pos++;
              
              tiltServo.write(tilt_pos);
              delay(50);
              
              #ifdef DEBUG
              Serial.println("up!");
              #endif
            }
          }
          else if(new_pos < tilt_pos)
          {
            while (new_pos < tilt_pos)
            {
              tilt_pos--;
              
              tiltServo.write(tilt_pos);
              delay(50);
              
              #ifdef DEBUG
              Serial.println("down!");
              #endif
            }
          }
          
          new_pos = tiltServo.read();
        }
        else
        {
          #ifdef DEBUG
          Serial.println("===== Bad Tilt Servo input =====");
          Serial.print(" - Servo: ");
          Serial.println(command);
          Serial.print(" - Position: ");
          Serial.println(new_pos);
          #endif
        }
    }
    else if(command == 'r')
    {
      // We want to read the LRF
      
      //test response
      Serial.println(123.45);
      
      #ifdef DEBUG
      Serial.println("===== Read LRF =====");
      #endif 
    }
    else
    {
      #ifdef DEBUG
      Serial.println("===== Bad Input =====");
      Serial.print("Command: ");
      Serial.println(command);
      #endif
    }
  }
} 

