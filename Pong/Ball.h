#pragma once
#include <SFML\Graphics.hpp>

class Ball {
private:
	sf::Vector2f position;
	sf::RectangleShape ballShape;

	float xVelocity = 0.2f;
	float yVelocity = 0.2f;

public:
	Ball(float startX, float StartY);
	//the four which define a rectangle
	sf::FloatRect getPosition();
	//used to return the getShape to the main loop
	sf::RectangleShape getShape();
	//getter for the x velocity
	float getXVelocity();

	//What happens when the ball hits the side of the screen ?
	void reboundSides();
	//What happens when the ball hits the bat or the top of the screen ?
	void reboundBatOrTop();
	//What happens when the ball hits the bottom of the screen ?
	//we place the ball back at the top-middle of the screen!
	void hitBottom();
	void update();
};