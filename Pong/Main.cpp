#include "Ball.h"
#include "Bat.h"
#include <sstream>
#include <SFML\Audio.hpp>
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")//per evitare il pop up della console

void GameOver(sf::RenderWindow &window, sf::Text &text, int windowsWidth,int windowsHeight,int score,int lives) {
	text.setPosition((windowsWidth / 2) - 100, windowsHeight / 2 - 20);
	text.setString("YOU LOOSE\n\ny continue...");
	window.clear(sf::Color::Blue);
	window.draw(text);//pensare ad una function che loop throug an array and draw each element
	window.display();
	while (!sf::Keyboard::isKeyPressed(sf::Keyboard::Y)) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
			window.close();
			return;
		}
	};
	text.setPosition(0, 0);
	score = 0; lives = 3;
}
void SetupAudio(sf::SoundBuffer &normalBounceBuffer, sf::SoundBuffer &batBounceBuffer, sf::SoundBuffer &outBuffer,
	sf::Sound &normalBounceSound, sf::Sound &outSound, sf::Sound &batBounceSound) {
	normalBounceBuffer.loadFromFile("Audio/bounceNormal.ogg");
	batBounceBuffer.loadFromFile("Audio/bounce.ogg");
	outBuffer.loadFromFile("Audio/out.ogg");

	normalBounceSound.setBuffer(normalBounceBuffer);
	normalBounceSound.setVolume(50);
	outSound.setBuffer(outBuffer);
	outSound.setVolume(30);
	batBounceSound.setBuffer(batBounceBuffer);
}

int main() {
	//create a window
	int windowsWidth = 512;
	int windowsHeight = 384;

	sf::RenderWindow window(sf::VideoMode(windowsWidth, windowsHeight), "Pong",sf::Style::None);
	//instaciate game objects
	Ball ball(windowsWidth/2 , 1);
	Bat bat(windowsWidth/2, windowsHeight - 20);

	//dealing with the hud
	sf::Text text;
	sf::Font font;
	font.loadFromFile("ka1.ttf");
	text.setFont(font);
	text.setCharacterSize(28);
	text.setFillColor(sf::Color::White);
	//initial player values
	int score = 0;
	int lives = 3;

	//DEALING WITH AUDIO
	sf::SoundBuffer normalBounceBuffer;
	sf::SoundBuffer batBounceBuffer;
	sf::SoundBuffer outBuffer;
	sf::Sound normalBounceSound;
	sf::Sound batBounceSound;
	sf::Sound outSound;
	SetupAudio(normalBounceBuffer,batBounceBuffer,outBuffer,normalBounceSound,batBounceSound,outSound);

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
			outSound.play();
			lives--;
			if (lives < 1) {//player loose,reset the game
				GameOver(window, text, windowsWidth, windowsHeight,score,lives);
			}
		}
		//if the ball hit the top of the screen
		if (ball.getPosition().top < 0) {
			ball.reboundBatOrTop();
			normalBounceSound.play();
			score++;
		}
		//if the ball hits the sides of the screen, 10 is the ball size in ball.cpp
		if (ball.getPosition().left < 0 || ball.getPosition().left + 10> windowsWidth) {
			ball.reboundSides();
			normalBounceSound.play();
		}
		//if the ball intersects the bat
		if (ball.getPosition().intersects(bat.getPosition())) {
			ball.reboundBatOrTop();
			batBounceSound.play();
		}
		//if the bat reach the sides of the screen
		if (bat.getPosition().left < 0 ) {
			bat.moveRight();
		}
		if (bat.getPosition().left + 50 > windowsWidth) {
			bat.moveLeft();
		}
		//UPDATE THE OBJECTS POSITIONS
		ball.update();
		bat.update();
		//update hud
		std::stringstream ss;
		ss << "Score: " << score << "    Lives: " << lives;
		text.setString(ss.str());

		//LET'S HANDLE THE DRAWINGS 
		//TODO set the draw to be a loop
		window.clear(sf::Color::Blue);//clear the previous frame
		window.draw(bat.getShape());//draw bat
		window.draw(ball.getShape());//draw ball
		window.draw(text);//draw text
		window.display();//show the result
	}//end of while loop

	return 0;
}

