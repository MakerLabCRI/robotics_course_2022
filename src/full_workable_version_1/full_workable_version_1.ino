//—--- Mari car
// Motor A
//int enA = 9;
//int in1 = 2;
//int in2 = 3;
 
// Motor B
////int enB = 10;
//int in3 = 4;
//int in4 = 5;
 
//Ultrasonic
//int trigPin = 12; // Trigger
//int echoPin = 11; // Echo
//long duration, cm;
 
//—--- Hala car
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
//---------------------HALA car-----------------------keep
 
int goal = 0;
 
// 0 is up
// 1 is right
// 2 is down
// 3 is left
int direction = 2;
//  the point in the grid where the robot is
//TODO: take variable from start_x, start_y
int i = 0;
int j = 0;
// we will have 2 matrix
//int path[8][8] =
//{
//  {    1,0,0,1,1,1,1,1    }  ,
//  {    1,1,0,1,1,1,1,1    }  ,
//  {    1,1,0,1,1,1,1,1    } ,
//  {    1,1,0,1,1,1,1,1    } ,
//  {    1,1,0,0,1,1,1,1    } ,
//  {    1,1,1,-1,1,1,1,1  } ,
//  {    1,1,1,1,1,1,1,1   } ,
//  {    1,1,1,1,1,1,1,1   }
//};
 
 
// path part start
#define OBST 99
#define beautiful_output 1 //beautiful output
//
////Test 1 normal 8 8
#define map_size_rows 8
#define map_size_cols 8
//
int ind[map_size_rows][map_size_cols] = {
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0}
};
 
int path[map_size_rows][map_size_cols] = {
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0}
};
 
//this is to see data during testing process
int test = 0;
int test_main = 0;
int test_main_path = 0;
int test_main_display = 0;
int test_arduino = 0; //for arduino functions to show
//int test_main_path_arduino = 1;
 
int start = 1; //start point
int start_x = 0; //vertical
int start_y = 0; //horisontal
 
int goal_target = -1; //TODO: FINALLY REWRITE FOR PATH
int goal_x = map_size_rows - 1;
int goal_y = map_size_cols - 1;
 
//int goal_x = 7; int goal_y = 1; //test left goal
int path_max_value = 0;
int calc_matrix_wave = 1; // 1 - calculated?
 
// CHANGE output for arduino
void pr(int value) {
//    printf("%2d",value);
   Serial.print(" ");
   Serial.print(value);
}
 
void pr_s(char value[]) {
//    printf(value);
   Serial.print(" ");
   Serial.print(value);
}
 
void ln(void){
//    printf("\n");
    Serial.println();
}
 
int update_matrix_with(int matrix[map_size_rows][map_size_cols], int x, int y, int new_value){
    //check if position exist
    if(x >= 0 && x <= map_size_rows && y >= 0 && y <= map_size_cols) {
        matrix[x][y] = new_value;
    }
    else {
        pr_s("Can't update, position doesn't exist");
        pr(x); pr_s(","); pr(y); ln();
    }
    return matrix[x][y];
}
 
void insert_obstcls(int ind[map_size_rows][map_size_cols], int obst){
    update_matrix_with(ind, 1, 1, OBST);
    update_matrix_with(ind, 1, 2, OBST);
}
 
void ind_first_line(void) {
    pr_s("..");
    for(int i = 0; i < map_size_cols; i++) {
        pr(i);
        pr_s(" ");
    }
    ln();
}
 
void show_matrix(int matrix[map_size_rows][map_size_cols]){
    if(beautiful_output) ind_first_line();
    for(int i = 0; i < map_size_rows; i++){
        if(beautiful_output) pr(i);
        for(int j = 0; j < map_size_cols; j++){
            pr(matrix[i][j]);
            pr_s(" ");
        } ln();
    } ln();
}
 
void show_matrix_revert(int matrix[map_size_rows][map_size_cols]){
    if(beautiful_output) {
        pr_s(".. ");
        for(int i = map_size_rows - 1; i >= 0; i--)
            pr(i);
        ln();
    }
    for(int i = map_size_rows - 1; i >= 0; i--) {
        if(beautiful_output) {
            pr(i);
            pr_s(":");
         }
        for(int j = map_size_rows - 1; j >= 0; j--) {
          pr(matrix[i][j]);
        }
        ln();
    } ln();
}
 
void replace_all(int matrix[map_size_rows][map_size_cols], int replace_what, int replace_with) {
    for(int i=0; i < map_size_rows; i++){
        for(int j=0; j < map_size_cols; j++){
            if(matrix[i][j] == replace_what) matrix[i][j] = replace_with;
        }
    }
}
 
