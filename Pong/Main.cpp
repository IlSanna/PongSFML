#include "Ball.h"
#include "Bat.h"

//#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")//per evitare il pop up della console

int main() {
	//create a window
	int windowsWidth = 512;
	int windowsHeight = 384;

	sf::RenderWindow window(sf::VideoMode(windowsWidth, windowsHeight), "Pong");
	//instaciate game objects
	Ball ball(windowsWidth / 2, 1);
	Bat bat(windowsWidth/2, windowsHeight -20);

	//dealing with the hud
	sf::Text text;
	sf::Font font;
	font.loadFromFile("ka1.ttf");
	text.setFont(font);
	text.setCharacterSize(12);
	text.setFillColor(sf::Color::White);

	int score = 0;
	int lives = 3;
	
	//main loop
	while (window.isOpen()) {

		sf::Event event;
		//we check if any messages have been sent to the operating system
		//and subsequently passed on to SFML
		while (window.pollEvent(event)) {
			//if the event is that the the user close the window
			if (event.type == sf::Event::Closed) {
				window.close();//then we close the window
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			bat.moveLeft();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			bat.moveRight();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
			window.close();
		}
	}
}