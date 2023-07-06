#define _USE_MATH_DEFINES
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <vector>
#include <random>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <chrono>
#include "telaPerdeu.hpp"

class Player {
public:
	Player(float x, float y, const Maze &maze) :
			m_x(x), m_y(y), m_maze(maze) {
	}

	void Move(int dx, int dy) {
		int newX = static_cast<int>(m_x) + dx;
		int newY = static_cast<int>(m_y) + dy;

		// Verificar se a nova posição está dentro dos limites do labirinto
		if (newX >= 0 && newX < m_maze.GetWidth() && newY >= 0
				&& newY < m_maze.GetHeight()) {
			// Verificar se a célula na nova posição é vazia (false)
			if (m_maze.GetCellValue(newX, newY) && !(newX == 2 && newY == 0)
					&& !(newX == 10 && newY == 12)) {
				m_x = static_cast<float>(newX);
				m_y = static_cast<float>(newY);
			}
		}
	}

	void Draw(sf::RenderWindow &window, const Maze &maze, float cellSize,
			sf::Texture &playerTexture) {

		float posX = static_cast<float>(m_x) * cellSize;
		float posY = static_cast<float>(m_y) * cellSize;

		float playerSize = cellSize * 0.8f;

		sf::Sprite playerSprite;
		playerSprite.setTexture(playerTexture);

		playerSprite.setTextureRect(
				sf::IntRect(0, 0, playerTexture.getSize().x,
						playerTexture.getSize().y));

		playerSprite.setScale(playerSize / playerTexture.getSize().x,
				playerSize / playerTexture.getSize().y);
		playerSprite.setPosition(posX + (cellSize - playerSize) / 2.0f,
				posY + (cellSize - playerSize) / 2.0f);

		window.draw(playerSprite);
	}

	float GetX() const {
		return m_x;
	}

	float GetY() const {
		return m_y;
	}

	void PrintCurrentCell() {
		int x = static_cast<int>(m_x);
		int y = static_cast<int>(m_y);

		std::cout << "O player está na célula (" << x << ", " << y << ")"
				<< std::endl;
	}

	void setPosition(float x, float y) {
		m_x = x;
		m_y = y;
	}

private:
	unsigned int m_x;
	unsigned int m_y;
	const Maze &m_maze;
};

class Inimigo {
public:
	Inimigo(float x, float y, const Maze &maze) :
			m_x(x), m_y(y), m_maze(maze) {
	}

	void MoveRandomly(int tamLab) {
		int dx = 0;
		int dy = 0;

		// Escolher uma direção aleatória
		int direction = rand() % 4;
		switch (direction) {
		case 0: // Cima
			dy = -1;
			break;
		case 1: // Baixo
			dy = 1;
			break;
		case 2: // Esquerda
			dx = -1;
			break;
		case 3: // Direita
			dx = 1;
			break;
			sf::sleep(sf::milliseconds(115));
		}

		// Calcular a nova posição
		int newX = static_cast<int>(m_x) + dx;
		int newY = static_cast<int>(m_y) + dy;

		// Verificar se a nova posição está dentro dos limites do labirinto
		if (newX >= 0 && newX < m_maze.GetWidth() && newY >= 0
				&& newY < m_maze.GetHeight()) {

			// Verificar se a célula na nova posição é vazia (false)
			if (m_maze.GetCellValue(newX, newY) && !(newX == 2 && newY == 0)
					&& !(newX == 10 * tamLab && newY == 12 * tamLab)) {
				m_x = static_cast<float>(newX);
				m_y = static_cast<float>(newY);
				sf::sleep(sf::milliseconds(115));
			}
		}
	}

	void Draw(sf::RenderWindow &window, const Maze &maze, float cellSize,
			sf::Texture &enemyTexture) {
		float posX = static_cast<float>(m_x) * cellSize;
		float posY = static_cast<float>(m_y) * cellSize;

		float enemySize = cellSize * 0.8f;

		sf::Sprite enemySprite;
		enemySprite.setTexture(enemyTexture);

		enemySprite.setTextureRect(
				sf::IntRect(0, 0, enemyTexture.getSize().x,
						enemyTexture.getSize().y));

		enemySprite.setScale(enemySize / enemyTexture.getSize().x,
				enemySize / enemyTexture.getSize().y);
		enemySprite.setPosition(posX + (cellSize - enemySize) / 2.0f,
				posY + (cellSize - enemySize) / 2.0f);

		window.draw(enemySprite);
	}

