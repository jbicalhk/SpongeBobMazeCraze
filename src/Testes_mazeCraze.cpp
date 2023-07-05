#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>
using namespace std;
using namespace sf;


void paginaCreditos()
{
    sf::RenderWindow window(sf::VideoMode(960, 540), "SFML App");

    sf::Texture backgroundTexture;
        if (!backgroundTexture.loadFromFile("assets/Creditos.png"))
        {
           cout<< "nao foi possivel carregar imagem pagina inicial";
        }

        Sprite background;
        background.setTexture(backgroundTexture);

        //Texture buttonTexture;
        //buttonTexture.loadFromFile("assets/JOGAR.png");
        //Sprite button(buttonTexture);
        //button.setPosition(344, 270);


        Font fonte;
        fonte.loadFromFile("assets/fonte.ttf");

        Text text;
        text.setFont(fonte);
        text.setString("Jogar");
        text.setCharacterSize(50);
		text.setFillColor(sf::Color::Black);
		text.setPosition(398, 275);

		Text titulo;
		titulo.setFont(fonte);
		titulo.setString("Maze Craze");
		titulo.setCharacterSize(80);
		titulo.setFillColor(sf::Color::Black);
		titulo.setPosition(290, 180);


    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::White);
        window.draw(background);
        //window.draw(button);
        //window.draw(titulo);
        //window.draw(text);
        //window.display();
    }

}



void paginaInicial()
{
    sf::RenderWindow window(sf::VideoMode(960, 540), "SFML App");

    sf::Texture backgroundTexture;
        if (!backgroundTexture.loadFromFile("assets/paginaInicial.png"))
        {
           cout<< "nao foi possivel carregar imagem pagina inicial";
        }

        Sprite background;
        background.setTexture(backgroundTexture);

        Texture buttonTexture;
        buttonTexture.loadFromFile("assets/JOGAR.png");
        Sprite button(buttonTexture);
        button.setPosition(344, 270);


        Font fonte;
        fonte.loadFromFile("assets/fonte.ttf");

        Text text;
        text.setFont(fonte);
        text.setString("Jogar");
        text.setCharacterSize(50);
		text.setFillColor(sf::Color::Black);
		text.setPosition(398, 275);

		Text titulo;
		titulo.setFont(fonte);
		titulo.setString("Maze Craze");
		titulo.setCharacterSize(80);
		titulo.setFillColor(sf::Color::Black);
		titulo.setPosition(290, 180);


    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::Black);
        window.draw(background);
        window.draw(button);
        window.draw(titulo);
        window.draw(text);
        window.display();
    }

}



