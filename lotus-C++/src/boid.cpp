#include "boid.h"

/* A Boid has a settable location and colour, along with a 
   reference to a Mouser (user's mouse). 
 
  See boid.h for a Boid's private properties. */

void Boid::setup(float x, float y, ofColor color, Ball &ball) {
	location.set(x, y);
	this->color = color;
	this->ball = &ball;
}

/* Update a Boid's location through this process:

	 - Seek: Calculate Acceleration Required To Follow Mouse Pointer
	 - Accelerate: Apply Acceleration to Current Velocity
	 - Move: Apply Velocity to Current Location
*/

void Boid::update() {
	// Seek! Calculate desired acceleration using seeking behaviour.
	acceleration = seek(ball->getLocation());

	// Accelerate! Apply the acceleration to the Boid's velocity.
	velocity += acceleration; 	
	
	// Limit Boid to a maximum speed.
	velocity.limit(MAX_SPEED); 
	
	// Move! 
	location += velocity; 	
}

/* Boids seek a target location by moving while correcting for speed and angle.

   Seeking force calculation:

   - Full speed towards the target (desired velocity)
   - Correct for current velocity. (desired velocity - current velocity)
   - Slow down your approach as you get close. (max speed scaled to distance)

*/

ofVec2f Boid::seek(ofVec2f targetLocation) {
	// Delta between target location and current location
	ofVec2f desireLine = targetLocation - location;

	// The length of the distance to cover.
	float distanceToCover = desireLine.length();
	
	// Starting from a max, scale down the boid's speed, as we approach target.
	float approachSpeed = MAX_SPEED;
	if (distanceToCover < SLOW_APPROACH_RADIUS) {
		approachSpeed *= distanceToCover / SLOW_APPROACH_RADIUS;
	}

	// Boid desires to move at full speed towards the target location.
	ofVec2f steeringUnitVector = desireLine.normalize();
	ofVec2f fullSpeedTowardsTarget = steeringUnitVector * approachSpeed;

	// What's the difference between full speed towards target and boid's current velocity?
	ofVec2f velocityCorrectedSteeringForce = fullSpeedTowardsTarget - velocity;

	// Limt steering force to a maximum.
	velocityCorrectedSteeringForce.limit(MAX_FORCE);

	// accelerate according to the steering force.
	return velocityCorrectedSteeringForce;
}

/* Draw the Boid as a circle with line nose: O-
   
   The length of a Boid's nose scales to its speed.

   The DRAW_RADIUS and DRAW_STROKE constants are set in the boid.h file.

   A Boid's color is set using setup().
*/

void Boid::draw() {
	// Length of boid's nose depends on radius and current velocity.
	float noseLength = DRAW_RADIUS * 1.1 + 3 * velocity.length();

	ofPushMatrix();	                                 // Save the global coordinates
	
	ofTranslate(location.x, location.y);             // Translate coords to the boid's position
	ofRotateZDeg(headingInDegrees());                // Rotate coordinate system to its heading

	ofSetLineWidth(DRAW_STROKE);                     // Set stroke witdh for lines
	ofSetColor(ofColor::black);                      // Stroke is black
	ofDrawCircle(0, 0, DRAW_RADIUS + DRAW_STROKE);   // Draw the "body" stroke
	ofSetColor(color);                               // Fill is this->color
	ofDrawCircle(0, 0, DRAW_RADIUS);                 // Draw the "body" fill
	ofSetColor(ofColor::black);                      // Stroke is black 
	ofDrawLine(0, 0, noseLength, 0);                 // Draw the "nose" stroke
	
	ofPopMatrix();                                   // Pop the saved global coordinates
}

/* Public Getter - Boid's Location */

ofVec2f Boid::getLocation() {
	return location;
}

/* Private Helper - Boid's Heading in Degrees */

float Boid::headingInDegrees() {
	// The angle between the xAxis and the boid's velocity is:	
	ofVec2f xAxis(1, 0);
	return xAxis.angle(velocity);
}


