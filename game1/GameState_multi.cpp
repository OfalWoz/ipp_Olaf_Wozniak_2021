#include "GameState_multi.hpp"

GameState_multi::GameState_multi(sf::RenderWindow& window, std::stack<std::shared_ptr<State>>& states) : State(window, states)
{
	font.loadFromFile("fonts/arial.ttf");
	//initButtons();
	if (!birdText.loadFromFile("textures/redbird-upflap.png"))
	{
		std::cout << "ERROR::LOADING BIRD TEXTURES\n";
	}
	if (!birdtwoText.loadFromFile("textures/yellowbird-midflap.png"))
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
	background.setTexture(backText);

	sf::Vector2f birdtwo_size = (sf::Vector2f)birdText.getSize();
	birdtwo.setScale(sf::Vector2f(window.getSize().x / (birdtwo_size.x * 15), window.getSize().y / (birdtwo_size.y * 15)));
	birdtwo.setTexture(birdtwoText);

	sf::Vector2f bird_size = (sf::Vector2f)birdtwoText.getSize();
	bird.setScale(sf::Vector2f(window.getSize().x / (bird_size.x * 15), window.getSize().y / (bird_size.y * 15)));
	bird.setTexture(birdText);

	sf::Vector2f rock_size = (sf::Vector2f)rockText.getSize();
	rock.setTexture(rockText);
	rock.setScale(sf::Vector2f(2, 2));
	rock.setPosition(rx, ry);

	piorko.setTexture(piorkoText);
	piorko.setPosition(px, py);

	wynik.setFont(font);
	punkt = std::to_string(ptk);
	wynik.setString("First Player: " + punkt + "/25");
	wynik.setCharacterSize(50);
	wynik.setPosition(10, 10);

	wyniktwo.setFont(font);
	punkttwo = std::to_string(ptk2);
	wyniktwo.setString("Second Player: " + punkttwo + "/25");
	wyniktwo.setCharacterSize(50);
	wyniktwo.setPosition(window.getSize().x - 460, 10);

	start = clock();
}

GameState_multi::~GameState_multi()
{
	auto it = buttons.begin();
	for (it = buttons.begin(); it != buttons.end(); ++it)
	{
		delete it->second;
	}
}

void GameState_multi::updateMousePosition()
{
	mousePosScreen = sf::Mouse::getPosition();
	mousePosWindow = sf::Mouse::getPosition(window);
	mousePosView = window.mapPixelToCoords(sf::Mouse::getPosition(window));
}

void GameState_multi::updateButtons()
{
	for (auto& it : buttons)
	{
		it.second->update(mousePosView);
	}
}

void GameState_multi::updatePiorko()
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
		wynik.setString("First Player: " + punkt + "/25");
	}
	if (birdtwo.getGlobalBounds().intersects(piorko.getGlobalBounds()))
	{
		float px = rand() % 400 + 200;
		float py = rand() % 400 + 200;
		ptk2++;
		std::cout << ptk2 << "\n";
		window.clear();
		piorko.setPosition(px, py);
		punkttwo = std::to_string(ptk2);
		wyniktwo.setString("Second Player: " + punkttwo + "/25");
	}
}

void GameState_multi::updateBird()
{
	bird_x = bird_x + bird_vx;
	bird_y = bird_y + bird_vy * 2;
	bird_vy = bird_vy - 0.1 * (-2);

	bird2_x = bird2_x + bird2_vx;
	bird2_y = bird2_y + bird2_vy * 2;
	bird2_vy = bird2_vy - 0.1 * (-2);

	ry = ry - rock_vy;

	if (ry == (window.getSize().y / 2) - 100)
	{
		rock_vy = -2;
	}
	if (ry == window.getSize().y)
	{
		rock_vy = 2;
	}

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

	if (bird2_vy > 2)
	{
		bird2_vy = 2;
	}
	if (bird2_x < -10)
	{
		bird2_x = window.getSize().x;
	}
	if (bird2_y > window.getSize().y)
	{
		bird2_y = 0;
	}
	if (bird2_y < -10)
	{
		bird2_y = window.getSize().y;
	}
	birdtwo.setPosition(bird2_x, bird2_y);
	bird.setPosition(bird_x, bird_y);
	rock.setPosition(rx, ry);
}

void GameState_multi::updateRock(const sf::Time dt)
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
				wynik.setString("First Player: " + punkt + "/25");
			}
			if (birdtwo.getGlobalBounds().intersects(rock.getGlobalBounds()))
			{
				timeSinceLastUpdateSpecial = sf::seconds(0.f);
				std::cout << "kolizja2\n";
				ptk2--;
				window.clear();
				punkttwo = std::to_string(ptk2);
				wyniktwo.setString("Second Player: " + punkttwo + "/25");
			}
		}
	}
}

void GameState_multi::update(const sf::Time dt)
{
	updateMousePosition();
	updateButtons();
	if (ptk == 25)
	{
		end = clock();
		double roznica = difftime(end, start);
		printf("The time was: %f\n", roznica / CLK_TCK);
		//states.push(std::shared_ptr<State>(new WinningState_single(window, states, roznica)));
	}
	else
	{
		updatePiorko();
		updateBird();
		updateRock(dt);
	}
}

void GameState_multi::renderButtons(sf::RenderTarget& target)
{
	for (auto& it : buttons)
	{
		it.second->render(target);
	}
}

void GameState_multi::draw()
{
	window.draw(background);
	renderButtons(window);
	window.draw(bird);
	window.draw(birdtwo);
	window.draw(piorko);
	window.draw(rock);
	window.draw(wynik);
	window.draw(wyniktwo);
}

void GameState_multi::handleEvent(const sf::Event& event)
{
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up )
	{
		bird_y = bird_y - 1;
		bird_vy = -5;
	}
	if (event.key.code == sf::Mouse::Left )
	{
		bird2_y = bird2_y - 1;
		bird2_vy = -5;
	}
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
	{
		states.pop();
	}
}
