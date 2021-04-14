#pragma once
#include "State.hpp"
#include "HardLevelState.hpp"
#include "Button.hpp"
#include "WinningState_single.hpp"
#include <iostream>
#include <sstream>
#include <string>

class GameState_easy : public State
{
public:
	GameState_easy(sf::RenderWindow& window, std::stack<std::shared_ptr<State>>& states);
	~GameState_easy();

	void updateMousePosition();
	void updateButtons();
	void updatePiorko();
	void updateBird();
	void updateRock(const sf::Time dt);
	void update(const sf::Time dt);
	void renderButtons(sf::RenderTarget& target);
	void draw();
	void handleEvent(const sf::Event& event);

private:
	float bird_vx = 5;
	float bird_vy = 2.5;
	float bird_x = 100;
	float bird_y = 100;

	float px = rand() % 400 + 200;
	float py = rand() % 400 + 200;

	int rx = 1000;
	int ry = window.getSize().y/2;

	int ptk = 0;

	clock_t start, end;

	sf::Time timeSinceLastUpdateSpecial;

	sf::Sprite bird;
	sf::Texture birdText;

	sf::Sprite piorko;
	sf::Texture piorkoText;

	sf::Sprite rock;
	sf::Texture rockText;

	sf::Sprite background;
	sf::Texture backText;
	sf::Font font;
	sf::Text logo;
	std::map<std::string, Button*> buttons;
	void initButtons();

	std::string punkt;
	sf::Text wynik;

	sf::Vector2i mousePosScreen;
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;
};