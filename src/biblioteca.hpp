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


class Player {
public:
    Player(float x, float y, const Maze& maze) :
        m_x(x),
        m_y(y),
        m_maze(maze)
    {
    }

    void Move(float dx, float dy)
    {
        float newX = m_x + dx;
        float newY = m_y + dy;

        // Verificar se a nova posição está dentro dos limites do labirinto
        if (newX >= 0 && newX < static_cast<float>(m_maze.GetWidth()) &&
            newY >= 0 && newY < static_cast<float>(m_maze.GetHeight()))
        {
            // Verificar se a célula na nova posição é vazia (false)
            if (m_maze.GetCellValue(static_cast<float>(newX), static_cast<float>(newY))) {
                m_x = newX;
                m_y = newY;
            }
        }
    }


    void Draw(sf::RenderWindow& window, const Maze& maze, float cellSize, sf::Texture& playerTexture)
    {
        // Calcular as coordenadas x e y para a posição do jogador
        float posX = static_cast<float>(m_x) * cellSize;
        float posY = static_cast<float>(m_y) * cellSize;

        // Calcular o tamanho da sprite do jogador com base no tamanho da célula
        float playerSize = cellSize * 0.8f; // Ajuste o fator de escala conforme necessário

        // Criar um objeto sprite para representar o jogador
        sf::Sprite playerSprite;
        playerSprite.setTexture(playerTexture);
        playerSprite.setTextureRect(sf::IntRect(0, 0, playerTexture.getSize().x, playerTexture.getSize().y));
        playerSprite.setScale(playerSize / playerTexture.getSize().x, playerSize / playerTexture.getSize().y);
        playerSprite.setPosition(posX + (cellSize - playerSize) / 2.0f, posY + (cellSize - playerSize) / 2.0f);

        // Desenhar o jogador na janela
        window.draw(playerSprite);
    }


private:
    unsigned int m_x;
    unsigned int m_y;
    const Maze& m_maze;
};

void labirinto()
{
	std::srand(static_cast<unsigned int>(std::time(nullptr)));

	int width = 39 / 3;
	int height = 39 /3;
	Maze m(width,height);
	m.Generate();
	Player player(2, 1, m);

	sf::Texture playerTexture;
	if (!playerTexture.loadFromFile("assets/bobEsponja2.png")) {
	    std::cout << "nao abre";
	}

    // Create the SFML window
    sf::RenderWindow window(sf::VideoMode(800, 800), "Sponge Bob SquarePants MazeCraze");
    float cellSize = std::min(
            static_cast<float>(window.getSize().x) / 800,
            static_cast<float>(window.getSize().y) / 800);

    while (window.isOpen()){
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        if (event.key.code == sf::Keyboard::Up)
        player.Move(0, -1);
        else if (event.key.code == sf::Keyboard::Down)
        player.Move(0, 1);
        else if (event.key.code == sf::Keyboard::Left)
        player.Move(-1, 0);
        else if (event.key.code == sf::Keyboard::Right)
        player.Move(1, 0);

        window.clear();
        m.desenharQuadrados(window, m);
        float cellSize = std::min(
        static_cast<float>(window.getSize().x) / width,
        static_cast<float>(window.getSize().y) / height
                );
        player.Draw(window, m, cellSize, playerTexture);
        // Display the content of the window
        window.display();
    }

}
