#pragma once
#include <list>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

class Snake
{
private:
    std::list<sf::Sprite> cuerpo;
    std::list<sf::Sprite>::iterator cabeza;
    std::list<sf::Sprite>::iterator cola;

public:
    Snake() : cuerpo(std::list<sf::Sprite>(1))
    {
        cabeza = --cuerpo.end();
        cola = cuerpo.begin();
    }
    ~Snake()
    {
    }

    void Ini(const sf::Texture &textura)
    {
        float x = 16.f;
        for(auto &piece : cuerpo)
        {
            piece.setTexture(textura);
            piece.setPosition(x, 16.f);
            x += 16.f;
        }
    }
    void Mover(const sf::Vector2f &direccion)
    {

    }
    
    void Crecer(const sf::Vector2f &direccion)
    {

    }
    void Dibujar(sf::RenderTarget &target, sf::RenderStates states) const
    {
        for(auto &piece : cuerpo)
        {
            target.draw(piece);
        }
        
    }

};