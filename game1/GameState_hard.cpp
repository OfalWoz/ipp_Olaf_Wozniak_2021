#include "GameState_hard.hpp"

GameState_hard::GameState_hard(sf::RenderWindow& window, std::stack<std::shared_ptr<State>>& states) : State(window, states)
{
	font.loadFromFile("fonts/MiniKongo.ttf");
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

	sf::Vector2f rock_size2 = (sf::Vector2f)rockText2.getSize();
	rock2.setTexture(rockText);
	rock2.rotate(180);
	rock2.setScale(sf::Vector2f(2, 2));
	rock2.setPosition(rx2, ry2);

	sf::Vector2f rock_size = (sf::Vector2f)rockText.getSize();
	rock.setTexture(rockText);
	rock.setScale(sf::Vector2f(2, 2));
	rock.setPosition(rx, ry);

	piorko.setTexture(piorkoText);
	piorko.setPosition(px, py);

	wynik.setFont(font);
	punkt = std::to_string(ptk);
	wynik.setString("Score: " + punkt + "/25");
	wynik.setCharacterSize(50);
	wynik.setPosition(10, 10);

	start = clock();
}

GameState_hard::~GameState_hard()
{
	auto it = buttons.begin();
	for (it = buttons.begin(); it != buttons.end(); ++it)
	{
		delete it->second;
	}
}

void GameState_hard::updateMousePosition()
{
	mousePosScreen = sf::Mouse::getPosition();
	mousePosWindow = sf::Mouse::getPosition(window);
	mousePosView = window.mapPixelToCoords(sf::Mouse::getPosition(window));
}

void GameState_hard::updateButtons()
{
	for (auto& it : buttons)
	{
		it.second->update(mousePosView);
	}
}

void GameState_hard::updatePiorko()
{
	if (bird.getGlobalBounds().intersects(piorko.getGlobalBounds()))
	{
		float px = rand() % 400 + 200;
		float py = rand() % 400 + 200;
		ptk++;
		std::cout << ptk << "\n";
		window.clear();
		piorko.setPosition(px, py);
		punkt = std::to_string(ptk);
		wynik.setString("Score: " + punkt + "/25");
	}
}

void GameState_hard::updateBird()
{
	bird_x = bird_x + bird_vx;
	bird_y = bird_y + bird_vy * 2;
	bird_vy = bird_vy - 0.1 * (-2);
	ry = ry - rock_vy;
	ry2 = ry2 - rock_vy2;

	if (ry == (window.getSize().y / 2)+50)
	{
		rock_vy = -2;
	}
	if (ry == window.getSize().y)
	{
		rock_vy = 2;
	}
	if (ry2 == (window.getSize().y / 2) - 50)
	{
		rock_vy2 = 2;
	}
	if (ry2 == 0)
	{
		rock_vy2 = -2;
	}
	if (bird_vy > 2)
	{
		bird_vy = 2;
	}
	if (bird_x > window.getSize().x)
	{
		bird_x = -10;
	}
	bird.setPosition(bird_x, bird_y);
	rock.setPosition(rx, ry);
	rock2.setPosition(rx2, ry2);
}

void GameState_hard::updateRock(const sf::Time dt)
{
	if (ry <= window.getSize().y)
	{
		timeSinceLastUpdateSpecial += dt;
		if (timeSinceLastUpdateSpecial > sf::seconds(1.f))
		{
			if (bird.getGlobalBounds().intersects(rock.getGlobalBounds()))
			{
				timeSinceLastUpdateSpecial = sf::seconds(0.f);
				std::cout << "kolizja\n";
				ptk--;
				window.clear();
				punkt = std::to_string(ptk);
				wynik.setString("Score: " + punkt + "/25");
			}
			if (bird.getGlobalBounds().intersects(rock2.getGlobalBounds()))
			{
				timeSinceLastUpdateSpecial = sf::seconds(0.f);
				std::cout << "kolizja\n";
				ptk--;
				window.clear();
				punkt = std::to_string(ptk);
				wynik.setString("Score: " + punkt + "/25");
			}
		}
		if (bird_y > window.getSize().y || bird_y < -10)
		{
			states.push(std::shared_ptr<State>(new LoseState_single(window, states)));
		}
	}
}

void GameState_hard::update(const sf::Time dt)
{
	updateMousePosition();
	updateButtons();
	if (ptk == 25)
	{
		end = clock();
		double roznica = difftime(end, start);
		printf("The time was: %f\n", roznica / CLK_TCK);
		states.push(std::shared_ptr<State>(new WinningState_single(window, states, roznica, hard)));
	}
	if (ptk == -5)
	{
		states.push(std::shared_ptr<State>(new LoseState_single(window, states)));
	}
	else
	{
		updatePiorko();
		updateBird();
		updateRock(dt);
	}
}

void GameState_hard::renderButtons(sf::RenderTarget& target)
{
	for (auto& it : buttons)
	{
		it.second->render(target);
	}
}

void GameState_hard::draw()
{
	window.draw(background);
	renderButtons(window);
	window.draw(bird);
	window.draw(piorko);
	window.draw(rock);
	window.draw(rock2);
	window.draw(wynik);
}

void GameState_hard::handleEvent(const sf::Event& event)
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

void GameState_hard::initButtons()
{
}