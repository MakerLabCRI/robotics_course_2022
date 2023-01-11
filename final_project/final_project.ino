/*
 * Pololu Zumo Robot with Obstacle Avoidance 
 *
 * by Clemence, Romaric & Tiffany 
 *
 * This robot will travel from start to goal in a 8x8 grid while
 * avoiding known obstacles placed on the grid.
 * 
 */
// import library
#include <ZumoShield.h>

//Zumo robot set-up
ZumoMotors motors;

//define constants
#define PATH_LEN 15
#define X 8
#define Y 8

//motor speeds and duration 
#define TURN_SPEED 275
#define FORWARD_SPEED 200
#define FORWARD_DURATION 1600 
#define TURN_LEFT_DURATION 250 
#define TURN_RIGHT_DURATION 246

//define 
char position;
//8x8 grid with obstacles = 1
int grid[X][Y]=	{
         {0,0,0,0,1,0,0,1},
				 {0,0,1,0,0,0,0,0},
				 {0,0,0,0,0,1,0,0},
				 {0,1,0,1,0,0,0,1},
				 {0,0,0,0,0,0,1,0},
				 {0,1,0,1,1,0,0,0},
         {0,0,0,0,0,0,0,0},
         {0,0,0,1,1,0,0,0},
         };

void setup() {
  // put your setup code here, to run once:
  position = 'n';
  Serial.begin(9600);
}

//robot path from start to goal
int path[PATH_LEN][2] = {
  {0,0},
  {0,1},
  {1,1},
  {1,2},
  {2,2},
  {2,3},
  {2,4},
  {3,4},
  {3,5},
  {4,5},
  {5,5},
  {6,5},
  {6,6},
  {6,7},
  {7,7}
};

/*
goPath,
This function moves the robot to the next location in the path.
inputs = currentX: x current location, currentY: y current location, nextX: next x location, nextY: next y location 
output = status of our followed path (3 for goal reached, 2 if obstacle detected, 1 for no direction 

*/
int goPath(int currentX,int currentY,int nextX,int nextY ){
    
    int returnValue = 1;

    Serial.print("(");
    Serial.print(currentX);
    Serial.print(",");
    Serial.print(currentY);
    Serial.print(")");
    Serial.print("-->");
 
    Serial.print("(");
    Serial.print(nextX);
    Serial.print(",");
    Serial.print(nextY);
    Serial.println(")");

    char direction = goNext(currentX, currentY, nextX, nextY);
    Serial.print("Direction: ");

    Serial.println(direction);

    if (direction == 'r'){
        turnRight();
        goForward();
    }
    else if (direction == 'l'){
        turnLeft();
        goForward();
    }

    else if (direction == 'f'){
        goForward();
    }
  return returnValue;

}

/*
goNext,
Depending on the current position, the robot moves to the next square on the grid.
input = x: x current, y: y current, w: x next, z: y next
output = f: front, b:back, l:left, r:right
*/
char goNext(int x,int y,int w,int z){

    if (x == w && y < z){
        if (position == 'n'){
        return 'f';
        }
    else if (position == 'o'){return 'r';}
    else if(position == 's'){return 'b';}
    else if(position == 'e'){return 'l';}
    }
    if (x == w && y > z){
        if (position == 'n'){
        return 'b';}
    else if (position == 'o'){return 'l';}
    else if(position == 's'){return 'f';}
    else if(position == 'e'){return 'r';}
    }
 if (x < w && y == z){
        if (position == 'n'){
        return 'l';}
    else if (position == 'o'){return 'f';}
    else if(position == 's'){return 'r';}
    else if(position == 'e'){return 'b';}
    }
    if (x > w && y == z){
        if (position == 'n'){
        return 'r';}
    else if (position == 'o'){return 'b';}
    else if(position == 's'){return 'l';}
    else if(position == 'e'){return 'f';}
    }
    if ((x == w && y == z) || (x !=w && y != z)){
        return 'e';
    }

}

//functions to move robot
//robot moves forward
void goForward(){
    motors.setSpeeds(FORWARD_SPEED, FORWARD_SPEED);
    delay(FORWARD_DURATION);
    stop();
}

//robot stops 
void stop(){
    motors.setSpeeds(0, 0);
    delay(1000);
}

//robot makes 90 degree left turn
void turnLeft(){
    motors.setSpeeds(-TURN_SPEED, TURN_SPEED);
    delay(TURN_LEFT_DURATION);
    if (position == 'n'){
    position = 'o';
    }
    else if (position == 'o'){position = 's';}
    else if(position == 's'){position = 'e';}
    else if(position == 'e'){position = 'n';}
    stop();
}

//robot makes 90 degree right turn
void turnRight(){
    motors.setSpeeds(TURN_SPEED, -TURN_SPEED);
    delay(TURN_RIGHT_DURATION);
    if (position == 'n'){
    position = 'e';
    }
    else if (position == 'e'){position = 's';}
    else if(position == 's'){position = 'o';}
    else if(position == 'o'){position = 'n';}
    stop();
}

int count = 0;

void loop() {
  // 
  if(count == 0){
    for(int i = 0; i < PATH_LEN -1 ; i++){
      int currentX =  path[i][0];
      int currentY = path[i][1];

      if(i == PATH_LEN -1){
        // goal reached
        break;
      }
      int nextX = path[i+1][0];
      int nextY = path[i+1][1];

      goPath(currentX, currentY, nextX, nextY);
      
    }
    //ends loop
    count++;
  }

}
