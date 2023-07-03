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

int tamLab = 2;

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

	/*void PrintCurrentCell() {
		int x = static_cast<int>(m_x);
		int y = static_cast<int>(m_y);

		std::cout << "O player está na célula (" << x << ", " << y << ")"
				<< std::endl;
	}*/

	void SetPosition(unsigned int x, unsigned int y) {
		m_x = x;
		m_y = y;
	}

	/*void CheckExitCell(Player &player, const Maze &maze,
			sf::RenderWindow &window, sf::RenderWindow &window2) {
		unsigned int exitX = maze.GetWidth() - 3;
		unsigned int exitY = maze.GetHeight() - 2;

		if (player.GetX() == exitX && player.GetY() == exitY) {
			window.clear();
			window.display();

			window2.clear();
			Maze newMaze(39/4, 39/4); // Substitua NEW_WIDTH e NEW_HEIGHT pelas novas dimensões desejadas
			newMaze.Generate();
			newMaze.desenharQuadrados(window2, newMaze);
			window2.display();

			player.SetPosition(2, 1); // Movendo o jogador de volta para (2, 1)
		}
	}*/

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

	void MoveRandomly() {
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

private:
	unsigned int m_x;
	unsigned int m_y;
	const Maze &m_maze;
};

void labirinto() {
	std::srand(static_cast<unsigned int>(std::time(nullptr)));


	int width = 39 / tamLab;
	int height = 39 / tamLab;
	Maze m(width, height);
	m.Generate();
	Player player(2, 1, m);
	Inimigo enemy(20/tamLab, 20/ tamLab, m);

	sf::Texture playerTexture;
	if (!playerTexture.loadFromFile("assets/bobEsponja1.png")) {
		std::cout << "nao abre";
	}
	sf::Texture enemyTexture;
	if (!enemyTexture.loadFromFile("assets/plankton1.png")) {
		std::cout << "nao abre";
	}

	// Create the SFML window
	sf::RenderWindow window(sf::VideoMode(800, 800), "Sponge Bob SquarePants MazeCraze");

	float cellSize = std::min(static_cast<float>(window.getSize().x) / 800,
	static_cast<float>(window.getSize().y) / 800);
	bool isMoving = false;

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}


		if (event.type == sf::Event::KeyPressed) {
			// Verifica qual tecla foi pressionada
			if (event.key.code == sf::Keyboard::Up) {
				isMoving = true;
				player.Move(0, -1); // Movimento para cima
			} else if (event.key.code == sf::Keyboard::Down) {
				isMoving = true;
				player.Move(0, 1); // Movimento para baixo
			} else if (event.key.code == sf::Keyboard::Left) {
				isMoving = true;
				player.Move(-1, 0); // Movimento para a esquerda
			} else if (event.key.code == sf::Keyboard::Right) {
				isMoving = true;
				player.Move(1, 0); // Movimento para a direita
			}


		} else if (event.type == sf::Event::KeyReleased) {
			// Verifica qual tecla foi liberada
			if (event.key.code == sf::Keyboard::Up
					|| event.key.code == sf::Keyboard::Down
					|| event.key.code == sf::Keyboard::Left
					|| event.key.code == sf::Keyboard::Right) {
				isMoving = false; // Parar o movimento
			}
		}
		if (isMoving) {
			// Atraso entre os movimentos (por exemplo, 200 milissegundos)
			sf::sleep(sf::milliseconds(115));
		}
		//player.PrintCurrentCell();
		enemy.MoveRandomly();

		window.clear();
		m.desenharQuadrados(window, m);

		float cellSize = std::min(
		static_cast<float>(window.getSize().x) / width,
		static_cast<float>(window.getSize().y) / height);


		player.Draw(window, m, cellSize, playerTexture);
		enemy.Draw(window, m, cellSize, enemyTexture);

		window.display();
	}


}
