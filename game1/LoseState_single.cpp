#include "LoseState_single.hpp"

LoseState_single::LoseState_single(sf::RenderWindow& window, std::stack<std::shared_ptr<State>>& states) : State(window, states)
{
	initButtons();
	font.loadFromFile("fonts/arial.ttf");
	if (!backText.loadFromFile("textures/back.png"))
	{
		std::cout << "ERROR::LOADING BACKGROUND TEXTURES\n";
	}
	sf::Vector2f back = (sf::Vector2f)backText.getSize();
	background.setScale(sf::Vector2f(window.getSize().x / back.x, window.getSize().y / back.y));
	background.setTexture(backText);

	logo.setFont(font);
	logo.setString("Game Over");
	logo.setCharacterSize(50);
	logo.setPosition((window.getSize().x / 2) - 50, 20);
}

LoseState_single::~LoseState_single()
{
}

void LoseState_single::updateMousePosition()
{
}

void LoseState_single::updateButtons()
{
}

void LoseState_single::update(const sf::Time dt)
{
}

void LoseState_single::renderButtons(sf::RenderTarget& target)
{
}

void LoseState_single::draw()
{
	window.draw(background);
	window.draw(logo);
	renderButtons(window);
}

void LoseState_single::handleEvent(const sf::Event& event)
{
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
	{
		states.push(std::shared_ptr<State>(new MainMenuState(window, states)));
	}
}

void LoseState_single::initButtons()
{
}
