# Algorithm
## Path finding and A*

#### A* is a graph traversal and path search algorithm. Starting from a specific starting node of a graph, it aims to find apath to the given goal node having the smallest cost

We are going to take this grid as an example:

![image](https://user-images.githubusercontent.com/113441374/210691268-29917a55-1359-42c9-96c4-0a360b14ac95.png)


The grid has a start point, an end point and obstacles

- First, it checks for neighbours. Because our robot can move up,
down, right or left, it checks for the neighbour that has
smallest cost.

- The smallest cost, f is the sum of g and h, where:
    - g = the movement cost to move from the starting point to a given
square on the grid, following the path generated to get there
    - h = the estimated movement cost to move from that given square on the grid to
the final destination

- At each iteration, the f value is calculated

- It keeps track of the paths originating from the start node

- The algorithm is extending the paths one grid cell at a time until its termination criterion is satisfied, which is meeting the end node

## The steps involved in implementation of A*

- Specifying the start and end node

- Creating an open list to store all the nodes that can be taken into account when calculating the path

- Creating a closed list that stores all the nodes that have been visited

- We start with the start node and check its children (up, down, left and right)

- We check if the children are in the maze boundaries, if the identify as an obstacle, or if they were already visited. If they meet any of these requirements, then we skip to the next child and do not calculate the f value, nor assign it to the open list. Otherwise, we calculate the g and h cost that form the final f.

- We then check for the child with the lowest f and make this child the current node. We also append it to the closed list to form the path later

- The iteration continues until the current node will have the same x and y positions as the end node.

- The path will be returned taken into account the parents of the nodes. The path is calculated backwards, starting with the end point and tracing back the parents accordingly.

## Flowchart of A* algorithm

 ![image](https://user-images.githubusercontent.com/113441374/210694023-ff1081c1-a971-48b0-8659-01b11a468859.png)


## Movment

## Test the front 

![WhatsApp Image 2023-01-05 at 09 25 47](https://user-images.githubusercontent.com/113441374/210738497-08524a0e-cebb-4d09-93bc-6667d08010e6.jpg)

## frontOpen

![WhatsApp Image 2023-01-05 at 09 25 48](https://user-images.githubusercontent.com/113441374/210738582-f55d6433-0d8e-457a-8c01-411f206d52bc.jpg)

## Go Forward

![WhatsApp Image 2023-01-05 at 09 25 48](https://user-images.githubusercontent.com/113441374/210738674-e10dde17-e0c5-458c-9e5b-c02088b8faa9.jpg)

## Turn left

![WhatsApp Image 2023-01-05 at 09 25 47](https://user-images.githubusercontent.com/113441374/210738742-470fb530-3c18-4797-bcde-74f7c72a3066.jpg)


### General Algorithm of movment

![WhatsApp Image 2023-01-05 at 02 10 02](https://user-images.githubusercontent.com/113441374/210738268-da515aec-b926-45a1-8071-9e2a88f34c6f.jpg)
