<b>Update 10 January 2023:</b>
Defined an array of coordinates that make up the path of the robot. As the program iterates through the array of coordinates with position information (robot is facing north, south, east, or west), the Zumo robot moves accordingly forward, left or right. 

--------------------------------------------------------------------------------------------------------
tried to implement dijkstra, but difficult to put together code with our basic C++ skill level. 

Changed tactic to use wavefront algorithm in pathplanning

Using wavefront:
- defined array 8x8, obstacle value = 255, goal value = 1, path = 0, robot location = 254
- defined start, goal, and robot locations
- if, using ultrasound sensor, sent pings to detect obstacles. if distance is less than a maximum distance of 200cm, an obstacle is recognized
- else if, not an obstacle and not the goal, add +1 to the value on the array 
- continue to loop until goal is found 
- if, goal, return the minimum path to goal for robot to travel. 