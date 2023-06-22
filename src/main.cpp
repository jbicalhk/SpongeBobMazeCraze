//Generate and display a random maze.
#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>
#include <random>
#include "labirinto.hpp"
#include <SFML/Graphics.hpp>

/*void renderMaze(const Maze& maze, sf::RenderWindow& window)
{
   const unsigned int windowWidth = maze.getWidth() * 20;
   const unsigned int windowHeight = maze.getHeight() * 20;

   window.create(sf::VideoMode(windowWidth, windowHeight), "Maze");

   while (window.isOpen())
   {
      sf::Event event;
      while (window.pollEvent(event))
      {
         if (event.type == sf::Event::Closed)
            window.close();
      }

      window.clear();

      for (unsigned y = 0; y < maze.getHeight(); y++)
      {
         for (unsigned x = 0; x < maze.getWidth(); x++)
         {
            sf::RectangleShape cell(sf::Vector2f(20, 20));
            cell.setPosition(x * 20, y * 20);
            cell.setFillColor(maze.isCellEmpty(x, y) ? sf::Color::White : sf::Color::Black);

            window.draw(cell);
         }
      }

      window.display();
   }
}
*/
int main(int argc, char *argv[])
{
   Maze m(39/5,39/5);
   m.Generate();
   std::cout << m;
   //m.array();
  return 0;
}
