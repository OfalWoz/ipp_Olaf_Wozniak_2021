#include "GameState_easy.hpp"

GameState_easy::GameState_easy(sf::RenderWindow& window, std::stack<std::shared_ptr<State>>& states) : State(window, states) 
{
	initButtons();
	if (!backText.loadFromFile("textures/back.png"))
	{
		std::cout << "ERROR::LOADING BACKGROUND TEXTURES\n";
	}
	sf::Vector2f back = (sf::Vector2f)backText.getSize();
	background.setScale(sf::Vector2f(window.getSize().x / back.x, window.getSize().y / back.y));
	background.setTexture(backText);
}

GameState_easy::~GameState_easy()
{
	auto it = buttons.begin();
	for (it = buttons.begin(); it != buttons.end(); ++it) 
	{
		delete it->second;
	}
}

void GameState_easy::updateMousePosition()
{
	mousePosScreen = sf::Mouse::getPosition();
	mousePosWindow = sf::Mouse::getPosition(window);
	mousePosView = window.mapPixelToCoords(sf::Mouse::getPosition(window));
}

void GameState_easy::updateButtons()
{
	for (auto& it : buttons) {
		it.second->update(mousePosView);
	}
}

void GameState_easy::update(const sf::Time dt)
{
	updateMousePosition();
	updateButtons();
}

void GameState_easy::initButtons()
{
}

void GameState_easy::renderButtons(sf::RenderTarget& target)
{
	for (auto& it : buttons) 
	{
		it.second->render(target);
	}
}

void GameState_easy::draw()
{
	window.draw(background);
	renderButtons(window);
}

void GameState_easy::handleEvent(const sf::Event& event)
{
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
	{
		states.pop();
	}
}