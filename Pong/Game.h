#pragma once
#include <sstream>
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>

class Game {
public:
	Game() {}
	~Game() {}
	// simply set the running variable to true
	void init() { m_bRunning = true; }
	void render() {}
	void update() {}
	void handleEvents() {}
	void clean() {}
	// a function to access the private running variable
	bool running() { return m_bRunning; }
private:
	bool m_bRunning;
};