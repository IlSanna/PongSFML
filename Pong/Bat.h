#pragma once
#include <SFML\Graphics.hpp>

class Bat{
private:
	//will hold horizontal and vertical pos
	sf::Vector2f position;
	//the actual bat that appears on screen
	sf::RectangleShape batShape;
	//number of pixel per frame that the bat can move at
	float batSpeed = 0.3f;
public:
	//constructor
	Bat(float startX, float startY);
	//the four which define a rectangle
	sf::FloatRect getPosition();
	//used to return the batshape to the main loop
	sf::RectangleShape getShape();
	void moveLeft();
	void moveRight();
	void update();
};