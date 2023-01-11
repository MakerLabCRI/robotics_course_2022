#include <stdio.h>

#define map_size_rows 8
#define map_size_cols 8
#define OBST 99
//beautiful output
#define beautiful_output 1

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

int update_matrix_with(int matrix[map_size_rows][map_size_cols], int x, int y, int new_value){
    //check if position exist
    if(x >=0 && x <= map_size_rows && y >= 0 && y <= map_size_cols)
        matrix[x][y] = new_value;
    else
        printf("Can't update, position doesn't exist\n");
    return matrix[x][y];
}

void insert_obstcl(int ind[map_size_rows][map_size_cols], int obst){
//    update_matrix_with(ind, 1, 1, OBST);
    update_matrix_with(ind, 3, 4, OBST);
}

void ind_first_line(void) {
    printf(".. ");
    for(int i = 0; i < map_size_rows; i++)
        printf(" %2d",i);
    printf("\n");
}

void show_matrix(int matrix[map_size_rows][map_size_cols]){
    if(beautiful_output) ind_first_line();
    for(int i=0; i < map_size_rows; i++){
        if(beautiful_output)  printf("%2d: ",i);
        for(int j=0; j < map_size_cols; j++){
                printf("%2d ",matrix[i][j]);
        }
        printf("\n");
    } printf("\n");
}

void show_matrix_revert(int matrix[map_size_rows][map_size_cols]){
    if(beautiful_output) {
        printf(".. ");
        for(int i = map_size_rows - 1; i >= 0; i--)
            printf(" %2d",i);
        printf("\n");
    }
    for(int i = map_size_rows - 1; i >= 0; i--) {
        if(beautiful_output)  printf("%2d: ",i);
        for(int j = map_size_rows - 1; j >= 0; j--) {
            printf("%2d ",matrix[i][j]);
        }
        printf("\n");
    } printf("\n");
}

void replace_all(int matrix[map_size_rows][map_size_cols], int replace_what, int replace_with) {
    for(int i=0; i < map_size_rows; i++){
        for(int j=0; j < map_size_cols; j++){
            if(matrix[i][j] == replace_what) matrix[i][j] = replace_with;
        }
    }
}

void pr(int value) {
    printf("%2d ", value);
}

int check_point_boundaries(int point_x, int point_y) {
    int result;
    if (point_x < map_size_rows && point_x >= 0 && point_y < map_size_cols && point_y >= 0) {
        result = 1; //true
    } else result = 0; //false
    return result;
}

int get_x(int index){
    return index % map_size_rows;
}

int get_y(int index){
    return (index - (index % map_size_rows)) / map_size_rows ;
}

