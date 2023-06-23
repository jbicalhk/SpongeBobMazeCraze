//Generate and display a random maze.
#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>
#include <random>
#include "labirinto.hpp"
#include <SFML/Graphics.hpp>

void labirinto()
{
	Maze m(39*3,39*3);
		   m.Generate();

    // Create the SFML window
    sf::RenderWindow window(sf::VideoMode(800, 800), "Sponge Bob SquarePants MazeCraze");
    while (window.isOpen()){
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Clear the window
        window.clear();
         m.desenharQuadrados(window, m);

        // Display the content of the window
        window.display();
    }

}
int main(int argc, char **argv) {
	labirinto();
	return 0;
}
