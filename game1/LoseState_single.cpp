#include "LoseState_single.hpp"

LoseState_single::LoseState_single(sf::RenderWindow& window, std::stack<std::shared_ptr<State>>& states) : State(window, states)
{
	initButtons();
	font.loadFromFile("fonts/MiniKongo.ttf");
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
	logo.setPosition((window.getSize().x / 2) - 170, 20);
}

LoseState_single::~LoseState_single()
{
	auto it = buttons.begin();
	for (it = buttons.begin(); it != buttons.end(); ++it)
	{
		delete it->second;
	}
}

void LoseState_single::updateMousePosition()
{
	mousePosScreen = sf::Mouse::getPosition();
	mousePosWindow = sf::Mouse::getPosition(window);
	mousePosView = window.mapPixelToCoords(sf::Mouse::getPosition(window));
}

void LoseState_single::updateButtons()
{
	for (auto& it : buttons)
	{
		it.second->update(mousePosView);
	}
}

void LoseState_single::update(const sf::Time dt)
{
	updateMousePosition();
	updateButtons();
}

void LoseState_single::renderButtons(sf::RenderTarget& target)
{
	for (auto& it : buttons)
	{
		it.second->render(target);
	}
}

void LoseState_single::draw()
{
	window.draw(background);
	window.draw(logo);
	renderButtons(window);
}

void LoseState_single::handleEvent(const sf::Event& event)
{
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape || buttons["GAME_MENU"]->isPressed())
	{
		states.push(std::shared_ptr<State>(new MainMenuState(window, states)));
	}
}

void LoseState_single::initButtons()
{
	buttons["GAME_MENU"] = new Button(100, window.getSize().y - 100, 200, 30, &font, "Back", sf::Color::White, sf::Color::Cyan, sf::Color::Cyan);
}