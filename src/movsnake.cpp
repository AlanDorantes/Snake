#include <SFML/Graphics.hpp>

class Personaje {
public:
    Personaje(sf::Vector2f position, const std::string& texturePath) {
        if (!texture.loadFromFile(texturePath)) {
            // Manejar el error si no se puede cargar la textura
        }

        sprite.setTexture(texture);
        sprite.setPosition(position);
    }

    void setTexture(const std::string& texturePath) {
        if (!texture.loadFromFile(texturePath)) {
            // Manejar el error si no se puede cargar la textura
        }

        sprite.setTexture(texture);
    }

    void move(float offsetX, float offsetY) {
        sprite.move(offsetX, offsetY);
    }

    void draw(sf::RenderWindow& window) {
        window.draw(sprite);
    }

public:
    sf::Texture texture;
    sf::Sprite sprite;
};

double velocidad = 0.025;

int main(int argc, char const *argv[]) 
{
    sf::RenderWindow window(sf::VideoMode(1000, 600), "DinoChrome");

    Personaje character(sf::Vector2f(100, 500), "./assets/images/snake_cab_i.png");

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        int myConst;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            character.setTexture("./assets/images/snake_cab_i.png");
            myConst = 1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            character.setTexture("./assets/images/snake_cab_d.png");
            myConst = 2;
            character.move(velocidad, 0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            character.setTexture("./assets/images/snake_cab_ar.png");
            myConst = 3;
            character.move(0, velocidad * -1);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            character.setTexture("./assets/images/snake_cab_ab.png");
            character.move(0, velocidad);
            myConst = 4;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            window.close();
        }

        if (myConst == 1) {
            character.move(velocidad * -1, 0);
        }
        if (myConst == 2) {
            character.move(velocidad, 0);
        }
        if (myConst == 3) {
            character.move(0, velocidad * -1);
        }
        if (myConst == 4) {
            character.move(0, velocidad);
        }

        if (character.sprite.getPosition().x < 0 || 
            character.sprite.getPosition().x > 1000 || 
            character.sprite.getPosition().y < 0 || 
            character.sprite.getPosition().y > 600) {
            window.close();
        }
    

        window.clear();
        character.draw(window);
        window.display();
    }

    return 0;
}
