/*
 * Pathfinding Pololu Zumo Robot with Obstacle Avoidance 
 *
 * by Clemence, Romaric & Tiffany 
 *
 * This robot will find the shortest path from point A to B
 * in a 8x8 grid while avoiding known obstacles placed on the grid.
 * 
 */

maze format
7 _ _ _ _ _ _ _ _
6 _ _ _ _ _ _ _ _
5 _ _ _ _ _ _ _ _
4 _ _ _ _ _ _ _ _
3 _ _ _ _ _ _ _ _
2 _ _ _ _ _ _ _ _
1 _ _ _ _ _ _ _ _
0 _ _ _ _ _ _ _ _
  0 1 2 3 4 5 6 7
start=0-0;
arrival=7-7;
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

//temporary variables
int counter=0;

//for looking for smallest node number
int minimum_node=250;
int min_node_location=0;
int reset_min=250;//

//defining grid for pathfinding 

int grid[8][8]=	{{0,0,0,0,0,0,0,0},
				 {0,0,0,0,0,0,0,0},
				 {0,255,0,0,0,0,0,0},
				 {0,0,0,255,0,0,0,0},
				 {0,0,0,0,1,0,0,0},
				 {0,0,0,0,0,0,0,0}};

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
      grid[robot_x][robot_y] = min_surrounding_node_value + 1;
    }

    // Check if the robot has reached the goal
    if (grid[robot_x][robot_y] < reset_min && min_surrounding_node_value == goal)
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

void unpropagate(int robot_x, int robot_y)//clears old path to determine new path
	{
	//stay within boundary
	for(x=0; x<6; x++)
		for(y=0; y<6; y++)
			if (map[x][y] != wall && map[x][y] != goal) //if this location is something, just ignore it
				map[x][y] = nothing;//clear that space
	
	//store robot location in map
	map[robot_x][robot_y]=robot;
	//store robot location in map
	map[goal_x][goal_y]=goal;
	}

//if no solution is found, delete all walls from map
void clear_map(void)
	{	
	for(x=0;x<6;x++)
		for(y=0;y<6;y++)
			if (map[x][y] != robot && map[x][y] != goal)
				map[x][y]=nothing;
	}


//this function looks at a node and returns the lowest value around that node
//1 is up, 2 is right, 3 is down, and 4 is left (clockwise)
int min_surrounding_node_value(int x, int y)
	{
	minimum_node=reset_min;//reset minimum

	//down
	if(x < 5)//not out of boundary
		if  (map[x+1][y] < minimum_node && map[x+1][y] != pathway)//find the lowest number node, and exclude empty nodes (0's)
		    {
			minimum_node = map[x+1][y];
			min_node_location=3;
            }

	//up
	if(x > 0)
		if  (map[x-1][y] < minimum_node && map[x-1][y] != pathway)
		    {
			minimum_node = map[x-1][y];
			min_node_location=1;
            }
	
	//right
	if(y < 5)
		if  (map[x][y+1] < minimum_node && map[x][y+1] != pathway)
		    {
			minimum_node = map[x][y+1];
			min_node_location=2;
            }
            
	//left
	if(y > 0)
		if  (map[x][y-1] < minimum_node && map[x][y-1] != pathway)
		    {
			minimum_node = map[x][y-1];
			min_node_location=4;
            }
	   
	return minimum_node;
	}


void setup() {
  // put your setup code here, to run once:
}

void loop() {
  // put your main code here, to run repeatedly:
  // Propagate the wavefront from the start location
  int next_direction = propagate_wavefront(robot_x, robot_y, goal_x,  goal_y);
  // move the robot in the appropriate direction

    if (next_direction == 1) {
    //move the robot up
     motors.setSpeeds(FORWARD_SPEED, FORWARD_SPEED);
     delay(FORWARD_DURATION);
   } 

   else if (next_direction == 2) {
    // move the robot right
    motors.setSpeeds(TURN_SPEED, -TURN_SPEED);
    delay(TURN DURATION);
  } 
  else if (next_direction == 3) {
    // move the robot down
    motors.setSpeeds(REVERSE_SPEED,REVERSE_SPEED);
    delay(REVERSE_DURATION);
  } 
  else if (next_direction == 4) {
    // move the robot left
    motors.setSpeeds(-TURN_SPEED, TURN_SPEED);
    delay(TURN DURATION);
  }

}
