#include "WinningState_multi.hpp"

WinningState_multi::WinningState_multi(sf::RenderWindow& window, std::stack<std::shared_ptr<State>>& states, int who) : State(window, states)
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
	if (who == 1)
	{
		logo.setString("First Player Win!");
	}
	if (who == 2)
	{
		logo.setString("Second Player Win!");
	}
	logo.setCharacterSize(50);
	logo.setPosition((window.getSize().x / 2) - 170, 20);
}

WinningState_multi::~WinningState_multi()
{
	auto it = buttons.begin();
	for (it = buttons.begin(); it != buttons.end(); ++it)
	{
		delete it->second;
	}
}

void WinningState_multi::updateMousePosition()
{
	mousePosScreen = sf::Mouse::getPosition();
	mousePosWindow = sf::Mouse::getPosition(window);
	mousePosView = window.mapPixelToCoords(sf::Mouse::getPosition(window));
}

void WinningState_multi::updateButtons()
{
	for (auto& it : buttons)
	{
		it.second->update(mousePosView);
	}
}

void WinningState_multi::update(const sf::Time dt)
{
	updateMousePosition();
	updateButtons();
}

void WinningState_multi::renderButtons(sf::RenderTarget& target)
{
	for (auto& it : buttons)
	{
		it.second->render(target);
	}
}

void WinningState_multi::draw()
{
	window.draw(background);
	window.draw(logo);
	renderButtons(window);
}

void WinningState_multi::handleEvent(const sf::Event& event)
{
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape || buttons["GAME_MENU"]->isPressed())
	{
		states.push(std::shared_ptr<State>(new MainMenuState(window, states)));
	}
}

void WinningState_multi::initButtons()
{
	buttons["GAME_MENU"] = new Button(100, window.getSize().y - 100, 200, 30, &font, "Back", sf::Color::White, sf::Color::Cyan, sf::Color::Cyan);
}
