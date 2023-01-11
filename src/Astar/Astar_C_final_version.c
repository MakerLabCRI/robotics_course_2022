#include <stdio.h>
#include <stdlib.h>

//A* algorithm


//Creating a struct to store all proprieties the node has

typedef struct {
    int x; //position of x
    int y; //position of y
    double f;
    double g;
    double h;
}Node;

//Creating a list of structs to store the open list
typedef struct{
    Node info;
    struct List_node* next;
}List_node;

//Creating a linked list to add the first element of the list (start node)

List_node* Add(List_node *next_node, Node node, int start_x, int start_y, int end_x, int end_y) //this will return us a list
{
    List_node * new_node;
    new_node = (List_node*)malloc(sizeof(List_node));
    new_node->info=node;
    new_node->next=next_node;//the node's new value
}

// Creating the possible children the nodes can take
//This function returns the node that has the lowest f value checking for all the possible children the node can take
Node thebest(Node node, int start_x, int start_y, int end_x, int end_y)
{

        int pos= 1; //The robot can go just 1 position from the current cell
        int min = 1000; //This value is used to compare between the f values
        //int count =0;

        Node counter = node;
        Node nodeLeft;
        nodeLeft = node;

        //Calculating the position
        //The robot goes left
        int adding = node.x-pos; //calculates the next position
        nodeLeft.x=adding;
        nodeLeft.y=node.y;
        nodeLeft.g=abs(nodeLeft.x-start_x)+abs(nodeLeft.y-start_y);
        nodeLeft.h=abs(nodeLeft.x-end_x)+abs(nodeLeft.y-end_y);
        nodeLeft.f=nodeLeft.g+nodeLeft.h;
        if(nodeLeft.f < counter.f)
        {
            printf("left");
            min = nodeLeft.f;
            counter=nodeLeft;
            //count = 4;
        }
       //The robot goes up
        Node nodeUp;
        nodeUp = node;
        nodeUp.x=node.x;
        int adding2 = node.y+pos; //calculates the next position
        nodeUp.y=adding2;
        nodeUp.g=abs(nodeUp.x-start_x)+abs(nodeUp.y-start_y);
        nodeUp.h=abs(nodeUp.x-end_x)+abs(nodeUp.y-end_y);
        nodeUp.f=nodeUp.g+nodeUp.h;

       if(nodeUp.f < counter.f)
        {
            printf("up");
            min = nodeUp.f;
            counter=nodeUp;
            //count = 1;
        }
    //The robot goes right
        Node nodeRight;
        nodeRight = node;
        nodeRight.y = node.y;
        int adding3 = node.x+pos; //calculates the next position
        nodeRight.x=adding3;
        nodeRight.g=abs(nodeRight.x-start_x)+abs(nodeRight.y-start_y);
        nodeRight.h=abs(nodeRight.x-end_x)+abs(nodeRight.y-end_y);
        nodeRight.f=nodeRight.g+nodeRight.h;

        if(nodeRight.f < counter.f)
        {
            printf("right");
            min = nodeRight.f;
            counter=nodeRight;
            //count = 2;
        }
    //The robot goes down
        Node nodeDown;
        nodeDown = node;
        nodeDown.x = node.x;
        int adding4 = node.y-pos; //calculates the next position
        nodeDown.y=adding4;
        nodeDown.g=abs(nodeDown.x-start_x)+abs(nodeDown.y-start_y);
        nodeDown.h=abs(nodeDown.x-end_x)+abs(nodeDown.y-end_y);
        nodeDown.f=nodeDown.g+nodeDown.h;

        if(nodeDown.f < counter.f)
        {
            printf("down");
            min = nodeDown.f;
            counter=nodeDown;
            //count = 3;
        }
    return counter; //this functions returns the child with the lowest f

}

List_node *Addchildren(List_node* new_node, Node node, int start_x, int start_y, int end_x, int end_y )
{
    Node simple;
    List_node *thebest1=(List_node*)malloc(sizeof(List_node));
    simple=thebest(node, start_x, start_y, end_x, end_y);
    thebest1->info=simple;
    thebest1->next=new_node;

    if(thebest1->info.x != end_x && thebest1->info.y != end_y)
    {
        int path_found=1;
        thebest1->next=NULL;
    }
    else
        return thebest1->next=new_node;
}

void main()
{
    //Defining the start and end nodes
    int path_found =0;
    int start_x =0;
    int start_y=0;
    int end_y=5;
    int end_x=9;
    //Initializing startnode
    Node Startnode;
    Startnode.x = start_x;
    Startnode.y=start_y;
    Startnode.f=0;
    Startnode.g=0;
    Startnode.h=0;

    List_node *node=NULL;
    List_node *node2=NULL; //list initializing

   node = Add(node, Startnode, start_x, start_y, end_x, end_y);
   node2 = Addchildren(node, Startnode, start_x, start_y, end_x, end_y);

   int maze[8][8] =
            {{0, 0, 1, 0, 0, 0, 0, 0},
            { 0, 0, 1, 0, 0, 0, 0, 0},
            { 0, 0, 1, 0, 0, 0, 0, 0},
            { 0, 0, 1, 0, 0, 0, 0, 0},
            { 0, 0, 1, 0, 0, 0, 0, 0},
            { 0, 0, 0, 0, 0, 0, 0, 0},
            { 0, 0, 1, 0, 0, 0, 0, 0},
            {0, 0, 1, 0, 0, 0, 0, 0}};

    for(int i = 0; i < 8; i++)
        for(int j = 0; j < 8; j++) {

        List_node *iList = node2;
        Node current;
        if ((i == iList->info.x)&&(j==iList->info.y)){
            current.x=i;
            current.y=i;
            node2 = Addchildren(node, current, start_x, start_y, end_x, end_y);
        }

        while(iList!=0)
        {
        printf("%d ", iList->info.x);
        printf("%d ", iList->info.y);
        iList = iList ->next;
        }

    return 0;
}
}
