#include "HightScoreState.hpp"

HightScoreState::HightScoreState(sf::RenderWindow& window, std::stack<std::shared_ptr<State>>& states) : State(window, states)
{
	initButtons();
	font.loadFromFile("fonts/RoguedashSolid-BWjqx.otf");
	if (!backText.loadFromFile("textures/back.png"))
	{
		std::cout << "ERROR::LOADING BACKGROUND TEXTURES\n";
	}
	sf::Vector2f back = (sf::Vector2f)backText.getSize();
	background.setScale(sf::Vector2f(window.getSize().x / back.x, window.getSize().y / back.y));
	background.setTexture(backText);

	logo.setFont(font);
	logo.setString("Hight Scores");
	logo.setCharacterSize(50);
	logo.setPosition((window.getSize().x / 2) - 100, 20);
	
	std::ifstream file("config/score.ini");
	std::string linia;
	for (int i = 0; i < 15; i++)
	{
		std::getline(file, linia);
		hardTimes[i] = std::stoi(linia);
		std::cout << hardTimes[i] << "\n";
	}
	fonts();
}

HightScoreState::~HightScoreState()
{
	auto it = buttons.begin();
	for (it = buttons.begin(); it != buttons.end(); ++it)
	{
		delete it->second;
	}
}

void HightScoreState::updateMousePosition()
{
	mousePosScreen = sf::Mouse::getPosition();
	mousePosWindow = sf::Mouse::getPosition(window);
	mousePosView = window.mapPixelToCoords(sf::Mouse::getPosition(window));
}

void HightScoreState::updateButtons()
{
	for (auto& it : buttons)
	{
		it.second->update(mousePosView);
	}
}

void HightScoreState::update(const sf::Time dt)
{
	updateMousePosition();
	updateButtons();
}

void HightScoreState::renderButtons(sf::RenderTarget& target)
{
	for (auto& it : buttons)
	{
		it.second->render(target);
	}
}

void HightScoreState::draw()
{
	window.draw(background);
	window.draw(logo);
	window.draw(score1);
	window.draw(score2);
	window.draw(score3);
	renderButtons(window);
}

void HightScoreState::handleEvent(const sf::Event& event)
{
	if (buttons["GAME_MENU"]->isPressed())
	{
		states.pop();
	}
}

void HightScoreState::initButtons()
{
	buttons["GAME_MENU"] = new Button(100, window.getSize().y - 100, 200, 30, &font, "Back", sf::Color::White, sf::Color::Cyan, sf::Color::Cyan);
}

void HightScoreState::fonts()
{
	score1.setFont(font);
	score1.setCharacterSize(30);
	score1.setString("Best for Hard:\n1. "+std::to_string(hardTimes[0] / 1000)+", 2. " + std::to_string(hardTimes[1] / 1000) + ", 3. " + std::to_string(hardTimes[2] / 1000) + ", 4. " + std::to_string(hardTimes[3] / 1000) + ", 5. " + std::to_string(hardTimes[4] / 1000));
	score1.setPosition(100, 100);

	score2.setFont(font);
	score2.setCharacterSize(30);
	score2.setString("Best for Normal:\n1. " + std::to_string(hardTimes[5] / 1000) + ", 2. " + std::to_string(hardTimes[6] / 1000) + ", 3. " + std::to_string(hardTimes[7] / 1000) + ", 4. " + std::to_string(hardTimes[8] / 1000) + ", 5. " + std::to_string(hardTimes[9] / 1000));
	score2.setPosition(100, 200);

	score3.setFont(font);
	score3.setCharacterSize(30);
	score3.setString("Best for Easy:\n1. " + std::to_string(hardTimes[10] / 1000) + ", 2. " + std::to_string(hardTimes[11] / 1000) + ", 3. " + std::to_string(hardTimes[12] / 1000) + ", 4. " + std::to_string(hardTimes[13] / 1000) + ", 5. " + std::to_string(hardTimes[14] / 1000));
	score3.setPosition(100, 300);
}