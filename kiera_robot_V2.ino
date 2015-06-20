// kiera_robot_V2.ino

#include <Wire.h>
#include "utility/Adafruit_PWMServoDriver.h"
#include "Adafruit_MotorShield.h"

#define MAX_SPEED 150 // zet snelheid op 150 max is 255
#define MAX_SPEED_OFFSET 1 // variable tussen 2 motor opstart snelheden opvangen

int speedSet = 0;
int state = 0;
int S = 2;

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
// Select which 'port' M1, M2, M3 or M4. In this case, M1
Adafruit_DCMotor *motor1 = AFMS.getMotor(1);
// You can also make another motor on port M3
Adafruit_DCMotor *motor2 = AFMS.getMotor(3);


void setup() {
	Serial.begin(9600);  // set up Serial library at 9600 bps
	Serial.println("kiera_robot_V2s serial");
        AFMS.begin(); // create with the default frequency 1.6KHz

      } 


      void loop() { 
        if (Serial.available() > 0) {
          state = Serial.read();
          Serial.println(state);
          switch (state) {
            case 'U':
            vooruit();
            break;
            case 'D':
            achteruit();
            break;
            case 'C':
            stop();
            break;
            case 'L':
            links();
            break;
            case 'R':
            rechts();
            break;
            case 'a': // is in asci code 97
            rechts180();
            break; 
            case 100: // is kleine d 
            S = S + 10;
            if (S > 70) {
              S = 70;
            }
            break; 
            case 99: // is kleine c
            S = S - 10;
            break; 

          }
        }
      }

      void stop() {
        motor1->run(RELEASE); 
        motor2->run(RELEASE);
      }  

      void vooruit() {
        motor1->run(FORWARD);     
        motor2->run(FORWARD);      
        for (speedSet = 20; speedSet < MAX_SPEED; speedSet +=2)
        {
          motor1->setSpeed(speedSet + S);
          motor2->setSpeed(speedSet + MAX_SPEED_OFFSET + S);
        }
      }

      void achteruit() {
        motor1->run(BACKWARD);      
        motor2->run(BACKWARD);     
        for (speedSet = 20; speedSet < MAX_SPEED; speedSet +=2) 
        {
          motor1->setSpeed(speedSet);
          motor2->setSpeed(speedSet+MAX_SPEED_OFFSET);
        }
      }  

      void rechts() {
        motor1->run(FORWARD);      
        motor2->run(BACKWARD);     
        delay(160);
        stop();
      }  

      void rechts180() {
        motor1->run(FORWARD);      
        motor2->run(BACKWARD);     
        delay (1500); // eerst 780
        stop();
      }  

      void links() {
        motor1->run(BACKWARD);     
        motor2->run(FORWARD); 
        delay (160);
        stop(); 

      }

