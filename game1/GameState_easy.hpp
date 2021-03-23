#pragma once
#include "State.hpp"
#include "SettingsState.hpp"
#include "Button.hpp"

class GameState_easy : public State
{
public:
	GameState_easy(sf::RenderWindow& window, std::stack<std::shared_ptr<State>>& states);
	~GameState_easy();

	void updateMousePosition();
	void updateButtons();
	void update(const sf::Time dt);
	void renderButtons(sf::RenderTarget& target);
	void draw();
	void handleEvent(const sf::Event& event);

private:
	float bird_vx = 2;
	float bird_vy = 2;
	float bird_x = 100;
	float bird_y = 100;

	sf::Sprite bird;
	sf::Texture birdText;

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