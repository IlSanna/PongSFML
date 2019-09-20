#include "Ball.h"

Ball::Ball(float startX, float StartY){
	position.x = startX;
	position.y = StartY;

	ballShape.setSize(sf::Vector2f(10, 10));
	ballShape.setPosition(position);
}

sf::FloatRect Ball::getPosition(){
	return ballShape.getGlobalBounds();
}

sf::RectangleShape Ball::getShape(){
	return ballShape;
}

float Ball::getXVelocity(){
	return xVelocity;
}
/*the reboundSides function will be called every time the ball hits the sides of the screen.
  makes xVelocity the negative of whatever it currently is.
  So if it is positive (moving right) it will become negative and move left,
  and vice versa as well.*/
void Ball::reboundSides(){
	xVelocity = -xVelocity;
}
/*
alters the position.y value by the equivalent of 30 frames of 
movement and prevents the ball from getting stuck on the bat. 
Then reverses the direction of the ball.
*/
void Ball::reboundBatOrTop(){
	position.y -= (yVelocity * 30);
	yVelocity = -yVelocity;
}

void Ball::hitBottom(){
	position.y = 1;//placing the ball back at the top of the screen
	position.x = 500;//placing it around about the middle horizontally
}

void Ball::update(){
	//each frame is we update position by velocity
	position.x += xVelocity;
	position.y += yVelocity;
	//we update the rectshape with new values from position
	ballShape.setPosition(position);
}
