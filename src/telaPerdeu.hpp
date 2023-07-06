
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

void perdeu(sf::RenderWindow& window) {
    //sf::RenderWindow window(sf::VideoMode(1400, 800), "Animar-CasoPerca");

    std::vector<sf::Texture> texturasPerdeu;
    std::vector<sf::Sprite> spritesPerdeu;
    std::vector<std::string> imagePathsPerdeu;
    imagePathsPerdeu = {"assets/perdeu/casoPerca1.png", "assets/perdeu/casoPerca2.png", "assets/perdeu/casoPerca3.png"};

    sf::Font fonte;
    fonte.loadFromFile("assets/fonte.ttf");
    	sf::Text perdeu("VOCE PERDEU!", fonte, 50);
    	perdeu.setFillColor(sf::Color::White);
    	perdeu.setPosition(520, 600);

    for (const auto& path : imagePathsPerdeu) {
        sf::Texture texture;
        if (!texture.loadFromFile(path)) {
            // Trate o erro caso não seja possível carregar a textura
        }
        texturasPerdeu.push_back(std::move(texture));
    }

    for (const auto& texture : texturasPerdeu) {
        sf::Sprite sprite(texture);
        // Aumentar o tamanho do sprite
        float escala = 2.0f; // Ajuste a escala para aumentar o tamanho
        sprite.setScale(escala, escala);
        spritesPerdeu.push_back(std::move(sprite));
    }

    // Posição na tela
    float x = (window.getSize().x - spritesPerdeu[0].getGlobalBounds().width) / 2.0f;
    float y = (window.getSize().y - spritesPerdeu[0].getGlobalBounds().height) / 2.0f;
    for (auto& sprite : spritesPerdeu) {
        sprite.setPosition(x, y);
    }

    int frameAtual = 0;
    float duracaoFrame = 0.4f; // Tempo dos frames
    float tempoPassado = 0.0f;

    sf::Clock tempo;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        float deltaTime = tempo.restart().asSeconds();
        // Atualizar a animação
        tempoPassado += deltaTime;
        if (tempoPassado >= duracaoFrame) {
            frameAtual = (frameAtual + 1) % spritesPerdeu.size(); // Ciclo dos frames
            tempoPassado = 0.0f;
        }

        window.clear();
        window.draw(spritesPerdeu[frameAtual]);
        window.draw(perdeu);
        window.display();
    }
}

