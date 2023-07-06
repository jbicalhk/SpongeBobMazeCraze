//Generate and display a random maze.
#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>
#include <random>
#include "labirinto.hpp"
#include <SFML/Graphics.hpp>
#include "biblioteca.hpp"
#include <SFML/Audio.hpp>


void menuRegras() {
	sf::RenderWindow regrasJogo(sf::VideoMode(1400, 800), "Maze Craze");

	sf::Image header;
	header.loadFromFile("assets/logoJogo.png");
	regrasJogo.setIcon(header.getSize().x, header.getSize().y,
			header.getPixelsPtr());

	sf::Texture bgRulesTex;
	bgRulesTex.loadFromFile("assets/menuRegras.png");
	sf::Sprite bgRules(bgRulesTex);
	float escalaX = regrasJogo.getSize().x
			/ static_cast<float>(bgRulesTex.getSize().x);
	float escalaY = regrasJogo.getSize().y
			/ static_cast<float>(bgRulesTex.getSize().y);
	bgRules.setScale(escalaX, escalaY);

	sf::Font fonte;
	fonte.loadFromFile("assets/fonte.ttf");
	sf::Text jogar("OK", fonte, 30);
	jogar.setFillColor(sf::Color::Black);
	jogar.setPosition(683, 692);

	while (regrasJogo.isOpen()) {
		sf::Event event;
		while (regrasJogo.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				regrasJogo.close();
		}

		if (event.type == sf::Event::MouseButtonPressed
				&& event.mouseButton.button == sf::Mouse::Left
				&& jogar.getGlobalBounds().contains(event.mouseButton.x,
						event.mouseButton.y)) {
			regrasJogo.close();

		}

		regrasJogo.clear();
		regrasJogo.draw(bgRules);
		regrasJogo.draw(jogar);
		regrasJogo.display();
	}
}

int main(int argc, char **argv) {
	sf::RenderWindow paginaInicial(sf::VideoMode(1400, 800),
			"Sponge Bob SquarePants MazeCraze");

	sf::Image header;
	header.loadFromFile("assets/logoJogo.png");
	paginaInicial.setIcon(header.getSize().x, header.getSize().y,
			header.getPixelsPtr());

	sf::Texture backgroundTexture;
	backgroundTexture.loadFromFile("assets/backgroundInicial.png");
	sf::Sprite background(backgroundTexture);
	float escalaX = paginaInicial.getSize().x
			/ static_cast<float>(backgroundTexture.getSize().x);
	float escalaY = paginaInicial.getSize().y
			/ static_cast<float>(backgroundTexture.getSize().y);
	background.setScale(escalaX, escalaY);

	sf::Texture buttonMenuTex;
	buttonMenuTex.loadFromFile("assets/jogar.png");

	sf::Font fonte;
	fonte.loadFromFile("assets/fonte.ttf");
	sf::Text titulo("Maze Craze", fonte, 110);
	titulo.setFillColor(sf::Color::Black);
	titulo.setPosition(360, 132 * 1.5 + 20);

	sf::Text play("Jogar", fonte, 50);
	play.setFillColor(sf::Color::Black);
	play.setPosition(398 * 1.458333f + 10, 265 * 1.4814814);
	sf::Sprite button(buttonMenuTex);
	button.setPosition(370 * 1.458333f, 260 * 1.4814814);

	sf::Text rules("Como Jogar", fonte, 35);
	rules.setFillColor(sf::Color::Black);
	rules.setPosition(380 * 1.458333f, 350 * 1.4814814);
	sf::Sprite buttonRules(buttonMenuTex);
	buttonRules.setPosition(370 * 1.458333f, 340 * 1.4814814);

	sf::Text impossible("Fase Impossivel", fonte, 28);
	impossible.setFillColor(sf::Color::Black);
	impossible.setPosition(380 * 1.458333f, 428 * 1.4814814);
	sf::Sprite buttonImp(buttonMenuTex);
	buttonImp.setPosition(370 * 1.458333f, 415 * 1.4814814);

	sf::Music bolha;
	if (!bolha.openFromFile("assets/somBolha.wav")) {
		std::cout << "nao abre a musica";
	}

	sf::Music music;
	if (!music.openFromFile("assets/trilhaSonora.wav")) {
		std::cout << "nao abre a musica";
	}
	music.setVolume(75.0f);

	std::vector<sf::Texture> texturasPaginaInicial;
	std::vector<sf::Sprite> spritesPaginaInicial;
	std::vector<std::string> imagePathsPaginaInicial = {
			"assets/telaInicialBob1.png", "assets/telaInicialBob2.png",
			"assets/telaInicialBob3.png", "assets/telaInicialBob4.png",
			"assets/telaInicialBob5.png" };

	for (const auto &path : imagePathsPaginaInicial) {
		sf::Texture texture;
		texture.loadFromFile(path);
		texturasPaginaInicial.push_back(std::move(texture));
	}

	for (const auto &texture : texturasPaginaInicial) {
		sf::Sprite sprite(texture);
		float escala = 0.5f;
		sprite.setScale(escala, escala);
		spritesPaginaInicial.push_back(std::move(sprite));
	}

	float x = 695.0f * 1.5, y = 240.0f * 1.5;
	for (auto &sprite : spritesPaginaInicial) {
		sprite.setPosition(x, y);
	}

	sf::Clock tempo;
	int frameAtual = 0;
	float duracaoFrame = 0.3f, tempoPassado = 0.0f;

	while (paginaInicial.isOpen()) {
		sf::Event event;
		while (paginaInicial.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				paginaInicial.close();
		}
		music.setLoop(true);

		float deltaTime = tempo.restart().asSeconds();
		tempoPassado += deltaTime;
		if (tempoPassado >= duracaoFrame) {
			frameAtual = (frameAtual + 1) % spritesPaginaInicial.size();
			tempoPassado = 0.0f;
		}

		if (event.type == sf::Event::MouseButtonPressed
				&& event.mouseButton.button == sf::Mouse::Left
				&& play.getGlobalBounds().contains(event.mouseButton.x,
						event.mouseButton.y)) {
			music.play();
			bolha.play();
			paginaInicial.clear();
			labirinto(paginaInicial);
			paginaInicial.display();
		}

		if (event.type == sf::Event::MouseButtonPressed
				&& event.mouseButton.button == sf::Mouse::Left
				&& rules.getGlobalBounds().contains(event.mouseButton.x,
						event.mouseButton.y)) {
			bolha.play();
			paginaInicial.clear();
			menuRegras();
			paginaInicial.display();
		}

		if (event.type == sf::Event::MouseButtonPressed
				&& event.mouseButton.button == sf::Mouse::Left
				&& impossible.getGlobalBounds().contains(event.mouseButton.x,
						event.mouseButton.y)) {
			bolha.play();
			music.play();
			paginaInicial.clear();
			labirintoImpossivel(paginaInicial);
			paginaInicial.display();
		}

		paginaInicial.clear();
		paginaInicial.draw(background);
		paginaInicial.draw(button);
		paginaInicial.draw(buttonRules);
		paginaInicial.draw(buttonImp);
		paginaInicial.draw(titulo);
		paginaInicial.draw(play);
		paginaInicial.draw(rules);
		paginaInicial.draw(impossible);
		paginaInicial.draw(spritesPaginaInicial[frameAtual]);
		paginaInicial.display();
	}
	return 0;
}

