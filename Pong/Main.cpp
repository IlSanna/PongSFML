#include "Ball.h"
#include "Bat.h"
#include <sstream>

//#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")//per evitare il pop up della console

int main() {
	//create a window
	int windowsWidth = 512;
	int windowsHeight = 384;

	sf::RenderWindow window(sf::VideoMode(windowsWidth, windowsHeight), "Pong",sf::Style::None);
	//instaciate game objects
	Ball ball(windowsWidth / 2, 1);
	Bat bat(windowsWidth/2, windowsHeight - 20);

	//dealing with the hud
	sf::Text text;
	sf::Font font;
	font.loadFromFile("ka1.ttf");
	text.setFont(font);
	text.setCharacterSize(32);
	text.setFillColor(sf::Color::White);

	int score = 0;
	int lives = 3;
	
	//main loop
	while (window.isOpen()) {
		//PLAYER INPUTS
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
		//COLLISION DETECTION
		//if the top position of the ball exceeds the windowsheight->the ball is going out
		if (ball.getPosition().top > windowsHeight) {
			ball.hitBottom();
			lives--;
			if (lives < 1) {//player loose,reset the game
				score = 0; lives = 3;
			}
		}
		//if the ball hit the top of the screen
		if (ball.getPosition().top < 0) {
			ball.reboundBatOrTop();
			score++;
		}
		//if the ball hits the sides of the screen, 10 is the ball size in ball.cpp
		if (ball.getPosition().left < 0 || ball.getPosition().left + 10> windowsWidth) {
			ball.reboundSides();
		}
		//if the ball intersects the bat
		if (ball.getPosition().intersects(bat.getPosition())) {
			ball.reboundBatOrTop();
		}
		//UPDATE THE OBJECTS POSITIONS
		ball.update();
		bat.update();
		//update hud
		std::stringstream ss;
		ss << "Score: " << score << "    Lives: " << lives;
		text.setString(ss.str());

		//LET'S HANDLE THE DRAWINGS
		window.clear(sf::Color::Black);//clear the previous frame
		window.draw(bat.getShape());//draw bat
		window.draw(ball.getShape());//draw ball
		window.draw(text);//draw text
		window.display();//show the result
	}//end of while loop

	return 0;
}