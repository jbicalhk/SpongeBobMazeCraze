//Generate and display a random maze.
#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>
#include <random>
#include "labirinto.hpp"
#include <SFML/Graphics.hpp>



/*int main1(int argc, char *argv[])
{
   Maze m(39/2,39/2);
   m.Generate();
   //std::cout << m;
   //m.array();
  return 0;
}*/


int main()
{
	Maze m(39/1,39/1);
	   m.Generate();
    // Defina o tamanho da janela
    sf::Vector2u tamanhoJanela(821, 821);

    // Crie uma instância da janela
    sf::RenderWindow janela(sf::VideoMode(tamanhoJanela.x, tamanhoJanela.y), "Exemplo de Vetor Booleano");

    // Defina o tamanho do quadrado
    float tamanhoQuadrado = 21.1f;

    // Exemplo de vetor booleano
    std::vector<bool> vetorBool = { true, false, true, true, false };

    // Loop principal da aplicação
    while (janela.isOpen())
    {
        // Verifique eventos na janela
        sf::Event evento;
        while (janela.pollEvent(evento))
        {
            if (evento.type == sf::Event::Closed)
                janela.close();
        }

        // Limpe a janela
        janela.clear();

        // Desenhe os quadrados
        m.desenharQuadrados(janela, m, tamanhoQuadrado);

        // Atualize a janela
        janela.display();
    }

    return 0;
}


#include <SFML/Graphics.hpp>

/*int main2()
{
    // Create the SFML window
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Circle");

    // Game loop
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Clear the window
        window.clear();

        // Draw the circle
        window.draw(circle);

        // Display the content of the window
        window.display();
    }

    return 0;
}
*/
