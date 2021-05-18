#pragma once
#include "MainMenuState.hpp"
#include "Application.hpp"
#include "Button.hpp"
#include "GameState_easy.hpp"
#include "GameState_normal.hpp"
#include "GameState_hard.hpp"

class WinningState_multi : public State
{
public:
	WinningState_multi(sf::RenderWindow& window, std::stack<std::shared_ptr<State>>& states, int who);
	~WinningState_multi();

	void updateMousePosition();
	void updateButtons();
	void update(const sf::Time dt);
	void renderButtons(sf::RenderTarget& target);
	void draw();
	void handleEvent(const sf::Event& event);

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

