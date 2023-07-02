#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>
#include <random>
#include <SFML/Graphics.hpp>


class Maze {
public:

   // Constructor.
   Maze(unsigned width, unsigned height) :
      m_width(width),
      m_height(height)
   {
      m_maze.resize(m_width * m_height);
   }

   // Generate a random maze.
   void Generate()
      {
         std::random_device rd;
         std::mt19937 gen(rd());

         Initialize();
         Carve(2, 2, gen);
         m_maze[m_width + 2] = true;
         m_maze[(m_height - 2) * m_width + m_width - 3] = true;
      }

   bool GetCellValue(unsigned int x, unsigned int y) const
       {
           return m_maze[y * m_width + x];
       }

   void desenharQuadrados(sf::RenderWindow& window, const Maze& maze)
   {
       // Obtenha o tamanho do labirinto
       unsigned int larguraLabirinto = maze.m_width;
       unsigned int alturaLabirinto = maze.m_height;

       // Calcule o tamanho proporcional do quadrado
       float tamanhoQuadrado = std::min(
           static_cast<float>(window.getSize().x) / larguraLabirinto,
           static_cast<float>(window.getSize().y) / alturaLabirinto
       );

       // Defina uma cor mudar para sprite
       sf::Color cor(255, 0, 0);

       // Percorra as células do labirinto
       for (unsigned int y = 0; y < alturaLabirinto; ++y)
       {
           for (unsigned int x = 0; x < larguraLabirinto; ++x)
           {
               // Verifique o valor da célula no labirinto
               if (!maze.GetCellValue(x, y))
               {
                   // Calcule as coordenadas x e y para o quadrado
                   float posX = static_cast<float>(x) * tamanhoQuadrado;
                   float posY = static_cast<float>(y) * tamanhoQuadrado;

                   // Crie um objeto de quadrado com base nas coordenadas e tamanho
                   sf::RectangleShape quadrado(sf::Vector2f(tamanhoQuadrado, tamanhoQuadrado));
                   quadrado.setPosition(posX, posY);
                   quadrado.setFillColor(cor);//mudar para sprite

                   // Desenhe o quadrado na janela
                   window.draw(quadrado);
               }
           }
       }
   }
   unsigned int GetWidth() const
       {
           return m_width;
       }

       unsigned int GetHeight() const
       {
           return m_height;
       }

private:

   /*Display the maze.
   std::ostream &Show(std::ostream &os) const
   {
      for(unsigned y = 0; y < m_height; y++) {
         for(unsigned x = 0; x < m_width; x++) {
            os << (m_maze[y * m_width + x] ? "  " : "# ");
         }
         os << "\n";
      }
      return os;
   }*/

   // Initialize the maze array.
   void Initialize()
   {
      std::fill(m_maze.begin(), m_maze.end(), false);
      for(unsigned x = 0; x < m_width; x++) {
         m_maze[x] = true;
         m_maze[(m_height - 1) * m_width + x] = true;
      }
      for(unsigned y = 0; y < m_height; y++) {
         m_maze[y * m_width] = true;
         m_maze[y * m_width + m_width - 1] = true;
      }
   }

   // Carve starting at x, y.
   void Carve(int x, int y, std::mt19937& gen)
   {
      m_maze[y * m_width + x] = true;
      std::vector<int> directions = {0, 1, 2, 3};
      std::shuffle(directions.begin(), directions.end(), gen);
      for (int i = 0; i < 4; i++) {
         const int dirs[] = {1, -1, 0, 0};
         const int dx = dirs[(directions[i] + 0) % 4];
         const int dy = dirs[(directions[i] + 2) % 4];
         const int x1 = x + dx, y1 = y + dy;
         const int x2 = x1 + dx, y2 = y1 + dy;
         if (!m_maze[y1 * m_width + x1] && !m_maze[y2 * m_width + x2]) {
            m_maze[y1 * m_width + x1] = true;
            Carve(x2, y2, gen);
         }
      }
   }


   const unsigned m_width;
   const unsigned m_height;
   std::vector<bool> m_maze;

   friend std::ostream &operator<<(std::ostream &os, const Maze &maze);


};


/* Maze insertion operator.
std::ostream &operator<<(std::ostream &os, const Maze &maze)
{
   return maze.Show(os);
}*/