	float GetX() const {
		return m_x;
	}

	float GetY() const {
		return m_y;
	}

	void setPosition(float x, float y) {
		m_x = x;
		m_y = y;
	}

private:
	unsigned int m_x;
	unsigned int m_y;
	const Maze &m_maze;
};

void MovePlayer(const sf::Event &event, Player &player, bool &isMoving) {
	if (event.type == sf::Event::KeyPressed) {
		if (event.key.code == sf::Keyboard::Up) {
			player.Move(0, -1);
		} else if (event.key.code == sf::Keyboard::Down) {
			player.Move(0, 1);
		} else if (event.key.code == sf::Keyboard::Left) {
			player.Move(-1, 0);
		} else if (event.key.code == sf::Keyboard::Right) {
			player.Move(1, 0);
		}
		// sf::sleep(sf::milliseconds(1));
	} else if (event.type == sf::Event::KeyReleased) {

		if (event.key.code == sf::Keyboard::Up
				|| event.key.code == sf::Keyboard::Down
				|| event.key.code == sf::Keyboard::Left
				|| event.key.code == sf::Keyboard::Right) {
			isMoving = false;

		}
	}
}

void MovePlayer2(const sf::Event &event, Player &player2, bool &isMoving) {
	if (event.type == sf::Event::KeyPressed) {
		if (event.key.code == sf::Keyboard::W) {
			player2.Move(0, -1);
		} else if (event.key.code == sf::Keyboard::S) {
			player2.Move(0, 1);
		} else if (event.key.code == sf::Keyboard::A) {
			player2.Move(-1, 0);
		} else if (event.key.code == sf::Keyboard::D) {
			player2.Move(1, 0);
		}

		//  sf::sleep(sf::milliseconds(1));
	} else if (event.type == sf::Event::KeyReleased) {
		if (event.key.code == sf::Keyboard::W
				|| event.key.code == sf::Keyboard::S
				|| event.key.code == sf::Keyboard::A
				|| event.key.code == sf::Keyboard::D) {
			isMoving = false;
		}
	}
}

bool CheckCollision(const Player &player, const Inimigo &inimigo) {
	float playerX = player.GetX();
	float playerY = player.GetY();
	float inimigoX = inimigo.GetX();
	float inimigoY = inimigo.GetY();

	if (playerX == inimigoX && playerY == inimigoY) {
		return true;
	}
	return false;
}

bool playerNaSaida(const Player &player, const Player &player2,
		unsigned int saidaX, unsigned int saidaY) {
	if (player.GetX() == saidaX && player.GetY() == saidaY
			|| player2.GetX() == saidaX && player2.GetY() == saidaY) {
		return true;
	} else {
		return false;
	}

}

