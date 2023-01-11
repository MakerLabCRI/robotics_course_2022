
int enA = 9;
int in1 = 8;
int in2 = 7;
 
// Motor B
 
int enB = 3;
int in3 = 5;
int in4 = 4;

//Ultrasonic
int trigPin = 11;  // Trigger
int echoPin = 10; // Echo
long duration, cm;


bool goal = false;

// 0 is up
// 1 is right
// 2 is down
// 3 is left
int direction = 2;


int i = 2;
int j = 0;

int path[8][8] =
{
  {    1,0,0,1,1,1,1,1    }  ,
  {    1,1,0,1,1,1,1,1    }  ,
  {    1,1,0,1,1,1,1,1    } ,
  {    1,1,0,1,1,1,1,1    } ,
  {    1,1,0,0,1,1,1,1    } ,
  {    1,1,1,-1,1,1,1,1  } ,
  {    1,1,1,1,1,1,1,1   } ,
  {    1,1,1,1,1,1,1,1   }
};

void setup()

{
  //Ulterasonic
  //Serial Port begin
  Serial.begin(9600);
  //Define inputs and outputs pins for ultrasonic
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Set all the motor control pins to outputs

  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

}

/**
  turns on the motors to go forward.

  @param colorCode color code to convert.
  @return the numerical value of the color code.
*/

void forward() {

  // Turn on motor B and A to go forward
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);

  // Set the  speed value out of possible range 0~255
  analogWrite(enB, 200);
  analogWrite(enA, 182);
  delay(1800);

  Serial.println("Forward");

  //Change the indexs on the path matrix after the robot move
  if (direction == 0)
      j = j - 1;
  if (direction == 1)
      i = i + 1;
  if (direction == 2)
      j = j + 1;
  if (direction == 3)
      i = i - 1;
}



void left() {

  // Turn on motor B and A to turn to the left
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);

  delay(170);
  Serial.println("Left");

  // Change the direction of the robot after it turn left
  if (direction == 0)
      direction = 3;
  else if (direction == 1)
      direction = 0;
  else if (direction == 2)
      direction = 1;
  else if (direction == 3)
      direction = 2;

}


void right() {

  // Turn on motor B and A to turn to the right
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  //analogWrite(enB, 200);
   // analogWrite(enA, 200);
  delay(200);
  Serial.println("Right");

  if (direction == 0)
      direction = 1;
  else if (direction == 1)
      direction = 2;
  else if (direction == 2)
      direction = 3;
  else if (direction == 3)
      direction = 0;
}

void stop_robot() {
  //Stop the motors
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  delay(2000);
}


void turn180() {

  Serial.println("Around");
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(enB, 200);
  analogWrite(enA, 175);
  delay(500);
  if (direction == 0)
      direction = 2;
  else if (direction == 1)
      direction = 3;
  else if (direction == 2)
      direction = 0;
  else if (direction == 3)
      direction = 1;


}
/**
  Calculate the distance in the front of the robot.

  @param None.
  @return a the distance in cm.
*/
long calcDistance() {/////most change the comments---------------------------------

  // The sensor is triggered by a HIGH pulse of 10 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read the signal from the sensor: a HIGH pulse whose
  // duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);

  // Convert the time into a distance
  cm = (duration / 2) / 29.1;     // Divide by 29.1 or multiply by 0.0343

  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
   delay(300);

  return cm;
}


int test_front() {
  if (direction == 0) {
      return path[j - 1][i];
  }
  if (direction == 1) {
      return path[j][i + 1];
  }
  if (direction == 2) {
      return path[j + 1][i];
  }
  if (direction == 3) {
      return path[j][i - 1];
  }
}
int return_indexJ() {
  if (direction == 0) {
      return j - 1;
  }
  if (direction == 1 || direction == 3) {
      return j;
  }
  if (direction == 2) {
      return j + 1;
  }
    
}
int return_indexI() {
  if (direction == 0 || direction == 2) {
      return i;
  }
  if (direction == 1) {
      return i + 1;
  }
   
  if (direction == 3) {
      return i - 1;
  }
}



/**
  Gets the number on the Grid of the space to the Right of it.

  @param None.
  @return the vlaue of the grid.
*/
int test_right() {
  if (direction == 0) {
      return path[j][i + 1];
  }
  if (direction == 1) {
      return path[j + 1][i];
  }
  if (direction == 2) {
      return path[j][i - 1];
  }
  if (direction == 3) {
      return path[j - 1][i];
  }
}



/**
  Gets the number on the Grid of the Space to the Left of it.

  @param None.
  @return the vlaue of the grid.
*/
int test_left() {
  if (direction == 0) {
      return path[j][i - 1];
  }
  if (direction == 1) {
      return path[j - 1][i];
  }
  if (direction == 2) {
      return path[j][i + 1];
  }
  if (direction == 3) {
      return path[j + 1][i];
  }
}


/**
  Gets the number on the Grid of the Space to the Left of it.

  @param None.
  @return 1 if the front of the robot is closed due to the grid and the vaue of the grid if the front is open.
*/
int frontOpen() {
  int next = test_front();
  if (next == 0) {
      return next;
  }
  else if (next == -1) {
      goal = true;
      return next;
  }

  else {
      return 1;
  }
}

/**
  Gets the number on the Grid of the Space to the Left of it.

  @param None.
  @return True if the right of the robot is Open (free) due to the grid and False if it is closed.
*/
boolean rightOpen() {
  int next = test_right();
  if (next == 0 || next == -1) {
      return true;
  }
  else {
      return false;
  }
}

/**
  Gets the number on the Grid of the Space to the Left of it.

  @param None.
  @return True if the left of the robot is Open (free) due to the grid and False if it is closed.
*/
boolean leftOpen() {
  int next = test_left();
  if (next == 0 || next == -1) {
      return true;
  }
  else {
      return false;
  }
}

void set_obstecal() {
  int y= return_indexI();
  int x=return_indexJ();
  //recalc
}


void loop() {

  if (calcDistance() < 35) {
      stop_robot();
      set_obstecal();
      if (rightOpen() == true) {
          right();
      }
      else if (leftOpen() == true) {
          left();
      }
      else {
          turn180();

      }
  //recalc path----------------------------------------------
  }
  else {
      //delay(400);
      if (frontOpen() == 0 || frontOpen() == -1) {
          forward();
          stop_robot();
          //delay(1000);
          if (goal==true) {
              stop_robot();
              delay(100000);
          }
      }
      else if (rightOpen() == true) {
          right();
      }
      else if (leftOpen() == true) {
          left();
      }
      else {
          turn180();

      }
  }
}