int check_point_boundaries(int point_x, int point_y) {
    int result;
    if (point_x < map_size_rows && point_x >= 0 && point_y < map_size_cols && point_y >= 0) {
        result = 1; //true
    } else result = 0; //false
    return result;
}
 
int get_x(int index) {
    return (index - (index % map_size_cols)) / map_size_cols;
}
int get_y(int index) {
    return index % map_size_cols;
}
 
int get_index(int x, int y) {
    int index = x * map_size_cols + y;
    return index;
}
int check_point_values(int matrix[map_size_rows][map_size_cols], int point_x, int point_y) {
    int point_up_x = point_x; int point_up_y = point_y - 1;
    int point_left_x = point_x + 1; int point_left_y = point_y;
    int point_right_x = point_x - 1; int point_right_y = point_y;
    int point_down_x = point_x; int point_down_y = point_y + 1;
 
    //check for value not OBST
    int point = matrix[point_x][point_y];
    int point_up = matrix[point_up_x][point_up_y]; //up
    int point_left = matrix[point_left_x][point_left_y]; //left
    int point_right = matrix[point_right_x][point_right_y]; //right
    int point_down = matrix[point_down_x][point_down_y]; //down
 
    int not_checked_value = -4;
    int size_v = 4;
    static int checked_values[4];
    static int store_indexes[4];
 
    for(int i = 0; i < size_v; i++){
        checked_values[i] =  not_checked_value;
        store_indexes[i] = not_checked_value + 1;
    }
 
    if (check_point_boundaries(point_up_x, point_up_y) && point_up != OBST) {
        store_indexes[0] = get_index(point_up_x, point_up_y);
        checked_values[0] = point_up;
    }
    if (check_point_boundaries(point_left_x, point_left_y) && point_left != OBST) {
        store_indexes[1] = get_index(point_left_x, point_left_y);
        checked_values[1] = point_left;
    }
    if (check_point_boundaries(point_right_x, point_right_y) && point_right != OBST) {
        store_indexes[2] = get_index(point_right_x, point_right_y);
        checked_values[2] = point_right;
    }
    if (check_point_boundaries(point_down_x, point_down_y) && point_down != OBST) {
        store_indexes[3] = get_index(point_down_x, point_down_y);
        checked_values[3] = point_down;
    }
 
    int to_return = -5;
    int ind_up = 2; int ind_l = 0; int ind_r = 3; int ind_d = 1;
    //for testing - show up left right down variants
    if(test) {
        int value_show = 3;
 
        for(int i = 0; i < value_show; i++){
            for(int j = 0; j < value_show; j++){
                int to_print = 0;
                int to_print_index = -1;
 
                if(i == 0 && j == 1) {
                    to_print = checked_values[ind_up]; //up
                    to_print_index = store_indexes[ind_up];
                }
                if(i == 1 && j == 0) {
                    to_print = checked_values[ind_l]; //l
                    to_print_index = store_indexes[ind_l];
                }
                if(i == 1 && j == 1) {
                    to_print = point; //l
                    to_print_index = point_x * map_size_cols + point_y;
                }
                if(i == 1 && j == 2) {
                    to_print = checked_values[ind_r]; //r
                    to_print_index = store_indexes[ind_r];
                }
                if(i == 2 && j == 1) {
                    to_print = checked_values[ind_d]; //d
                }
                if(to_print) {
                    pr(to_print); pr_s("[");  pr(to_print_index); pr_s("] ");
                } else {
                    pr_s("   ");
                    pr_s(" "); pr_s("--"); pr_s("  ");
                }
            } ln();
        }
    }
 
    if(test) {
        pr(checked_values[ind_up]); pr_s(" ");pr(checked_values[ind_l]);pr_s(" "); pr(checked_values[ind_r]); pr_s(" ");pr(checked_values[ind_d]);
        pr_s(" Point_checked_values \n"); //ln();
    }
    if(test) {
        pr(store_indexes[ind_up]); pr_s(" ");pr(store_indexes[ind_l]);pr_s(" "); pr(store_indexes[ind_r]); pr_s(" ");pr(store_indexes[ind_d]);
        pr_s(" : val[Index]\n ");
    }
 
    if(test) pr_s("possible variant(s):\n");
    int minimum_value_index = -1;
    int minimum_value = 100;
    for(int i = 0; i < size_v; i++){
        int next_point = point - 1;
        if(checked_values[i] > 0 && store_indexes[i] >= 0 && checked_values[i] <= next_point  && checked_values[i] != OBST){
                int test_ind = store_indexes[i];
                int test_x = get_x(test_ind);
                int test_y = get_y(test_ind);
                if(checked_values[i] < minimum_value) {
                    minimum_value = checked_values[i];
                    minimum_value_index = store_indexes[i];
                }
            if(test) {
                pr(checked_values[i]); pr_s("["); pr(store_indexes[i]);  pr_s("]=");  //pr(i);
                pr(ind[test_x][test_y]);  pr_s("["); pr(test_x); pr_s(","); pr(test_y); pr_s("]");
                pr_s(",\n");
            }
            to_return = minimum_value_index; //TODO: when return which? if sroe_index[i] open - return and close = 1
        }
    }
    return to_return;
}
 
