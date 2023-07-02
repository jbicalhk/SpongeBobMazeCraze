#define _USE_MATH_DEFINES
#include <SFML/Graphics.hpp>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <iostream>
/*
enum class Direcao
{
    Cima,
    Baixo,
    Esquerda,
    Direita
};

class Personagens
{
public:
    std::vector<sf::Texture> frames;
    sf::Sprite personagem;
    sf::Vector2f position;
    sf::Vector2f velocity;
    float speed;
    int currentFrame;
    float accumulatedTime;

    Personagens(const std::string& prefix, const std::string& extension, int numFrames, const sf::Vector2f& initialPosition, float movementSpeed)
        : position(initialPosition), speed(movementSpeed), currentFrame(0)
    {
        for (int i = 1; i <= numFrames; ++i)
        {
            std::string filename = prefix + std::to_string(i) + extension;
            sf::Texture frame;
            if (!frame.loadFromFile(filename))
            {
                std::cerr << "Erro ao carregar a textura do frame " << i << std::endl;
                exit(-1);
            }
            frames.push_back(frame);
        }

        personagem.setTexture(frames[currentFrame]);
        personagem.setPosition(position);
    }

    void update(float elapsedTime, const sf::Time& frameDuration)
    {
        position += velocity;
        personagem.setPosition(position);

        // Acumula o tempo decorrido
        accumulatedTime += elapsedTime;

        // Verifica se a acumulação atingiu ou excedeu a duração do frame
        if (accumulatedTime >= frameDuration.asSeconds())
        {
            currentFrame = (currentFrame + 1) % frames.size();
            personagem.setTexture(frames[currentFrame]);

            // Reduz a acumulação subtraindo a duração do frame
            accumulatedTime -= frameDuration.asSeconds();
        }
    }

    void setVelocity(const sf::Vector2f& newVelocity)
    {
        velocity = newVelocity;
    }

    const sf::Sprite& getSprite() const
    {
        return personagem;
    }

    void mover(sf::Vector2f direction)
    {
        position += direction;
        personagem.setPosition(position);

        // Verificar e ajustar a rotação da sprite
        if (direction.x != 0 || direction.y != 0)
        {
            float angle = std::atan2(direction.y, direction.x) * 180.0f / M_PI;
            personagem.setRotation(angle);
        }
    }

    sf::Vector2f getPosicao() const
    {
        return position;
    }

    void desativar()
    {
        ativo = false;
    }

    bool estaAtivo() const
    {
        return ativo;
    }

    void desenhar(sf::RenderWindow& window)
    {
        if (ativo)
            window.draw(personagem);
    }

private:
    //sf::Vector2f position;
    bool ativo = true;
};

class Inimigo
{
public:
    Inimigo(sf::Vector2f position, Personagens* player) : pos(position), velocidade(2.0f), alvo(player)
    {
        if (!texture.loadFromFile("assets/plankton1.png"))
        {
            // Tratar erro ao carregar textura
        }

        sprite.setTexture(texture);
        sprite.setPosition(pos);
    }

    void mover()
    {
        if (!alvo->estaAtivo())
            return;

        sf::Vector2f direcao = alvo->getPosicao() - pos;

        float magnitude = std::sqrt(direcao.x * direcao.x + direcao.y * direcao.y);
        if (magnitude != 0.0f)
        {
            direcao /= magnitude;
        }

        pos += direcao * velocidade;
        sprite.setPosition(pos);

        // Verificar colisão com o personagem
        if (checkColisao())
        {
            alvo->desativar();
        }
    }

    void desenhar(sf::RenderWindow& window)
    {
        window.draw(sprite);
    }

private:
    sf::Vector2f pos;
    float velocidade;
    Personagens* alvo;
    sf::Texture texture;
    sf::Sprite sprite;

    bool checkColisao()
    {
        sf::FloatRect bounds1 = sprite.getGlobalBounds();
        sf::FloatRect bounds2 = alvo->personagem.getGlobalBounds();
        return bounds1.intersects(bounds2);
    }

   void respawn()
    {
        pos.x = static_cast<float>(rand() % GRID_WIDTH * GRID_SIZE);
        pos.y = static_cast<float>(rand() % GRID_HEIGHT * GRID_SIZE);
        sprite.setPosition(pos);
    }
};
int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Pac-Man");
    window.setFramerateLimit(60);

    std::srand(static_cast<unsigned int>(std::time(nullptr)));




    Personagens player("assets/patrick", ".png", 4, sf::Vector2f(100.0f, 100.0f), 3.0f);
    Personagens wasdSprites("assets/bobEsponja", ".png", 4, sf::Vector2f(100.0f, 100.0f), 3.0f);
    Inimigo inimigo(sf::Vector2f(200.0f, 200.0f), &player);
    //Personagens arrowSprites("assets/patrick", ".png", 4, sf::Vector2f(400.0f, 300.0f), 0.3f);
    sf::Clock clock;
    sf::Time elapsedTime;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        elapsedTime = clock.restart();

        sf::Vector2f direction;

        bool rightKeyPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Right);
        bool leftKeyPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
        bool upKeyPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Up);
        bool downKeyPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Down);

        if (rightKeyPressed)
            direction.x = player.speed;
        else if (leftKeyPressed)
            direction.x = -player.speed;

        if (upKeyPressed)
            direction.y = -player.speed;
        else if (downKeyPressed)
            direction.y = player.speed;

        player.setVelocity(direction);
        player.update(elapsedTime.asSeconds(), sf::seconds(0.1f));

        bool wKeyPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::W);
        bool aKeyPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
        bool sKeyPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::S);
        bool dKeyPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::D);

        sf::Vector2f wasdVelocity;
        if (dKeyPressed)
            wasdVelocity.x = wasdSprites.speed;
        else if (aKeyPressed)
            wasdVelocity.x = -wasdSprites.speed;

        if (wKeyPressed)
            wasdVelocity.y = -wasdSprites.speed;
        else if (sKeyPressed)
            wasdVelocity.y = wasdSprites.speed;

        wasdSprites.setVelocity(wasdVelocity);
        wasdSprites.update(elapsedTime.asSeconds(), sf::seconds(0.1f));

        inimigo.mover();

        window.clear();
       // window.draw(arrowSprites.getSprite());
        window.draw(wasdSprites.getSprite());
        window.draw(player.getSprite());
        inimigo.desenhar(window);
        window.display();
    }

    return 0;
}







enum class Direcao
{
    Cima,
    Baixo,
    Esquerda,
    Direita
};

class Personagens
{
public:
    std::vector<sf::Texture> frames;
    sf::Sprite personagem;
    sf::Vector2f position;
    sf::Vector2f velocity;
    float speed;
    int currentFrame;
    float accumulatedTime;

    Personagens(const std::string& prefix, const std::string& extension, int numFrames, const sf::Vector2f& initialPosition, float movementSpeed)
        : position(initialPosition), speed(movementSpeed), currentFrame(0)
    {
        for (int i = 1; i <= numFrames; ++i)
        {
            std::string filename = prefix + std::to_string(i) + extension;
            sf::Texture frame;
            if (!frame.loadFromFile(filename))
            {
                std::cerr << "Erro ao carregar a textura do frame " << i << std::endl;
                exit(-1);
            }
            frames.push_back(frame);
        }

        personagem.setTexture(frames[currentFrame]);
        personagem.setPosition(position);
    }

    void update(float elapsedTime, const sf::Time& frameDuration)
    {
        position += velocity;
        personagem.setPosition(position);

        // Acumula o tempo decorrido
        accumulatedTime += elapsedTime;

        // Verifica se a acumulação atingiu ou excedeu a duração do frame
        if (accumulatedTime >= frameDuration.asSeconds())
        {
            currentFrame = (currentFrame + 1) % frames.size();
            personagem.setTexture(frames[currentFrame]);

            // Reduz a acumulação subtraindo a duração do frame
            accumulatedTime -= frameDuration.asSeconds();
        }
    }

    void setVelocity(const sf::Vector2f& newVelocity)
    {
        velocity = newVelocity;
    }

    const sf::Sprite& getSprite() const
    {
        return personagem;
    }

    void mover(sf::Vector2f direction)
    {
        position += direction;
        personagem.setPosition(position);

        // Verificar e ajustar a rotação da sprite
        if (direction.x != 0 || direction.y != 0)
        {
            float angle = std::atan2(direction.y, direction.x) * 180.0f / 3.141592653589793238462643383279502884L;
            personagem.setRotation(angle);
        }
    }

    sf::Vector2f getPosicao() const
    {
        return position;
    }

    void desativar()
    {
        ativo = false;
    }

    bool estaAtivo() const
    {
        return ativo;
    }

    void desenhar(sf::RenderWindow& window)
    {
        if (ativo)
            window.draw(personagem);
    }

private:
    //sf::Vector2f position;
    bool ativo = true;
};

class Inimigo
{
public:
    Inimigo(sf::Vector2f position, Personagens* player) : pos(position), velocidade(2.0f), alvo(player)
    {
        if (!texture.loadFromFile("assets/plankton1.png"))
        {
            // Tratar erro ao carregar textura
        }

        sprite.setTexture(texture);
        sprite.setPosition(pos);
    }

    void mover()
    {
        if (!alvo->estaAtivo())
            return;

        sf::Vector2f direcao = alvo->getPosicao() - pos;

        float magnitude = std::sqrt(direcao.x * direcao.x + direcao.y * direcao.y);
        if (magnitude != 0.0f)
        {
            direcao /= magnitude;
        }

        pos += direcao * velocidade;
        sprite.setPosition(pos);

        // Verificar colisão com o personagem
        if (checkColisao())
        {
            alvo->desativar();
        }
    }

    void desenhar(sf::RenderWindow& window)
    {
        window.draw(sprite);
    }

private:
    sf::Vector2f pos;
    float velocidade;
    Personagens* alvo;
    sf::Texture texture;
    sf::Sprite sprite;

    bool checkColisao()
    {
        sf::FloatRect bounds1 = sprite.getGlobalBounds();
        sf::FloatRect bounds2 = alvo->personagem.getGlobalBounds();
        return bounds1.intersects(bounds2);
    }

   //void respawn()
    //{
      //  pos.x = static_cast<float>(rand() % GRID_WIDTH * GRID_SIZE);
        //pos.y = static_cast<float>(rand() % GRID_HEIGHT * GRID_SIZE);
        //sprite.setPosition(pos);
    //}
};
class Jogador : public Personagens {
public:
    Jogador(const std::string& prefix, const std::string& extension, int numFrames, const sf::Vector2f& initialPosition, float movementSpeed, const Maze& maze)
        : Personagens(prefix, extension, numFrames, initialPosition, movementSpeed),
        m_maze(maze)
    {
    }

    void mover(int dx, int dy)
    {
        int newX = static_cast<int>(position.x) + dx;
        int newY = static_cast<int>(position.y) + dy;

        // Verificar se a nova posição está dentro dos limites do labirinto
        if (newX >= 0 && newX < static_cast<int>(m_maze.GetWidth()) &&
            newY >= 0 && newY < static_cast<int>(m_maze.GetHeight()))
        {
            // Verificar se a célula na nova posição é vazia (false)
            if (m_maze.GetCellValue(newX, newY)) {
                position.x = static_cast<float>(newX);
                position.y = static_cast<float>(newY);
                personagem.setPosition(position);
            }
        }
    }

    void desenhar(sf::RenderWindow& window, float cellSize)
    {
        if (estaAtivo()) {
            // Calcular as coordenadas x e y para a posição do jogador
            float posX = position.x * cellSize;
            float posY = position.y * cellSize;

            // Calcular o tamanho do jogador com base no tamanho da célula
            float playerSize = cellSize * 0.8f; // Ajuste o fator de escala conforme necessário

            // Atualizar a posição e o tamanho do jogador
            personagem.setPosition(posX + (cellSize - playerSize) / 2.0f, posY + (cellSize - playerSize) / 2.0f);
            personagem.setScale(playerSize / frames[currentFrame].getSize().x, playerSize / frames[currentFrame].getSize().y);

            // Desenhar o jogador na janela
            window.draw(personagem);
        }
    }

private:
    const Maze& m_maze;
};


*/
