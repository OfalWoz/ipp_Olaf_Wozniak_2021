#include "WinningState_single.hpp"

WinningState_single::WinningState_single(sf::RenderWindow& window, std::stack<std::shared_ptr<State>>& states, double roznica, int hard) : State(window, states)
{
	initButtons();
	font.loadFromFile("fonts/arial.ttf");
	if (!backText.loadFromFile("textures/back.png"))
	{
		std::cout << "ERROR::LOADING BACKGROUND TEXTURES\n";
	}
	sf::Vector2f back = (sf::Vector2f)backText.getSize();
	background.setScale(sf::Vector2f(window.getSize().x / back.x, window.getSize().y / back.y));
	background.setTexture(backText);

	logo.setFont(font);
	logo.setString(std::to_string(roznica/1000));
	logo.setCharacterSize(50);
	logo.setPosition((window.getSize().x / 2) - 50, 20);

	std::ifstream file("config/score.ini");
	std::string linia;

	for (int i = 0; i < 15; i++)
	{
		std::getline(file, linia);
		hardTimes[i] = std::stoi(linia);
		std::cout << linia <<"\n";
	}

	if (hard == 3)
	{
		if (roznica < hardTimes[0])
		{
			hardTimes[4] = hardTimes[3];
			hardTimes[3] = hardTimes[2];
			hardTimes[2] = hardTimes[1];
			hardTimes[1] = hardTimes[0];
			hardTimes[0] = roznica;
		}
		else
		{
			if (roznica < hardTimes[1])
			{
				hardTimes[4] = hardTimes[3];
				hardTimes[3] = hardTimes[2];
				hardTimes[2] = hardTimes[1];
				hardTimes[1] = roznica;
			}
			else
			{
				if (roznica < hardTimes[2])
				{
					hardTimes[4] = hardTimes[3];
					hardTimes[3] = hardTimes[2];
					hardTimes[2] = roznica;
				}
				else
				{
					if (roznica < hardTimes[3])
					{
						hardTimes[4] = hardTimes[3];
						hardTimes[3] = roznica;
					}
					else
					{
						if (roznica < hardTimes[4])
						{
							hardTimes[4] = roznica;
						}
					}
				}
			}
		}
		std::cout << hardTimes[0];
	}
	if (hard == 2)
	{
		if (roznica < hardTimes[5])
		{
			hardTimes[9] = hardTimes[8];
			hardTimes[8] = hardTimes[7];
			hardTimes[7] = hardTimes[6];
			hardTimes[6] = hardTimes[5];
			hardTimes[5] = roznica;
		}
		else
		{
			if (roznica < hardTimes[6])
			{
				hardTimes[9] = hardTimes[8];
				hardTimes[8] = hardTimes[7];
				hardTimes[7] = hardTimes[6];
				hardTimes[6] = roznica;
			}
			else
			{
				if (roznica < hardTimes[7])
				{
					hardTimes[9] = hardTimes[8];
					hardTimes[8] = hardTimes[7];
					hardTimes[7] = roznica;
				}
				else
				{
					if (roznica < hardTimes[8])
					{
						hardTimes[9] = hardTimes[8];
						hardTimes[8] = roznica;
					}
					else
					{
						if (roznica < hardTimes[9])
						{
							hardTimes[9] = roznica;
						}
					}
				}
			}
		}
		std::cout << hardTimes[5];
	}
	if (hard == 1)
	{
		if (roznica < hardTimes[10])
		{
			hardTimes[14] = hardTimes[13];
			hardTimes[13] = hardTimes[12];
			hardTimes[12] = hardTimes[11];
			hardTimes[11] = hardTimes[10];
			hardTimes[10] = roznica;
		}
		else
		{
			if (roznica < hardTimes[11])
			{
				hardTimes[14] = hardTimes[13];
				hardTimes[13] = hardTimes[12];
				hardTimes[12] = hardTimes[11];
				hardTimes[11] = roznica;
			}
			else
			{
				if (roznica < hardTimes[12])
				{
					hardTimes[14] = hardTimes[13];
					hardTimes[13] = hardTimes[12];
					hardTimes[12] = roznica;
				}
				else
				{
					if (roznica < hardTimes[13])
					{
						hardTimes[14] = hardTimes[13];
						hardTimes[13] = roznica;
					}
					else
					{
						if (roznica < hardTimes[14])
						{
							hardTimes[14] = roznica;
						}
					}
				}
			}
		}
		std::cout << hardTimes[5];
	}

	std::ofstream ofs("config/score.ini");
	if (ofs.is_open())
	{
		for (int i = 0; i < 15; i++)
		{
			ofs << std::to_string(hardTimes[i]) << "\n";
		}
	}
	ofs.close();
}

WinningState_single::~WinningState_single()
{
}

void WinningState_single::updateMousePosition()
{
}

void WinningState_single::updateButtons()
{
}

void WinningState_single::update(const sf::Time dt)
{
}

void WinningState_single::renderButtons(sf::RenderTarget& target)
{
}

void WinningState_single::draw()
{
	window.draw(background);
	window.draw(logo);
	renderButtons(window);
}

void WinningState_single::handleEvent(const sf::Event& event)
{
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
	{
		states.push(std::shared_ptr<State>(new MainMenuState(window, states)));
	}
}

void WinningState_single::initButtons()
{
}