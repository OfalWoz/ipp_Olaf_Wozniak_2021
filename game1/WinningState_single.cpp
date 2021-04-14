#include "WinningState_single.hpp"

WinningState_single::WinningState_single(sf::RenderWindow& window, std::stack<std::shared_ptr<State>>& states, double roznica) : State(window, states)
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
	logo.setString(std::to_string(roznica/1000));
	logo.setCharacterSize(50);
	logo.setPosition((window.getSize().x / 2) - 50, 20);
}

WinningState_single::~WinningState_single()
{
}

void WinningState_single::updateMousePosition()
{
}

void WinningState_single::updateButtons()
{
}

void WinningState_single::update(const sf::Time dt)
{
}

void WinningState_single::renderButtons(sf::RenderTarget& target)
{
}

void WinningState_single::draw()
{
	window.draw(background);
	window.draw(logo);
	renderButtons(window);
}

void WinningState_single::handleEvent(const sf::Event& event)
{
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
	{
		states.push(std::shared_ptr<State>(new MainMenuState(window, states)));
	}
}

void WinningState_single::initButtons()
{
}
