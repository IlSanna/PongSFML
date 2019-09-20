#include "Bat.h"

// This the constructor and it is called when we create an object
Bat::Bat(float startX, float startY) {
	position.x = startX;
	position.y = startX;

	//creo una RectShape con setSize
	batShape.setSize(sf::Vector2f(50, 5));
	//setto la posizione di questa RectShape
	batShape.setPosition(position);
}
//returns the coordinates of the four corners of the rectangle shape
sf::FloatRect Bat::getPosition() {
	return batShape.getGlobalBounds();
}
//pass a copy of getShape, for drawing 
//when we code a public function with the only
//purpose of passing private date from a class is called
//getter function
sf::RectangleShape Bat::getShape()
{
	return batShape;
}
//subtract or add batSpeed from position
void Bat::moveLeft() {
	position.x -= batSpeed;
}
void Bat::moveRight() {
	position.x += batSpeed;
}
//called everyframe,set the batshape with the current value of position
void Bat::update() {
	batShape.setPosition(position);
}