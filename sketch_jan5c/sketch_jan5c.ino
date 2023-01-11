#include <ZumoShield.h>

ZumoMotors motors;
int lastError = 0;

//defining motors speed and duration 
#define REVERSE_SPEED 200 
#define TURN_SPEED 100
#define FORWARD_SPEED 100
#define REVERSE_DURATION 500 
#define TURN_DURATION 600
#define FORWARD_DURATION 2000
#define STOP 0 
#define STOP_DURATION 100 

// variables for wavefront
int pathway = 0;
int obstacle = 255;
int goal = 1;
int robot = 244;

//starting robot/goal locations
int robot_x = 7;
int robot_y = 0;
int goal_x = 0;
int goal_y = 7;

// grid locations
int x=7;
int y=0;

//temporary variables
int counter=0;

//for looking for smallest node number
int minimum_node=250;
int min_node_location=1;
int reset_min=250;//

//defining grid for pathfinding 
/*
int grid[8][8]=	{
         {1,0,0,0,255,0,0,255},
				 {0,0,255,0,0,0,0,0},
				 {0,0,0,0,0,255,0,0},
				 {0,255,0,255,0,0,0,255},
				 {0,0,0,0,0,0,255,0},
				 {0,255,0,255,255,0,0,0},
         {0,0,0,0,0,0,0,0},
         {0,0,0,255,255,0,0,254},
         };

/********************functions*******************/

/*int propagate_wavefront(int robot_x, int robot_y, int goal_x, int goal_y)
	{
	//clear old wavefront
	unpropagate(robot_x, robot_y);
	
	counter=0;//reset the counter for each run!
    while(counter<50)//allows for recycling until robot is found
        {
        x=0;
        y=0;
    	while(x<8 && y<8)//while the grid hasnt been fully scanned
    		{
    		//if this location is a wall or the goal, just ignore it
    		if (grid[x][y] != obstacle && grid[x][y] != goal)
    			{	
    			//a full trail to the robot has been located, finished!
    			if (min_surrounding_node_value(x, y) < reset_min && grid[x][y]==robot)
    				{
    				//finshed! tell robot to start moving down path
    				return min_node_location;
    				}
    			//record a value in to this node
    			else if (minimum_node!=reset_min)//if this isnt here, 'nothing' will go in the location
    			    grid[x][y]= minimum_node + 1;
    			}
    		
    		//go to next node and/or row
    		y++;
    		if (y==6 && x!=6)
    			{
    			x++;
    			y=0;
    			}
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
			if (grid[x][y] != obstacle && grid[x][y] != goal) //if this location is something, just ignore it
				grid[x][y] = pathway;//clear that space
	
	//store robot location in grid
	grid[robot_x][robot_y]=robot;
	//store robot location in grid
	grid[goal_x][goal_y]=goal;
	}
  

//if no solution is found, delete all obstacles from grid
void clear_grid(void)
	{	
	for(x=0;x<6;x++)
		for(y=0;y<6;y++)
			if (grid[x][y] != robot && grid[x][y] != goal)
				grid[x][y]=pathway;
	}


//this function looks at a node and returns the lowest value around that node
//1 is up, 2 is right, 3 is down, and 4 is left (clockwise)
int min_surrounding_node_value(int x, int y)
	{
	minimum_node=reset_min;//reset minimum

	//down
	if(x < 7)//not out of boundary
		if  (grid[x+1][y] < minimum_node && grid[x+1][y] != pathway)//find the lowest number node, and exclude empty nodes (0's)
		    {
			minimum_node = grid[x+1][y];
			min_node_location=3;
            }

	//up
	if(x > 0)
		if  (grid[x-1][y] < minimum_node && grid[x-1][y] != pathway)
		    {
			minimum_node = grid[x-1][y];
			min_node_location=1;
            }
	
	//right
	if(y < 7)
		if  (grid[x][y+1] < minimum_node && grid[x][y+1] != pathway)
		    {
			minimum_node = grid[x][y+1];
			min_node_location=2;
            }
            
	//left
	if(y > 0)
		if  (grid[x][y-1] < minimum_node && grid[x][y-1] != pathway)
		    {
			minimum_node = grid[x][y-1];
			min_node_location=4;
            }

	   
	return minimum_node;
	}
*/


void move(int min_node_location) {
  if (min_node_location == 1){
      // move up
      motors.setSpeeds(FORWARD_SPEED, FORWARD_SPEED);
      delay(FORWARD_DURATION);
      motors.setSpeeds(STOP, STOP);
      delay(STOP_DURATION);
      robot_y--; 
    }
    else if (min_node_location == 2){
      // move right
      motors.setSpeeds(-TURN_SPEED, TURN_SPEED);
      delay(TURN_DURATION);
      motors.setSpeeds(FORWARD_SPEED, FORWARD_SPEED);
      delay(FORWARD_DURATION);
      motors.setSpeeds(STOP, STOP);
      delay(STOP_DURATION);
      robot_x++;
    }
    
    else if (min_node_location += 3){
      // move down
      motors.setSpeeds(-REVERSE_SPEED, -REVERSE_SPEED);
      delay(REVERSE_DURATION);
      motors.setSpeeds(STOP, STOP);
      delay(STOP_DURATION);
      robot_y++;
    }
    else if (min_node_location == 4)
    {
      // move left
      motors.setSpeeds(TURN_SPEED, -TURN_SPEED);
      delay(TURN_DURATION);
      motors.setSpeeds(FORWARD_SPEED, FORWARD_SPEED);
      delay(FORWARD_DURATION);
      motors.setSpeeds(STOP, STOP);
      delay(STOP_DURATION);
      x--;
    }
  }


void setup() {
  Serial.begin(19200);
  delay(5000);
  Serial.println("hi");
}

void loop() {
  //int path = propagate_wavefront(robot_x, robot_y, goal_x, goal_y);
  //unpropagate(robot_x, robot_y);
  if (min_node_location > 4){
    min_node_location = 1;
  }
  move(min_node_location);

  Serial.println('hiihi');
  min_node_location++;
  


}
