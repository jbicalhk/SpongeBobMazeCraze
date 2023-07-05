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
//#include "labirinto.hpp"

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

void labirinto() {
	std::srand(static_cast<unsigned int>(std::time(nullptr)));

	int tamLab = 5;


	bool isEnemyVisible = false;
	int vida1= 100, vida2= 100;

	std::vector<sf::Texture> textures1;
	std::vector<sf::Texture> textures2;

	for (int i = 1; i <= 10; i++)
	    {
	        sf::Texture textureGreen;
	        std::string texturePath1 = "assets/hudGreen/barraVerde_" + std::to_string(i) + ".png"; // Supondo que as texturas tenham nomes como "barra_0.png", "barra_1.png", etc.

	        if (!textureGreen.loadFromFile(texturePath1))
	        {
	           std::cout <<"nao abre";
	        }

	        textures1.push_back(textureGreen);
	    }

	sf::RenderWindow window(sf::VideoMode(1400, 800),
			"Sponge Bob SquarePants MazeCraze");
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

	while (window.isOpen()) {
		Maze m(39 / tamLab, 39 / tamLab);
		m.Generate();
		Player player(2, 1, m);
		Player player2(2, 1, m);
		bool isMoving = false;


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
					vida1 -= 5;
				}

				if(CheckCollision(player2, enemy)) {
					vida2 -=5;
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
				if (isEnemyVisible) {
					enemy.MoveRandomly(tamLab);
					enemy.Draw(window, m, cellSize, enemyTexture);
				}

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
					vida1 -= 5;
				}

				if (CheckCollision(player2, enemy)) {
					vida2 -= 5;
				}
				if (CheckCollision(player, enemy2)) {
					vida1 -= 5;
				}

				if (CheckCollision(player2, enemy2)) {
					vida2 -= 5;
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

				window.display();
			}
		} else {
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
				m.desenharQuadrados(window, m);

				float cellSize = std::min(
						static_cast<float>(window.getSize().x) / m.GetWidth(),
						static_cast<float>(window.getSize().y) / m.GetHeight());

				player.Draw(window, m, cellSize, playerTexture);
				player2.Draw(window, m, cellSize, playerTexture2);
				window.display();
			}
		}
	}
}

