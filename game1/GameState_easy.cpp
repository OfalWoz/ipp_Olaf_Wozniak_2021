#include "GameState_easy.hpp"

GameState_easy::GameState_easy(sf::RenderWindow& window, std::stack<std::shared_ptr<State>>& states) : State(window, states) 
{
	initButtons();
	if (!birdText.loadFromFile("textures/redbird-upflap.png"))
	{
		std::cout << "ERROR::LOADING BIRD TEXTURES\n";
	}
	if (!piorkoText.loadFromFile("textures/piorko.png"))
	{
		std::cout << "ERROR::LOADING POINT TEXTURES\n";
	}
	if (!backText.loadFromFile("textures/back.png"))
	{
		std::cout << "ERROR::LOADING BACKGROUND TEXTURES\n";
	}
	sf::Vector2f back = (sf::Vector2f)backText.getSize();
	background.setScale(sf::Vector2f(window.getSize().x / back.x, window.getSize().y / back.y));
	bird.setScale(sf::Vector2f(window.getSize().x / 500, window.getSize().x / 500));
	background.setTexture(backText);
	bird.setTexture(birdText);
	piorko.setTexture(piorkoText);
	piorko.setPosition(px, py);
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
	for (auto& it : buttons) 
	{
		it.second->update(mousePosView);
	}
}

void GameState_easy::updatePiorko()
{
	if (bird.getGlobalBounds().intersects(piorko.getGlobalBounds()))
	{
		int px = rand() % (window.getSize().x - 100) + 100;
		int py = rand() % (window.getSize().y - 200) + 100;
		ptk++;
		std::cout << ptk << "\n";
		window.clear();
		piorko.setPosition(px, py);
	}
	
}

void GameState_easy::updateBird()
{
	bird_x = bird_x + bird_vx;
	bird_y = bird_y + bird_vy * 2;
	bird_vy = bird_vy - 0.1 * (-2);
	if (bird_vy > 2)
	{
		bird_vy = 2;
	}
	if (bird_x > window.getSize().x)
	{
		bird_x = -10;
	}
	bird.setPosition(bird_x, bird_y);
}

void GameState_easy::update(const sf::Time dt)
{
	updateMousePosition();
	updateButtons();
	updatePiorko();
	updateBird();
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
	window.draw(bird);
	window.draw(piorko);
}

void GameState_easy::handleEvent(const sf::Event& event)
{
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up || event.key.code == sf::Mouse::Left)
	{
		bird_y = bird_y - 1;
		bird_vy = -5;
	}
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
	{
		states.pop();
	}
}