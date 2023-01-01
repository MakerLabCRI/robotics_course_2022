/*
 * Pathfinding Pololu Zumo Robot with Obstacle Detection
 *
 * by Clemence, Romaric & Tiffany 
 *
 * This code will find the shortest path from point A to B
 * in a 8x8 grid while avoiding obstacles placed on the grid.
 * 
 /*
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
#include <QueueArray.h>

//setting up ultrasound sensor pins and max distance 
#define TRIGGER_PIN  13  
#define ECHO_PIN     12  
#define MAX_DISTANCE 200 
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); 


/*Size of the maze pre defined*/
#define Row 8
#define Col 8

byte goalN; // goal position on grid

byte openList[3432]; // contains all the possible paths
byte closedList[3432]; // contains the path taken
byte curBotPos; // holds current bot position

struct Node
{
  byte g, h, f;
  byte parent;
  byte index;
  byte gridNom;
};

//setup the grid map
struct Grid
{
  Node Map[row][col];
} PF ;


byte H(byte curR, byte curC, byte goalS)  // manhattan distance 
{
 byte rowg, colg;
 byte manhattan=0;

   rowg = (byte)goalS/8;
   colg = goalS%8;
   manhattan += (abs(curR - rowg) + abs(curC - colg));
   
  return manhattan;
}


byte G(byte curR, byte curC)  // "depth" level of the tile
{
  byte gValue, parInd;
  byte rowg, colg;
  parInd = PF.Map[curR][curC].parent;
 
  rowg = (byte)parInd/8;
  colg = parInd%8;
  gValue = PF.Map[rowg][colg].g;
  
  return (gValue+1);
}

byte FV(byte curG, byte curH) // the "cost" of the path taken; adds H and G values for each tile
{
 byte fValue; 
  
  fValue = curG + curH;
  return fValue;
}


ZumoMotors motor_9(9); // initalizes the left motor
ZumoMotors motor_10(10); // initializes the right motor

void move(byte direction, byte speed) // sets up potential movements for the robot; 
{
      byte leftSpeed = 0;
      byte rightSpeed = 0;
      if(direction == 1){
          leftSpeed = speed;
          rightSpeed = speed;
      }else if(direction == 2){
          leftSpeed = -speed;
          rightSpeed = -speed;
      }else if(direction == 3){
          leftSpeed = -speed;
          rightSpeed = speed;
      }else if(direction == 4){
          leftSpeed = speed;
          rightSpeed = -speed;
      }
      motor_9.run((9)==M1?-(leftSpeed):(leftSpeed));
      motor_10.run((10)==M1?-(rightSpeed):(rightSpeed));
}
double angle_rad = PI/180.0;
double angle_deg = 180.0/PI;


void setup() {
  // put your setup code here, to run once:
Serial.begin(115200);
buildMap();
printGrid1();
printGrid2();
setGoal();
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(50);                      // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
  unsigned int uS = sonar.ping(); // Send ping, get ping time in microseconds (uS).
  Serial.print("Ping: ");
  Serial.print(uS / US_ROUNDTRIP_CM); // Convert ping time to distance in cm and print result (0 = outside set distance range)
  Serial.println("cm");

}
