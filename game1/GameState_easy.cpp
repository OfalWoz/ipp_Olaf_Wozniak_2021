#include "GameState_easy.hpp"


GameState_easy::GameState_easy(sf::RenderWindow& window, std::stack<std::shared_ptr<State>>& states) : State(window, states) 
{
	font.loadFromFile("fonts/RoguedashSolid-BWjqx.otf");
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
	if (!rockText.loadFromFile("textures/pipe-green.png"))
	{
		std::cout << "ERROR::LOADING ROCK TEXTURES\n";
	}
	sf::Vector2f back = (sf::Vector2f)backText.getSize();
	background.setScale(sf::Vector2f(window.getSize().x / back.x, window.getSize().y / back.y));

	sf::Vector2f bird_size = (sf::Vector2f)birdText.getSize();
	bird.setScale(sf::Vector2f(window.getSize().x / (bird_size.x * 15), window.getSize().y / (bird_size.y * 15)));
	background.setTexture(backText);
	bird.setTexture(birdText);

	sf::Vector2f rock_size = (sf::Vector2f)rockText.getSize();
	rock.setTexture(rockText);
	rock.setScale(sf::Vector2f(window.getSize().x / (rock_size.x * 15), window.getSize().y / (rock_size.y * 15)));
	rock.setPosition(rx, ry);

	piorko.setTexture(piorkoText);
	piorko.setPosition(px, py);

	wynik.setFont(font);
	punkt = std::to_string(ptk);
	wynik.setString("Score: " + punkt);
	wynik.setCharacterSize(50);
	wynik.setPosition(10, 10);
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
		int py = rand() % (window.getSize().y - 300) + 200;
		int rx = rand() % (window.getSize().x - 100) + 200;
		int ry = rand() % (window.getSize().y - 300) + 200;
		ptk++;
		std::cout << ptk << "\n";
		window.clear();
		piorko.setPosition(px, py);
		rock.setPosition(rx, ry);
		punkt = std::to_string(ptk);
		wynik.setString("Score: " + punkt);
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
	if (bird_y > window.getSize().y)
	{
		bird_y = 0;
	}
	if (bird_y < -10)
	{
		bird_y = window.getSize().y;
	}
	bird.setPosition(bird_x, bird_y);
}

void GameState_easy::updateRock()
{
	if (rock.getGlobalBounds().intersects(piorko.getGlobalBounds()))
	{
		int rx = rand() % (window.getSize().x - 100) + 200;
		int ry = rand() % (window.getSize().y - 300) + 200;
		window.clear();
		rock.setPosition(rx, ry);
	}
	if (bird.getGlobalBounds().intersects(rock.getGlobalBounds()))
	{
		int rx = rand() % (window.getSize().x - 100) + 100;
		int ry = rand() % (window.getSize().y - 300) + 200;
		std::cout << "kolizja\n";
		ptk--;
		window.clear();
		rock.setPosition(rx, ry);
		punkt = std::to_string(ptk);
		wynik.setString("Score: " + punkt);
	}
}

void GameState_easy::update(const sf::Time dt)
{
	updateMousePosition();
	updateButtons();
	updatePiorko();
	updateBird();
	updateRock();
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
	window.draw(rock);
	window.draw(wynik);
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