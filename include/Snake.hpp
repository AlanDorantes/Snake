#pragma once
#include <list>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

class Snake : public sf::Drawable
{
private:
    std::list<sf::Sprite> m_cuerpo;
    std::list<sf::Sprite>::iterator m_cabeza;
    std::list<sf::Sprite>::iterator m_cola;

public:
    Snake() : m_cuerpo(std::list<sf::Sprite>(4))
    {
        m_cabeza = --m_cuerpo.end();
        m_cola = m_cuerpo.begin();
    }
    ~Snake()
    {
    }

    void Init(const sf::Texture &textura, const sf::Texture &texturaPrimeraPieza)
    {
        float x = 16.f;
        for(auto &piece : m_cuerpo)
        {
            if (&piece == &(*--m_cuerpo.end())) 
            {
                piece.setTexture(texturaPrimeraPieza);
            } 
            else 
            {
                piece.setTexture(textura);
            }
            piece.setPosition({x, 16.f});
            x += 16.f;
        }
    }
    
    void Mover(const sf::Vector2f &direccion)
    {
        m_cola->setPosition(m_cabeza->getPosition() + direccion);
        m_cabeza = m_cola;
        m_cola++;

        if (m_cola == m_cuerpo.end())
        {
            m_cola = m_cuerpo.begin();
        }
    }

    bool Colision(const sf::Sprite& objeto) const
    {
        return objeto.getGlobalBounds().intersects(m_cabeza->getGlobalBounds());
    }
    
    void Crecer(const sf::Vector2f &direccion)
    {
        sf::Sprite nuevaPieza;
        nuevaPieza.setTexture(*(m_cuerpo.begin()->getTexture()));
        nuevaPieza.setPosition(m_cabeza->getPosition() + direccion);
        
        m_cabeza = m_cuerpo.insert(++m_cabeza, nuevaPieza);
    }

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override
    {
        for(auto &piece : m_cuerpo)
        {
            target.draw(piece);
        }
        
    }

};