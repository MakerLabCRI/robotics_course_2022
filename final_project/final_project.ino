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