void calc_matrix_wave_func(void)  {
      ind[start_x][start_x] = start;
      insert_obstcls(ind, OBST);
 
    //fill matrix from 1 to N without obstcls
    int exit_flag = 0;
    int test_snake = 0; //0 - fill //1 - test off
 
    if(!test_snake){
      for(int i = start_x; i < map_size_rows; i++) {
          for(int j = start_y; j < map_size_cols; j++) {
              if(ind[i][j] != OBST) ind[i][j] = i + j + 1; //+start
              if(ind[i][j] > path_max_value) path_max_value = ind[i][j]; //goal target?
              if(i == goal_x && j == goal_y) {
                  exit_flag = 1;
                  break;
              }
          }
          if(exit_flag) break;
      }
    }
    pr_s("SHOW IND"); ln();
    show_matrix(ind);
 
    int filling_path_with = 1;
    int point_down = goal_x; int point_right = goal_y; //    int point_down = 7; int point_right = 3;
    if(test_main_path) {
      pr_s(" FROM {|x = "); pr(point_down);
      pr_s(",  -y ="); pr(point_right);
      pr_s("}");  ln();
    }
    int returned_index = check_point_values(ind, point_down, point_right); //return one index to go
    int next_x = get_x(returned_index);
    int next_y = get_y(returned_index);
 
    if(test_main_path) {
        pr_s("point "); pr(ind[point_down][point_right]);
    }
    if(test_main_path) {
        pr_s(" next |x:"); pr(next_x); pr_s(", -y:");pr(next_y);
    }
 
    int value = ind[next_x][next_y];
    if(test_main_path) {
        pr_s(" "); pr(value); pr_s("["); pr(returned_index);  pr_s("] !="); pr(start); ln();
    }
    int path_found = 1;
    int exit_path_not_found = map_size_rows * map_size_cols + 1;
    while(1){
        if (next_y == start_y && next_x == start_x) break;
        point_down = next_x; point_right = next_y; //get new position
        update_matrix_with(path, point_down, point_right, filling_path_with); //encoding path
        if(test) show_matrix(path);
        if(test_main) {
          pr_s("poit_down  = "); pr(point_down);
          pr_s(", point_right ="); pr(point_right); ln();
        }
        returned_index = check_point_values(ind, point_down, point_right); //return one index to go
         next_x = get_x(returned_index);
         next_y = get_y(returned_index);
        if(test_main_path) {
          pr_s(" point ");   pr(ind[point_down][point_right]);
        }
        if(test_main_path) {
            pr_s(" next x:");  pr(next_x);
          pr_s(", next y:"); pr(next_y);
        }
        value = ind[next_x][next_y];
        if(test_main_path) {
          pr_s(" "); pr(value);
          pr_s("["); pr(returned_index); pr_s("] !=");
          pr(start);
          ln();
        }
        exit_path_not_found--;
        if(exit_path_not_found == 0) {
            path_found = 0; //path not found
            break;
        }
    }
    point_down = next_x; point_right = next_y; //get new position
    update_matrix_with(path, point_down, point_right, filling_path_with); //encoding path
    if(test_main) {
      pr_s("poit_down  = "); pr(point_down);
      pr_s(", point_right ="); pr(point_right); ln();
    }
    returned_index = check_point_values(ind, point_down, point_right); //return one index to go
     next_x = get_x(returned_index);
     next_y = get_y(returned_index);
    if(test_main_path) {
      pr_s(" point ");   pr(ind[point_down][point_right]);
    }
    if(test_main_path) {
        pr_s(" next x:");  pr(next_x); pr_s(" != ");  pr(start_y);
        pr_s(", next y:"); pr(next_y); pr_s(" != ");  pr(start_x);
    }
    value = ind[next_x][next_y];
    if(test_main_path) {
      pr_s(" "); pr(value);
      pr_s("["); pr(returned_index); pr_s("] !=");
      pr(start);
      ln();
    }
 
    start = filling_path_with;
    update_matrix_with(path, start_x, start_y, start);
    update_matrix_with(path, goal_x, goal_y, goal_target); //for -1
//    update_matrix_with(path, goal_x, goal_y, filling_path_with); //for 0
 
    if(path_found) {
        //final encoding
        replace_all(path, 1, 2);
        replace_all(path, 0, 1);
        replace_all(path, 2, 0); //path 0
        pr_s("Path found\n");
//        show_matrix(path);
    } else {
        //TODO: path not found what todo? go around??)) dance
        pr_s("Path NOT found\n"); ln();
    }
    calc_matrix_wave = 0; //calculated the wave, got one path
} // path part finish
 