void telaFinal()
{
	sf::RenderWindow paginaFinal(sf::VideoMode(1400, 800), "Maze Craze");

	sf::Image header;
	header.loadFromFile("assets/logoJogo.png");
	paginaFinal.setIcon(header.getSize().x, header.getSize().y, header.getPixelsPtr());

	sf::Texture bgFinalTex;
	bgFinalTex.loadFromFile("assets/backgroudFinal.png");
	sf::Sprite bgFinal(bgFinalTex);
	float escalaX = paginaFinal.getSize().x / static_cast<float>(bgFinalTex.getSize().x);
	float escalaY = paginaFinal.getSize().y / static_cast<float>(bgFinalTex.getSize().y);
	bgFinal.setScale(escalaX, escalaY);

	sf::Font fonte;
	sf::Text titulo("Maze Craze", fonte, 110);
	titulo.setFillColor(sf::Color::Black);
	titulo.setPosition(389, 354);

	fonte.loadFromFile("assets/fonte.ttf");
	sf::Text jogar("", fonte, 32);
	jogar.setFillColor(sf::Color::White);
	jogar.setPosition(235, 600);

	sf::Text menu("Sair", fonte, 32);
	menu.setFillColor(sf::Color::Yellow);
	menu.setPosition(650, 600);

	sf::Text sair("", fonte, 35);
	sair.setFillColor(sf::Color::White);
	sair.setPosition(671, 387);

	while (paginaFinal.isOpen())
		{
		   sf::Event event;
		   while (paginaFinal.pollEvent(event))
		   {
		      if (event.type == sf::Event::Closed)
		    	  paginaFinal.close();
		   }

		   if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left
		   && jogar.getGlobalBounds().contains(event.mouseButton.x,event.mouseButton.y))
		   {
			   paginaFinal.close();
		      //labirinto();
		   }

		   if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left
		   && menu.getGlobalBounds().contains(event.mouseButton.x,event.mouseButton.y))
		   {
			   paginaFinal.close();
		   	   //telaInicial();
		   }

		   if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left
		   && sair.getGlobalBounds().contains(event.mouseButton.x,event.mouseButton.y))
		   {
			   paginaFinal.close();
		   }

		   paginaFinal.clear();
		   paginaFinal.draw(bgFinal);
		   paginaFinal.draw(titulo);
		   paginaFinal.draw(jogar);
		   paginaFinal.draw(menu);
		   paginaFinal.draw(sair);
		   paginaFinal.display();
		}
}

