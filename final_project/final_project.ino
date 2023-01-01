/*
 * Pathfinding Pololu Zumo Robot with Obstacle Detection
 *
 * by Clemence, Romaric & Tiffany 
 *
 * This robot will find the shortest path from point A to B
 * in a 8x8 grid while avoiding obstacles placed on the grid.
 * 
 */

// importing libraries 
#include <Wire.h>
#include <ZumoShield.h>
#include <NewPing.h>

//defining motors speed and duration 
#define REVERSE_SPEED 200 
#define TURN_SPEED 200
#define FORWARD_SPEED 100
#define REVERSE_DURATION 500 
#define TURN_DURATION 500
#define FORWARD_DURATION 5000
#define STOP 0 
#define STOP_DURATION 100 

//setting up ultrasound sensor pins and max distance 
#define TRIGGER_PIN  12 
#define ECHO_PIN     11  
#define MAX_DISTANCE 200

//setting up time constants for avoiding obstacles
#define OBSTACLE_CHECK_INTERVAL 500 // check for obstacles every 500 ms
#define OBSTACLE_AVOID_DURATION 2000 // avoid obstacles for 2 sec

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

//setting up graph 
struct GridNode {
  int x;
  int y;
  std::vector<GridNode*> neighbors;
  int cost;
  bool isObstacle;
};

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


void loop(){
  static unsigned long lastObstacleCheck = 0;
  static boolean avoidingObstacle = false;

  // Check for obstacles every OBSTACLE_CHECK_INTERVAL milliseconds
  if (millis() - lastObstacleCheck >= OBSTACLE_CHECK_INTERVAL) {
    lastObstacleCheck = millis();

    // Measure distance to nearest obstacle
    unsigned int uS = sonar.ping();
    Serial.print(uS);

    // If an obstacle is detected and we're not already avoiding it, start avoiding it
    if (uS != 0 && uS < MAX_DISTANCE && !avoidingObstacle) {
      avoidingObstacle = true;
      motors.setSpeeds(-REVERSE_SPEED, -REVERSE_SPEED);
      delay(REVERSE_DURATION);
      motors.setSpeeds(STOP, STOP);
      delay(STOP_DURATION);

      // Choose a random direction to turn
      if (random(2) == 0) {
        motors.setSpeeds(-TURN_SPEED, TURN_SPEED);
      } else {
        motors.setSpeeds(TURN_SPEED, -TURN_SPEED);
      }

  }
  }
}
