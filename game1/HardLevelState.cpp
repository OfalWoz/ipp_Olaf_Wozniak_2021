#include "HardLevelState.hpp"

HardLevelState::HardLevelState(sf::RenderWindow& window, std::stack<std::shared_ptr<State>>& states) : State(window, states)
{
	font.loadFromFile("fonts/RoguedashSolid-BWjqx.otf");
	initButtons();
	if (!backText.loadFromFile("textures/back.png"))
	{
		std::cout << "ERROR::LOADING BACKGROUND TEXTURES\n";
	}
	sf::Vector2f back = (sf::Vector2f)backText.getSize();
	background.setScale(sf::Vector2f(window.getSize().x / back.x, window.getSize().y / back.y));
	background.setTexture(backText);

	logo.setFont(font);
	logo.setString("Choose level");
	logo.setCharacterSize(50);
	logo.setPosition((window.getSize().x / 2) - 120, 20);

	Single.setFont(font);
	Single.setString("Singleplayer");
	Single.setCharacterSize(40);
	Single.setPosition((window.getSize().x / 2) + 80, 130);

	Multi.setFont(font);
	Multi.setString("Multiplayer");
	Multi.setCharacterSize(40);
	Multi.setPosition((window.getSize().x / 2) - 320, 130);
}

HardLevelState::~HardLevelState()
{
	auto it = buttons.begin();
	for (it = buttons.begin(); it != buttons.end(); ++it) 
	{
		delete it->second;
	}
}

void HardLevelState::initButtons()
{
	buttons["GAME_EASY"] = new Button(window.getSize().x / 2 + 100, 200, 150, 30, &font, "Easy", sf::Color::White, sf::Color::Cyan, sf::Color::Cyan);

	buttons["GAME_NORMAL"] = new Button(window.getSize().x / 2 + 100, 250, 150, 30, &font, "Normal", sf::Color::White, sf::Color::Cyan, sf::Color::Cyan);

	buttons["GAME_HARD"] = new Button(window.getSize().x / 2 + 100, 300, 150, 30, &font, "Hard", sf::Color::White, sf::Color::Cyan, sf::Color::Cyan);

	buttons["GAME_MULTI"] = new Button(window.getSize().x / 2 - 300, 250, 150, 30, &font, "Normal", sf::Color::White, sf::Color::Cyan, sf::Color::Cyan);

	buttons["GAME_MENU"] = new Button(100, window.getSize().y - 100, 200, 30, &font, "Back", sf::Color::White, sf::Color::Cyan, sf::Color::Cyan);
}

void HardLevelState::updateMousePosition()
{
	mousePosScreen = sf::Mouse::getPosition();
	mousePosWindow = sf::Mouse::getPosition(window);
	mousePosView = window.mapPixelToCoords(sf::Mouse::getPosition(window));
}

void HardLevelState::updateButtons()
{
	for (auto& it : buttons) 
	{
		it.second->update(mousePosView);
	}
}

void HardLevelState::update(const sf::Time dt)
{
	updateMousePosition();
	updateButtons();
	if (buttons["GAME_EASY"]->isPressed())
	{
		states.push(std::shared_ptr<State>(new GameState_easy(window, states)));
	}
	if (buttons["GAME_NORMAL"]->isPressed())
	{
		states.push(std::shared_ptr<State>(new GameState_normal(window, states)));
	}
	if (buttons["GAME_HARD"]->isPressed())
	{
		states.push(std::shared_ptr<State>(new GameState_hard(window, states)));
	}
	if (buttons["GAME_MULTI"]->isPressed())
	{
		states.push(std::shared_ptr<State>(new GameState_multi(window, states)));
	}
	if (buttons["GAME_MENU"]->isPressed()) 
	{
		states.pop();
	}
}

void HardLevelState::renderButtons(sf::RenderTarget& target)
{
	for (auto& it : buttons)
	{
		it.second->render(target);
	}
}

void HardLevelState::draw()
{
	window.draw(background);
	window.draw(logo);
	window.draw(Single);
	window.draw(Multi);
	renderButtons(window);
}

void HardLevelState::handleEvent(const sf::Event& event)
{

	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) 
	{
		states.pop();
	}
}