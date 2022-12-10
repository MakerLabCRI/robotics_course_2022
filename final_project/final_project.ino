/*
 * Pathfinding Pololu Zumo Robot with Obstacle Detection
 *
 * by Clemence, Romaric & Tiffany 
 *
 * This code will find the shortest path from point A to B
 * in a 6x6 grid while avoiding obstacles placed on the grid.
 * 
 */

// importing libraries 
#include <Wire.h>
#include <ZumoShield.h>
#include <NewPing.h>

//setting up ultrasound sensor pins and max distance 
#define TRIGGER_PIN  13  
#define ECHO_PIN     12  
#define MAX_DISTANCE 200 

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); 


void setup() {
  // put your setup code here, to run once:
Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(50);                      // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
  unsigned int uS = sonar.ping(); // Send ping, get ping time in microseconds (uS).
  Serial.print("Ping: ");
  Serial.print(uS / US_ROUNDTRIP_CM); // Convert ping time to distance in cm and print result (0 = outside set distance range)
  Serial.println("cm");

}
