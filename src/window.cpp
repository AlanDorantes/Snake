#include <SFML/Graphics.hpp>
#include "Mapa.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Snake Game");

    Mapa mapa(80, 100);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        mapa.dibujar();
        window.display();
    }

    return 0;
}