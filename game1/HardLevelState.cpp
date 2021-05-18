#include "HardLevelState.hpp"

HardLevelState::HardLevelState(sf::RenderWindow& window, std::stack<std::shared_ptr<State>>& states) : State(window, states)
{
	font.loadFromFile("fonts/MiniKongo.ttf");
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
	logo.setCharacterSize(40);
	logo.setPosition((window.getSize().x / 2) - 170, 20);

	Single.setFont(font);
	Single.setString("Singleplayer");
	Single.setCharacterSize(30);
	Single.setPosition((window.getSize().x / 2) + 50, 130);

	Multi.setFont(font);
	Multi.setString("Multiplayer");
	Multi.setCharacterSize(30);
	Multi.setPosition((window.getSize().x / 2) - 340, 130);
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

	buttons["GAME_MULTI_EASY"] = new Button(window.getSize().x / 2 - 300, 200, 150, 30, &font, "Easy", sf::Color::White, sf::Color::Cyan, sf::Color::Cyan);

	buttons["GAME_MULTI_NORMAL"] = new Button(window.getSize().x / 2 - 300, 250, 150, 30, &font, "Normal", sf::Color::White, sf::Color::Cyan, sf::Color::Cyan);

	buttons["GAME_MULTI_HARD"] = new Button(window.getSize().x / 2 - 300, 300, 150, 30, &font, "Hard", sf::Color::White, sf::Color::Cyan, sf::Color::Cyan);

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
	if (buttons["GAME_MULTI_EASY"]->isPressed())
	{
		int hard = 0;
		states.push(std::shared_ptr<State>(new GameState_multi(window, states, hard)));
	}
	if (buttons["GAME_MULTI_NORMAL"]->isPressed())
	{
		int hard = 1;
		states.push(std::shared_ptr<State>(new GameState_multi(window, states, hard)));
	}
	if (buttons["GAME_MULTI_HARD"]->isPressed())
	{
		int hard = 2;
		states.push(std::shared_ptr<State>(new GameState_multi(window, states, hard)));
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