#include <Servo.h> 
#include <SoftwareSerial.h>

//#define DEBUG

//tilt
#define TILT_LEVEL 90
#define TILT_MAX_DOWN 75

#define UP 1
#define DOWN 2

//pan
#define PAN_MIDDLE 90
#define PAN_MAX_LEFT 50
#define PAN_MAX_RIGHT 130

#define LEFT 1
#define RIGHT 2

// laser defines
#define SF01_ANALOG 1
#define SF01_0_0V_DISTANCE        0.0
#define SF01_3_3V_DISTANCE        33.00
int analog;
float analog_voltage;
float analog_distance_meters;
float slope = (SF01_3_3V_DISTANCE - SF01_0_0V_DISTANCE)/3.3;

//SoftwareSerial sf01_serial(9, 10);
 
Servo panServo;  // create servo object to control a servo 
Servo tiltServo;
 
int pan_pos;    // variable to store the servo position 
int tilt_pos;
int new_pos;

int val;

char command;
int i;
 
void setup() 
{ 
  panServo.attach(5);  // attaches the servo on pin 9 to the servo object 
  panServo.write(PAN_MIDDLE);
  
  tiltServo.attach(6);
  tiltServo.write(TILT_LEVEL);  
  
  pan_pos = panServo.read();
  tilt_pos = tiltServo.read();
  
  Serial.begin(9600);
  
  //sf01_serial.begin(115200);
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
      
      if((new_pos >= PAN_MAX_LEFT && new_pos <= PAN_MAX_RIGHT) || 
        (new_pos == LEFT && (pan_pos - 1) >= PAN_MAX_LEFT) || 
        (new_pos == RIGHT && (pan_pos + 1) <= PAN_MAX_RIGHT) ||
        (new_pos == 0) ) //return current position
      {
        #ifdef DEBUG
        Serial.print("Moving Pan Servo: ");
        Serial.print(new_pos);
        Serial.print(" -> ");
        Serial.println(pan_pos);
        #endif
        
        if (new_pos > pan_pos || new_pos == RIGHT)
        {
          if(new_pos == RIGHT)
            new_pos = pan_pos + 1;
          
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
        else if((new_pos < pan_pos && new_pos != 0) || new_pos == LEFT)
        {
          if(new_pos == LEFT)
            new_pos = pan_pos - 1;
            
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
        Serial.flush();
        Serial.println(new_pos);
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
      
      if((new_pos >= TILT_MAX_DOWN && new_pos <= TILT_LEVEL) || 
         (new_pos == UP && (tilt_pos + 1) <= TILT_LEVEL) || 
         (new_pos == DOWN && (tilt_pos - 1) >= TILT_MAX_DOWN) ||
         (new_pos == 0) )  //return current position
        {
          if (new_pos > tilt_pos || new_pos == UP)
          {
            if(new_pos == UP)
              new_pos = tilt_pos + 1;
              
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
          else if((new_pos < tilt_pos && new_pos != 0) || new_pos == DOWN)
          {
            if(new_pos == DOWN)
              new_pos = tilt_pos - 1;
              
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
          Serial.flush();
          Serial.println(new_pos);
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
      
      analog = 0;
      /*
      sf01_serial.write('d');
      while (!Serial.available()) {
        Serial.println("waiting...");
      }
      
      char c = Serial.read();
      
      Serial.println(c);
      
      for(i = 1; i <= 30; i++)
      {
        // Read the ADC value of the analog input pin
        val = analogRead(SF01_ANALOG);
        
        if(i >= 10) {
          
          if(i > 15 && (val < (analog/(i-10) - 3) || val > (analog/(i-10) + 3) )) {
            Serial.println("Bad value detected");
            delay(1000);
            val = analog/i;
          }
          
          analog += val; 
          
        }
        
        
        delay(150); //refresh time for laser is 125
      }
      
      */
      
      for(i = 1; i <= 20; i++)
      {
        // Read the ADC value of the analog input pin
        val = analogRead(SF01_ANALOG);
        analog += val;
        
        delay(150); //refresh time for laser is 125
      }
      
      //LPF the value
      analog = analog/20;
      
      // Convert this into a voltage 
      analog_voltage = analog * 0.0049;  
      
      //REMAP COMMAND??
      
      //Serial.println(analog);
      
      //analog_distance_meters = map(analog, 0, 1023, 0.0, 40.0);
      
      // Convert the voltage into a distance using the SF01 settings
      analog_distance_meters = analog_voltage*slope + SF01_0_0V_DISTANCE; 
      
      //test response
      Serial.flush();
      Serial.println(analog_distance_meters);
      
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

