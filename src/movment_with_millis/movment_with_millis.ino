 
int enA = 9;
int in1 = 8;
int in2 = 7;
 
// Motor B
 
int enB = 3;
int in3 = 5;
int in4 = 4;
 
 
//Ultrasonic
int trigPin = 11; // Trigger
int echoPin = 10; // Echo
long duration, cm;
// 0 is up 
// 1 is right
// 2 is down
// 3 is left
int direction = 2;
//  the point in the grid where the robot is
 
int i = 2;
int j = 0;
 
int path[8][8] =
{
  { 1,0,0,1,1,1,1,1 }
  ,
  { 1,1,0,1,1,1,1,1 }
  ,
  { 1,1,0,1,1,1,1,1 }
  ,
  { 1,1,0,1,1,1,1,1 }
  ,
  { 1,1,0,0,1,1,1,1 }
  ,
  { 1,1,1,-1,1,1,1,1  }
};
 
unsigned long currentMillis = millis();
unsigned long previousMillis = 0;
bool goal = false;
 
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
 
  @param None.
  @return None.
*/
 
void forward() {
  currentMillis = millis();
  Serial.println(currentMillis);
  // Turn on motor B and A to go forward
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
 
  analogWrite(enB, 200);
  analogWrite(enA, 175);
 
  if (currentMillis - previousMillis >= 1800) {
 
      Serial.println("Forward");
      digitalWrite(in1, LOW);
      digitalWrite(in2, LOW);
      digitalWrite(in3, LOW);
      digitalWrite(in4, LOW);
 
      //Change the indexs on the path matrix after the robot move
      if (direction == 0)
          j = j - 1;
      if (direction == 1)
          i = i + 1;
      if (direction == 2)
          j = j + 1;
      if (direction == 3)
          i = i - 1;
 previousMillis = currentMillis;
       if (goal) {
              
              delay(100000);
          }
     
  }
}
 
/**
  turns on the motors to turn to the left.
 
  @param None.
  @return None.
*/
void left() {
  currentMillis = millis();
Serial.println(currentMillis);
  // Turn on motor B and A to turn to the left
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(enB, 200);
  analogWrite(enA, 175);
 
 
  if (currentMillis - previousMillis >= 500) {
 
  Serial.println("Left");
      digitalWrite(in1, LOW);
      digitalWrite(in2, LOW);
      digitalWrite(in3, LOW);
      digitalWrite(in4, LOW);
      // Change the direction of the robot after it turn left
      if (direction == 0)
          direction = 3;
      else if (direction == 1)
          direction = 0;
      else if (direction == 2)
          direction = 1;
      else if (direction == 3)
          direction = 2;
      previousMillis = currentMillis;
 
  }
}
/**
  turns on the motors to turn to the right.
 
  @param None.
  @return None.
*/
void right() {
  currentMillis = millis();
Serial.println(currentMillis);
  // Turn on motor B and A to turn to the right
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(enB, 200);
  analogWrite(enA, 175);
 
 
  if (currentMillis - previousMillis >= 500) {
    Serial.println("Right");
      digitalWrite(in1, LOW);
      digitalWrite(in2, LOW);
      digitalWrite(in3, LOW);
      digitalWrite(in4, LOW);
 
      if (direction == 0)
          direction = 1;
      else if (direction == 1)
          direction = 2;
      else if (direction == 2)
          direction = 3;
      else if (direction == 3)
          direction = 0;
      previousMillis = currentMillis;
  }
}
/**
  turns on the motors to turn 180 degree.
 
  @param None.
  @return None.
*/
void turn180() {
  currentMillis = millis();
  Serial.println("Around");
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
 
  if (currentMillis - previousMillis >= 1000) {
      digitalWrite(in1, LOW);
      digitalWrite(in2, LOW);
      digitalWrite(in3, LOW);
      digitalWrite(in4, LOW);
  if (direction == 0)
      direction = 2;
  else if (direction == 1)
      direction = 3;
  else if (direction == 2)
      direction = 0;
  else if (direction == 3)
      direction = 1;
  previousMillis = currentMillis;
  }
 
 
}
 
/**
  turns ofthe motors to stop.
 
  @param None.
  @return None.
*/
void stop_robot() {
  //Stop the motors
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  delay(2000);
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
  cm = (duration / 2) / 29.1;   // Divide by 29.1 or multiply by 0.0343
 
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
  // delay(250);
 
  return cm;
}
 
 
 
/**
  test front of the robot due to the path matrix depending on the direction.
 
  @param None.
  @return the value of the matrix for the front.
*/
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
 
/**
  test right of the robot due to the path matrix depending on the direction.
 
  @param None.
  @return the value of the matrix for the right.
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
  test left of the robot due to the path matrix depending on the direction.
 
  @param None.
  @return the value of the matrix for the left.
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
  return the value of the matrix so we can now if we can go oe not.
 
  @param None.
  @return 1 if the front of the robot is closed due to the grid and the value of the grid if the front is open(0 or -1)
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
  test if the right is open to turn to it or not
 
  @param None.
  @return return True or False.
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
  test if the left if is open to turn to it or not
 
  @param None.
  @return return True or False.
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
  path[i][j] = 1;
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
             turn180();}
  //recalc path----------------------------------------------
  }
  else {
 
      if (frontOpen() == 0 || frontOpen() == -1) {
          forward();
 
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
 
 
 
 
