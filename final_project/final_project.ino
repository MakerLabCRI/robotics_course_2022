/*
 * Pathfinding Pololu Zumo Robot with Obstacle Avoidance 
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

//setting up Zumo robot
ZumoBuzzer buzzer;
ZumoReflectanceSensorArray reflectanceSensors;
ZumoMotors motors;
Pushbutton button(ZUMO_BUTTON);
int lastError = 0;

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

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

//setting up time constants for avoiding obstacles
#define OBSTACLE_CHECK_INTERVAL 500 // check for obstacles every 500 ms
#define OBSTACLE_AVOID_DURATION 200 // avoid obstacles for 2 sec


// variables for wavefront
int pathway = 0;
int obstacle = 255;
int goal = 1;
int robot = 254;

//starting robot/goal locations
int robot_x = 0;
int robot_y = 0;
int goal_x = 4;
int goal_y = 4;

// grid locations
int x=0;
int y=0;

//temp variables
int counter=0;

//when searching for a node with a lower value
int minimum_node=250;
int min_node_location=0;
int reset_min=250;//anything above this number is a special item, ie a wall or robot

//defining grid for pathfinding 

int grid[8][8]=	{{0,0,0,0,0,0},
				 {0,0,0,0,0,0},
				 {0,255,0,0,0,0},
				 {0,0,0,255,0,0},
				 {0,0,0,0,1,0},
				 {0,0,0,0,0,0}};

/********************functions*************/

int propagate_wavefront(int robot_x, int robot_y, int goal_x, int goal_y)
{


  counter = 0; // Reset the counter for each run!
  while (counter < 50) // Allows for recycling until robot is found
  {
    // Measure distance to nearest obstacle
    unsigned int uS = sonar.ping();

    // If an obstacle is detected within the MAX_DISTANCE, set the value of the current cell to OBSTACLE
    if (uS != 0 && uS < MAX_DISTANCE)
    {
      grid[robot_x][robot_y] = obstacle;
    }
    // If this location is not the goal, update its value
    else if (grid[robot_x][robot_y] != goal)
    {
      grid[robot_x][robot_y] = grid[robot_x][robot_y] + 1;
    }

    // Check if the robot has reached the goal
    if (grid[robot_x][robot_y] < reset_min && grid[robot_x][robot_y] == goal)
    {
      // Finished! Tell robot to start moving down path
      return min_node_location;
    }

    // Go to the next node and/or row
    robot_y++;
    if (robot_y == 6 && robot_x != 6)
    {
      robot_x++;
      robot_y = 0;
    }
    counter++;
  }
  return 0;
}

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:
  // Propagate the wavefront from the start location
propagate_wavefront(robot_x, robot_y, goal_x,  goal_y);
  
  
  motors.setSpeeds(TURN_SPEED, -TURN_SPEED);
  delay(TURN_DURATION);

  motors.setSpeeds(STOP, STOP);
  delay(STOP_DURATION);

  motors.setSpeeds(REVERSE_SPEED,REVERSE_SPEED);
  delay(REVERSE_DURATION);

}