void labirinto(sf::RenderWindow& window) {
	std::srand(static_cast<unsigned int>(std::time(nullptr)));
	sf::Sprite tela;
	sf::Sprite tela2;
	int tamLab = 5;

	bool isEnemyVisible = false;

	int vida1= 100, vida2= 100;

	std::vector<sf::Texture> huGreen;
	std::vector<sf::Texture> huRed;

	for(int c =0; c < 10 ; c++){
		sf::Texture texture;
		texture.loadFromFile("assets/hudGreen/barraVerde_"+  std::to_string(c + 1)  +".png");
		huGreen.push_back(texture);
	}

	for(int d =0; d < 10 ; d++){
			sf::Texture texture2;
			texture2.loadFromFile("assets/hudRed/barraVermelha_"+  std::to_string(d + 1)  +".png");
			huRed.push_back(texture2);
		}

	tela.setScale(0.1,0.1);
	tela.setPosition(820, 2*150);
	tela2.setScale(0.1,0.1);
	tela2.setPosition(820, 450);


	//sf::RenderWindow window(sf::VideoMode(1400, 800),
			//"Sponge Bob SquarePants MazeCraze");

	sf::Image icon;
	    if (!icon.loadFromFile("assets/logoJogo.png"))
	    {
	       std::cout <<"nao abre";
	    }
	    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

	sf::Texture playerTexture;
	if (!playerTexture.loadFromFile("assets/bobEsponja.png")) {
		std::cout << "nao abre" << std::endl;
		return;
	}
	sf::Texture playerTexture2;
	if (!playerTexture2.loadFromFile("assets/patrick.png")) {
		std::cout << "nao abre" << std::endl;
		return;
	}
	sf::Texture enemyTexture;
	if (!enemyTexture.loadFromFile("assets/serigueijo.png")) {
		std::cout << "nao abre" << std::endl;
		return;
	}
	sf::Texture background;
	if (!background.loadFromFile("assets/background2.png")) {
		std::cout << "nao abre" << std::endl;
		return;
	}
	sf::Texture enemyTexture2;
		if (!enemyTexture2.loadFromFile("assets/enemy.png")) {
		std::cout << "nao abre" << std::endl;
		return;
		}

	sf::Sprite backgroundSprite(background);

	sf::Texture textureIcon;
	if (!textureIcon.loadFromFile("assets/caraBob.png")) {
	}
	sf::Sprite iconBob(textureIcon);
	iconBob.setPosition(1180, 250);
	iconBob.setScale(0.2f, 0.2f);


	sf::Texture textureIcon2;
	if (!textureIcon2.loadFromFile("assets/caraPatrick.png")) {
	}
	sf::Sprite iconPatrick(textureIcon2);
	iconPatrick.setPosition(1180, 408);
	iconPatrick.setScale(0.2f, 0.2f);

	while (window.isOpen()) {
		Maze m(39 / tamLab, 39 / tamLab);
		m.Generate();
		Player player(2, 1, m);
		Player player2(2, 1, m);
		bool isMoving = false;
		int textureIndex1 = (vida1 / 10) -1;
		int textureIndex2 = (vida2 / 10) -1;

		sf::Texture& currentTexture1 = huGreen.back();
		sf::Texture& currentTexture2 = huRed.back();


		tela.setTexture(huGreen[textureIndex1]);
		tela2.setTexture(huRed[textureIndex2]);

		fflush(stdout);
		if (tamLab <= 3 && tamLab >=2) {
			Inimigo enemy(20 / tamLab, 20 / tamLab, m);


			float cellSize = std::min(
					static_cast<float>(window.getSize().x) / 800,
					static_cast<float>(window.getSize().y) / 800);

			while (true) {
				sf::Event event;
				while (window.pollEvent(event)) {
					if (event.type == sf::Event::Closed) {
						window.close();
						return;
					}
					MovePlayer(event, player, isMoving);
					MovePlayer2(event, player2, isMoving);
				}

				if (tamLab <= 3 && tamLab >=2) {
					isEnemyVisible = true;
				} else {
					isEnemyVisible = false;
				}

				if (CheckCollision(player, enemy)){
					vida1 -= 10;
					if (textureIndex1 > 0) {
					        textureIndex1--;
					        tela.setTexture(huGreen[textureIndex1]);
					    }
					if(textureIndex1 <= 0 || textureIndex2 <= 0){
							window.clear();
							perdeu(window);
							window.display();
						}
				}

				if(CheckCollision(player2, enemy)) {
					vida2 -=10;
					if (textureIndex2 > 0) {
					        textureIndex2--;
					        tela2.setTexture(huRed[textureIndex2]);

					    }
					if(textureIndex1 <= 0 || textureIndex2 <= 0){
							window.clear();
							perdeu(window);
							window.display();
						}

				}



				unsigned int saidaX = m.GetWidth() - 3;
				unsigned int saidaY = m.GetHeight() - 2;

				if (playerNaSaida(player, player2, saidaX, saidaY)) {
					tamLab--;
					break;
				}

				backgroundSprite.setPosition(0, 0);
				backgroundSprite.setScale(
						static_cast<float>(window.getSize().x)
								/ background.getSize().x,
						static_cast<float>(window.getSize().y)
								/ background.getSize().y);

				window.clear();
				window.draw(backgroundSprite);
				m.desenharQuadrados(window, m);

				float cellSize = std::min(
						static_cast<float>(window.getSize().x) / m.GetWidth(),
						static_cast<float>(window.getSize().y) / m.GetHeight());

				player.Draw(window, m, cellSize, playerTexture);
				player2.Draw(window, m, cellSize, playerTexture2);
				//if (isEnemyVisible) {
					enemy.MoveRandomly(tamLab);
					enemy.Draw(window, m, cellSize, enemyTexture);
				//}
				window.draw(tela);
				window.draw(tela2);
				window.draw(iconBob);
				window.draw(iconPatrick);
				window.display();
			}
		} else if (tamLab == 1){
			Inimigo enemy(20 / tamLab, 20 / tamLab, m);
			Inimigo enemy2(30 / tamLab, 30 / tamLab, m);

			float cellSize = std::min(
					static_cast<float>(window.getSize().x) / 800,
					static_cast<float>(window.getSize().y) / 800);

			while (true) {
				sf::Event event;
				while (window.pollEvent(event)) {
					if (event.type == sf::Event::Closed) {
						window.close();
						return;
					}
					MovePlayer(event, player, isMoving);
					MovePlayer2(event, player2, isMoving);
				}

				if (tamLab == 1) {
					isEnemyVisible = true;
				} else {
					isEnemyVisible = false;
				}

				if (CheckCollision(player, enemy)) {
					vida1 -= 10;
					if (textureIndex1 > 0) {
					        textureIndex1--;
					        tela.setTexture(huGreen[textureIndex1]);
					    }
					if(textureIndex1 <= 0 || textureIndex2 <= 0){
							window.clear();
							perdeu(window);
							window.display();
						}
				}

				if (CheckCollision(player2, enemy)) {
					vida2 -= 10;
					if (textureIndex2 > 0) {
					        textureIndex2--;
					        tela2.setTexture(huRed[textureIndex2]);
					    }
					if(textureIndex1 <= 0 || textureIndex2 <= 0){
							window.clear();
							perdeu(window);
							window.display();
						}
				}
				if (CheckCollision(player, enemy2)) {
					vida1 -= 10;
					if (textureIndex1 > 0) {
					        textureIndex1--;
					        tela.setTexture(huGreen[textureIndex1]);
					    }
					if(textureIndex1 <= 0 || textureIndex2 <= 0){
							window.clear();
							perdeu(window);
							window.display();
						}
				}

				if (CheckCollision(player2, enemy2)) {
					vida2 -= 10;
					if (textureIndex2 > 0) {
					        textureIndex2--;
					        tela2.setTexture(huRed[textureIndex2]);
					    }
					if(textureIndex1 <= 0 || textureIndex2 <= 0){
							window.clear();
							perdeu(window);
							window.display();
						}
				}

				unsigned int saidaX = m.GetWidth() - 3;
				unsigned int saidaY = m.GetHeight() - 2;

				if (playerNaSaida(player, player2, saidaX, saidaY)) {
					tamLab--;
					break;
				}

				backgroundSprite.setPosition(0, 0);
				backgroundSprite.setScale(
						static_cast<float>(window.getSize().x)
								/ background.getSize().x,
						static_cast<float>(window.getSize().y)
								/ background.getSize().y);

				window.clear();
				window.draw(backgroundSprite);
				m.desenharQuadrados(window, m);

				float cellSize = std::min(
						static_cast<float>(window.getSize().x) / m.GetWidth(),
						static_cast<float>(window.getSize().y) / m.GetHeight());

				player.Draw(window, m, cellSize, playerTexture);
				player2.Draw(window, m, cellSize, playerTexture2);

				//if (isEnemyVisible) {
					enemy.MoveRandomly(tamLab);
					enemy2.MoveRandomly(tamLab);
					enemy.Draw(window, m, cellSize, enemyTexture);
					enemy2.Draw(window, m, cellSize, enemyTexture2);
					//}
					window.draw(tela);
					window.draw(tela2);
					window.draw(iconBob);
					window.draw(iconPatrick);
				window.display();
			}
		} if(tamLab <= 5 && tamLab >=4){

			float cellSize = std::min(
					static_cast<float>(window.getSize().x) / 800,
					static_cast<float>(window.getSize().y) / 800);

			while (true) {
				sf::Event event;
				while (window.pollEvent(event)) {
					if (event.type == sf::Event::Closed) {
						window.close();
						return;
					}
					MovePlayer(event, player, isMoving);
					MovePlayer2(event, player2, isMoving);
				}

				unsigned int saidaX = m.GetWidth() - 3;
				unsigned int saidaY = m.GetHeight() - 2;

				if (playerNaSaida(player, player2, saidaX, saidaY)) {
					tamLab--;
					break;
				}


				backgroundSprite.setPosition(0, 0);
				backgroundSprite.setScale(
						static_cast<float>(window.getSize().x)
								/ background.getSize().x,
						static_cast<float>(window.getSize().y)
								/ background.getSize().y);

				window.clear();

				window.draw(backgroundSprite);
				window.draw(tela);
				window.draw(tela2);
				window.draw(iconBob);
				window.draw(iconPatrick);
				m.desenharQuadrados(window, m);

				float cellSize = std::min(
						static_cast<float>(window.getSize().x) / m.GetWidth(),
						static_cast<float>(window.getSize().y) / m.GetHeight());

				player.Draw(window, m, cellSize, playerTexture);
				player2.Draw(window, m, cellSize, playerTexture2);
				window.display();
			}

		}

	if(textureIndex1 <= 0 || textureIndex2 <= 0){
		window.clear();
		perdeu(window);
		window.display();
	}if(vida1 > 0 && vida2 > 0 && tamLab <1){
		window.close();
		telaFinal();
		window.display();

	}

	}
}

