#pragma once
#include "MainMenuState.hpp"
#include "Application.hpp"
#include "Button.hpp"

class HightScoreState : public State
{
public:
	HightScoreState(sf::RenderWindow& window, std::stack<std::shared_ptr<State>>& states);
	~HightScoreState();

	void updateMousePosition();
	void updateButtons();
	void update(const sf::Time dt);
	void renderButtons(sf::RenderTarget& target);
	void draw();
	void handleEvent(const sf::Event& event);

	int j = 10;
	float hardTimes[15] = { 100000, 100000, 100000, 100000, 100000, 100000, 100000, 100000, 100000, 100000, 100000, 100000, 100000, 100000, 100000 };

private:
	sf::Sprite background;
	sf::Texture backText;
	sf::Font font;
	sf::Text logo;

	sf::Text score1;
	sf::Text score2;
	sf::Text score3;

	std::map<std::string, Button*> buttons;
	void initButtons();
	void fonts();

	sf::Vector2i mousePosScreen;
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;
};