int check_point_values(int matrix[map_size_rows][map_size_cols], int point_x, int point_y) {
    int test = 0; //beautiful output
    
    int point_up_x = point_x; int point_up_y = point_y + 1;
    int point_left_x = point_x - 1; int point_left_y = point_y;
    int point_right_x = point_x + 1; int point_right_y = point_y;
    int point_down_x = point_x; int point_down_y = point_y - 1;
    
    //check for value not OBST
    int point = matrix[point_x][point_y];
    int point_up = matrix[point_up_x][point_up_y]; //up
    int point_left = matrix[point_left_x][point_left_y]; //left
    int point_right = matrix[point_right_x][point_right_y]; //right
    int point_down = matrix[point_down_x][point_down_y]; //down
    
    int not_checked_value = -4;
    int checked_point_up = not_checked_value;
    int checked_point_left = not_checked_value;
    int checked_point_right = not_checked_value;
    int checked_point_down = not_checked_value;
    
    //check x,y in 4 directions for barrer boundaries
    if (check_point_boundaries(point_up_x, point_up_y) && point_up != OBST) checked_point_up = point_up;
    if (check_point_boundaries(point_left_x, point_left_y) && point_left != OBST) checked_point_left = point_left;
    if (check_point_boundaries(point_down_x, point_down_y) && point_right != OBST) checked_point_down = point_down;
    if (check_point_boundaries(point_right_x, point_right_y) && point_down != OBST) checked_point_right = point_right;
   
    int size_v = 4;
    static int checked_values[4];
    static int store_indexes[4];
    
    int filling_value = -3; //just to fill with something
    
    for(int i = 0; i < size_v; i++) {
        checked_values[i] = filling_value;
        store_indexes[i] = filling_value + 1;
    }
    
    int map_size = map_size_rows * map_size_cols;
    int test_sum = point_up_x * map_size_rows + point_up_y;
    if(test_sum < map_size) store_indexes[0] = test_sum;
    
    test_sum = point_left_x * map_size_rows + point_left_y;
    if(test_sum < map_size) store_indexes[1] = test_sum;
    
    test_sum = point_right_x * map_size_rows + point_right_y;
    if(test_sum < map_size) store_indexes[2] = test_sum;
    
    test_sum = point_down_x * map_size_rows + point_down_y;
    if(test_sum < map_size) store_indexes[3] = test_sum;
   
    if(test) printf("%2d %2d %2d %2d Point_checked_values\n", checked_point_up, checked_point_left, checked_point_right, checked_point_down);
    
    if(test) {
        for(int i=0; i < size_v; i++){
            int index = store_indexes[i];
            printf("%2d ", index);
        }
        printf(" :val[Index]\n ");
    }

    checked_values[0] = checked_point_up;
    checked_values[1] = checked_point_left;
    checked_values[2] = checked_point_right;
    checked_values[3] = checked_point_down;
    
    int to_return = -5;
    if(test) printf("possible variant(s):");
    for(int i = 0; i < size_v; i++){
        if(checked_values[i] > 0 && store_indexes[i] >= 0 && checked_values[i] < point && checked_values[i] != OBST){
                if(test) printf("%2d[%d]: %d, ", checked_values[i], store_indexes[i], i);
                to_return = store_indexes[i];
        }
    }
    if(test)printf("\n");
    return to_return;
}

int main() {
    int test_main_display = 1;
    int test_main_path = 1;
    int start = 1; //start point
    int start_x = 0; //vertical
    int start_y = 0; //horisontal
    ind[start_x][start_y] = start;
    
    int goal_target = -1;
    int goal_x = map_size_cols - 1; int goal_y = map_size_rows - 1;
//    int goal_x = 3; int goal_y = 7;
    
    ind[goal_x][goal_y] = goal_target;
    update_matrix_with(path, goal_x, goal_y, goal_target);
    
    insert_obstcl(ind, OBST);
    int path_max_value = 1;
    
    //fill matrix from 1 to goal
    for(int i = 0; i < map_size_rows; i++) {
        for(int j = 0; j < map_size_cols; j++) {
            //TODO: stop if we met goal
            //if(ind[i][j] != goal_target)
            if(ind[i][j] != OBST) ind[i][j] = i+j+1;
            if(ind[i][j] > path_max_value) path_max_value = ind[i][j];
        }
    }
    
    if(test_main_display) show_matrix(ind);
    
    //path finding
    /*
     from goal to start we can use any way...
     go and show x,y, number
     */
  
    int point_down = goal_x; int point_right = goal_y;
    
    if(test_main_path) printf(" FROM x horisontal = %d, vertical y = %d \n", point_down, point_right);
    
    int returned_index = check_point_values(ind, point_down, point_right); //return one index to go
    int next_x = get_x(returned_index);
    int next_y = get_y(returned_index);
    
    if(test_main_path) printf("point%2d,",ind[point_down][point_right]);
    if(test_main_path) printf(" next x:%d, y:%d ", next_x, next_y);
    int value = ind[next_x][next_y];
    if(test_main_path) printf("%2d[%d]\n", value, returned_index);

    int filling_path_with = 1;
//    for(int count = 0; count < 1; count++){
    while(value != start){
        point_down = next_y; point_right = next_x; //get new position
//        path[point_down][point_right] = filling_path_with;
        update_matrix_with(path, point_down, point_right, filling_path_with); //encoding path
//        if(test_main) printf(" poit_down  = %d, poit_down = %d \n", point_down, point_right);
        returned_index = check_point_values(ind, point_down, point_right); //return one index to go
         next_x = get_x(returned_index);
         next_y = get_y(returned_index);
        if(test_main_path) printf("point%2d,",ind[point_down][point_right]);
        if(test_main_path) printf(" next x:%d, y:%d ", next_x, next_y);
        value = ind[next_x][next_y];
        if(test_main_path) printf("%2d[%d]\n", value, returned_index);
    }
    
    return 0;
}
