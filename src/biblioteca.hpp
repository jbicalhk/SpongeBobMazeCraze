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

int tamLab = 3;

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

	float GetX() const {
			return m_x;
		}

		float GetY() const {
			return m_y;
		}

private:
	unsigned int m_x;
	unsigned int m_y;
	const Maze &m_maze;
};

void MovePlayer(const sf::Event& event, Player& player, bool& isMoving) {
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
        sf::sleep(sf::milliseconds(115));
    } else if (event.type == sf::Event::KeyReleased) {

        if (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::Down ||
            event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::Right) {
            isMoving = false;

        }
    }
}

	bool CheckCollision(const Player &player, const Inimigo & inimigo){
	float playerX = player.GetX();
	float playerY = player.GetY();
	float inimigoX = inimigo.GetX();
	float inimigoY = inimigo.GetY();

		if(playerX == inimigoX && playerY == inimigoY){
			return true;
		}
		return false;
	}

	bool playerNaSaida(const Player &player, unsigned int saidaX, unsigned int saidaY){
		if (player.GetX() == saidaX && player.GetY() == saidaY) {
		    return true;
		} else {
		   return false;
		}

	}

void labirinto() {
	std::srand(static_cast<unsigned int>(std::time(nullptr)));


	int width = 39 / tamLab;
	int height = 39 / tamLab;
	Maze m(width, height);
	m.Generate();
	Player player(2, 1, m);
	Inimigo enemy(20/tamLab, 20/ tamLab, m);
	bool isMoving = false;


	sf::Texture playerTexture;
	if (!playerTexture.loadFromFile("assets/bobEsponja.png")) {
		std::cout << "nao abre";
	}
	sf::Texture enemyTexture;
	if (!enemyTexture.loadFromFile("assets/enemy1.png")) {
		std::cout << "nao abre";
	}

	sf::Texture background;
	if (!background.loadFromFile("assets/background2.png")) {
		std::cout << "nao abre";
	}
	sf::Sprite backgroundSprite(background);


	sf::RenderWindow window(sf::VideoMode(800, 800), "Sponge Bob SquarePants MazeCraze");

	float cellSize = std::min(static_cast<float>(window.getSize().x) / 800,
	static_cast<float>(window.getSize().y) / 800);


	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}

		if (event.type == sf::Event::KeyPressed) {
			MovePlayer(event, player, isMoving);
		}

		enemy.MoveRandomly();// move randomicamente o inimigo enemy

		if(CheckCollision(player, enemy)){
		std::cout << "bateu";
		}

		unsigned int saidaX = m.GetWidth() - 3;
		unsigned int saidaY = m.GetHeight() - 2;

		if(playerNaSaida(player, saidaX, saidaY)){
			std::cout <<"oi";
		}

		//player.PrintCurrentCell();
		//std::cout << "A célula de saída está na posição (" << saidaX << ", " << saidaY << ")" << std::endl;


		backgroundSprite.setPosition(0, 0);
		backgroundSprite.setScale(
		static_cast<float>(window.getSize().x) / background.getSize().x,
		static_cast<float>(window.getSize().y) / background.getSize().y);

		window.clear();
		window.draw(backgroundSprite);
		m.desenharQuadrados(window, m);


		float cellSize = std::min(
		static_cast<float>(window.getSize().x) / width,
		static_cast<float>(window.getSize().y) / height);


		player.Draw(window, m, cellSize, playerTexture);
		enemy.Draw(window, m, cellSize, enemyTexture);

		window.display();
	}


}