void setup() {
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
  turns on the motors to go forward and calculate the current indexes after moving.

  @param None.
  @return None.
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


/**
  turns on the motors to turn to the left and change the current direction after moving.

  @param None.
  @return None.
*/

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

/**
  turns on the motors to turn to the right and change the current direction after moving.

  @param None.
  @return None.
*/

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

/**
  turns off the motors for 2 secondes.

  @param None.
  @return None.
*/
void stopRobot() {
    if (test_arduino) pr_s("stop_robot"); ln();
    //Stop the motors
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
    delay(2000);
}

/**
  turns on the motors to turn 180 degree and change the current direction after moving.

  @param None.
  @return None.
*/
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
long calcDistance() {

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
/**
  calulate the J index of the obstecal.

  @param None.
  @return the value of J index .
*/
int returnIndexJ() {
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

/**
  calulate the i index of the obstecal.

  @param None.
  @return the value of i index .
*/
int returnIndexI() {
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
  test front of the robot due to the path matrix depending on the direction.

  @param None.
  @return the value of the matrix for the front.
*/
int testFront() {
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
  test the right of the robot due to the path matrix depending on the direction.

  @param None.
  @return the value of the matrix to the right.
*/
int testRight() {
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
  test the left of the robot due to the path matrix depending on the direction.

  @param None.
  @return the value of the matrix to the left.
*/
int testLeft() {
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
  @return 1 if the front of the robot is closed due to the grid and the value of the grid if the front is open(0 or -1).
*/
int frontOpen() {
    if (test_arduino) pr_s("frontOpen"); ln();
    int next = testFront();
    if (next == 0) {
        return next;
    }
    else if (next == -1) {
        goal = 1;
        return next;
    }

    else {
        return 1;
    }
}

/**
  test if the right is open to turn to it or not.

  @param None.
  @return True or False.
*/
boolean rightOpen() {
    if (test_arduino) pr_s("rightOpen"); ln();
    int next = testRight();
    if (next == 0 || next == -1) {
        return true;
    }
    else {
        return false;
    }
}

/**
  test if the left is open to turn to it or not.

  @param None.
  @return True or False.
*/
boolean leftOpen() {
    int next = testLeft();
    if (next == 0 || next == -1) {
        return true;
    }
    else {
        return false;
    }
}
void set_obstecal() {
  int y = (map_size_rows - 1) - returnIndexI();
  int x = (map_size_cols - 1) - returnIndexJ();
  pr_s("x=");pr(x);pr_s("y="); pr(y); ln();
  ind[y][x] = OBST;
  pr_s("!! = "); pr(ind[y][x]); ln();
//  update_matrix_with(ind, y, x, OBST);
  pr_s("New ind"); ln();
   show_matrix(ind);
}

void clean_path(){
  for(int i = 0; i < map_size_rows; i++){
        for(int j = 0; j < map_size_cols; j++){
            path[i][j] = 0;
            
        } 
    } 

}
 
void loop() {
  pr_s("HELLO");
  if(calc_matrix_wave) {
      calc_matrix_wave_func(); //return path
//      pr_s("PATH"); ln();
      show_matrix(path);
  }
  if (calcDistance() < 35) {
      calc_matrix_wave = 1; // we can recalc path
      stopRobot();
      clean_path();
//      set_obstecal();
 int y = (map_size_rows - 1) - return_indexI();
  int x = (map_size_cols - 1) - return_indexJ();
  pr_s("x=");pr(x);pr_s("y="); pr(y); ln();
  ind[y][x] = OBST;
  pr_s("!! = "); pr(ind[y][x]); ln();
//  update_matrix_with(ind, y, x, OBST);
  pr_s("New ind"); ln();
   show_matrix(ind);


//      pr_s("New ind"); ln();
//      show_matrix(ind);
      pr_s("-------New ind"); ln();
      
//      left();
//
//          if (rightOpen() == true) {
//          right();
//      }
//      else if (leftOpen() == true) {
//          left();
//      }
//      else {
//          turn180();
//  }
}
  else {
//      pr_s("PATH"); ln();
//      show_matrix(path);
      //delay(400);
      if (frontOpen() == 0 || frontOpen() == -1) {
          forward();
          stop_robot();
          //delay(1000);
          if (goal==1) {
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
 
 
 
