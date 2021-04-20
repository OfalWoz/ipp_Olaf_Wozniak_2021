#pragma once
#include "MainMenuState.hpp"
#include "Application.hpp"
#include "Button.hpp"
#include "GameState_easy.hpp"
#include "GameState_normal.hpp"
#include "GameState_hard.hpp"

class WinningState_single : public State
{
public:
	WinningState_single(sf::RenderWindow& window, std::stack<std::shared_ptr<State>>& states, double roznica);
	~WinningState_single();

	void updateMousePosition();
	void updateButtons();
	void update(const sf::Time dt);
	void renderButtons(sf::RenderTarget& target);
	void draw();
	void handleEvent(const sf::Event& event);

	int hardLines = 5;
	int hardTimes[5];

private:
	sf::Sprite background;
	sf::Texture backText;
	sf::Font font;
	sf::Text logo;
	std::map<std::string, Button*> buttons;
	void initButtons();

	sf::Vector2i mousePosScreen;
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;
};