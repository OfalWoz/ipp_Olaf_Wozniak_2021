#include "MainMenuState.hpp"

void MainMenuState::initButtons() {
	font.loadFromFile("fonts/MiniKongo.ttf");
	buttons["GAME_STATE"] = new Button(window.getSize().x / 2 - 100, 150, 150, 30,
		&font,"New Game", 
		sf::Color::White, sf::Color::Cyan, sf::Color::Cyan);

	buttons["GAME_HIGHT"] = new Button(window.getSize().x / 2 - 100, 200, 150, 30,
		&font, "Hight Scores",
		sf::Color::White, sf::Color::Cyan, sf::Color::Cyan);

	buttons["GAME_SET"] = new Button(window.getSize().x / 2 - 100, 250, 150, 30,
		&font, "Settings", 
		sf::Color::White, sf::Color::Cyan, sf::Color::Cyan);

	buttons["GAME_EXIT"] = new Button(window.getSize().x / 2 - 100, 300, 150, 30,
		&font, "Quit", 
		sf::Color::White, sf::Color::Cyan, sf::Color::Cyan);
}

MainMenuState::MainMenuState(sf::RenderWindow& window, std::stack<std::shared_ptr<State>>& states)
	: State(window, states) 
{
	initButtons();
	if (!backText.loadFromFile("textures/back.png")) 
	{
		std::cout << "ERROR::LOADING BACKGROUND TEXTURES\n";
	}
	sf::Vector2f back = (sf::Vector2f)backText.getSize();
	background.setScale(sf::Vector2f(window.getSize().x / back.x, window.getSize().y / back.y));
	background.setTexture(backText);

	if (!wozText.loadFromFile("textures/woz.png")) {}

	woz.setPosition(window.getSize().x - 150, window.getSize().y - 150);
	woz.setRadius(50);
	woz.setTexture(&wozText);

	logo.setFont(font);
	logo.setString("the crazy feathers");
	logo.setCharacterSize(50);
	logo.setPosition(window.getSize().x/2 - 350, 20);

	text.setFont(font);
	text.setString("@ofalwoz");
	text.setCharacterSize(20);
	text.setPosition(window.getSize().x - 160, window.getSize().y - 50);
}

void MainMenuState::updateMousePosition() 
{
	mousePosScreen = sf::Mouse::getPosition();
	mousePosWindow = sf::Mouse::getPosition(window);
	mousePosView = window.mapPixelToCoords(sf::Mouse::getPosition(window));
}

void MainMenuState::updateButtons() 
{
	for (auto& it : buttons) 
	{
		it.second->update(mousePosView);
	}
}

void MainMenuState::update(const sf::Time dt) 
{
	updateMousePosition();
	updateButtons();
}

void MainMenuState::renderButtons(sf::RenderTarget& target) 
{
	for (auto& it : buttons) 
	{
		it.second->render(target);
	}
}

void MainMenuState::draw() 
{
	window.draw(background);
	window.draw(woz);
	window.draw(text);
	window.draw(logo);
	renderButtons(window);
}

void MainMenuState::handleEvent(const sf::Event& event) 
{
	if (buttons["GAME_SET"]->isPressed())
	{
		states.push(std::shared_ptr<State>(new Settings(window, states)));
	}
	if (buttons["GAME_STATE"]->isPressed())
	{
		states.push(std::shared_ptr<State>(new HardLevelState(window, states)));
	}
	if (buttons["GAME_HIGHT"]->isPressed())
	{
		states.push(std::shared_ptr<State>(new HightScoreState(window, states)));
	}
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape || buttons["GAME_EXIT"]->isPressed()) 
	{
		window.close();
	}
}