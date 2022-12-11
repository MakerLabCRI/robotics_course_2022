/*
 * Pathfinding Pololu Zumo Robot with Obstacle Detection
 *
 * by Clemence, Romaric & Tiffany 
 *
 * This code will find the shortest path from point A to B
 * in a 6x6 grid while avoiding obstacles placed on the grid.
 * 
 */

// importing libraries 
#include <Wire.h>
#include <ZumoShield.h>
#include <NewPing.h>

//defining motors speed and duration 
#define REVERSE_SPEED 200 
#define TURN_SPEED 200
#define FORWARD_SPEED 400
#define REVERSE_DURATION 500 
#define TURN_DURATION 500
#define FORWARD_DURATION 5000
#define STOP 0 
#define STOP_DURATION 100 

//setting up ultrasound sensor pins and max distance 
#define TRIGGER_PIN  13  
#define ECHO_PIN     12  
#define MAX_DISTANCE 200 

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

//setting up Zumo robot
ZumoBuzzer buzzer;
ZumoReflectanceSensorArray reflectanceSensors;
ZumoMotors motors;
Pushbutton button(ZUMO_BUTTON);
int lastError = 0;
  
/*************************************************/

void setup() {
  // for testing ultrasonic sensor:
Serial.begin(115200);
}

/*************************************************/

void loop() 
{
  //learning how ultrasonic sensor works
  delay(50);                      // pause 50ms between pings (about 20 pings/sec)
  unsigned int uS = sonar.ping(); // this int gets ping time in microseconds (uS) after sending
  Serial.print("Ping: ");
  Serial.print(uS / US_ROUNDTRIP_CM); // Convert ping time to distance in cm and print result (0 = outside set distance range)
  Serial.println("cm");

  // learning how motor setspeeds work with delay
  motors.setSpeeds(FORWARD_SPEED,FORWARD_SPEED);
  delay(FORWARD_DURATION);

  motors.setSpeeds(TURN_SPEED, -TURN_SPEED);
  delay(TURN_DURATION);

  motors.setSpeeds(FORWARD_SPEED,FORWARD_SPEED);
  delay(FORWARD_DURATION);

  motors.setSpeeds(TURN_SPEED, -TURN_SPEED);
  delay(TURN_DURATION);

  motors.setSpeeds(STOP, STOP);
  delay(STOP_DURATION);

  motors.setSpeeds(REVERSE_SPEED,REVERSE_SPEED);
  delay(REVERSE_DURATION);
}
