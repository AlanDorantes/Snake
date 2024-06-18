#pragma once
#include <list>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

class Snake : public sf::Drawable
{
public:
    std::list<sf::Sprite> m_cuerpo;
    std::list<sf::Sprite>::iterator m_cabeza;
    std::list<sf::Sprite>::iterator m_cola;
    std::list<sf::Sprite>::iterator m_pos;

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

    void Mover(const sf::Vector2f &direccion, const sf::Texture &texturaPrimeraPieza, const sf::Texture &textura)
    {
        // Change the current head's texture back to the regular texture
        m_cabeza->setTexture(textura); // Assuming you have access to the regular texture

        // Move the head
        m_cola->setPosition(m_cabeza->getPosition() + direccion);

        // Update head and tail iterators
        m_cabeza = m_cola;
        m_cola++;
        if (m_cola == m_cuerpo.end())
        {
            m_cola = m_cuerpo.begin();
        }

        // Change the new head's texture to the special texture
        m_cabeza->setTexture(texturaPrimeraPieza);
    }

    bool Colision(const sf::Sprite& objeto) const
    {
        // COLISION CON MUROS
        sf::FloatRect cabezaBounds = m_cabeza->getGlobalBounds();
        float wallLeft = 16.f;
        float wallRight = 640.f - 16.f; // Assuming the width of the window is 800 pixels
        float wallTop = 16.f;
        float wallBottom = 352.f - 16.f; // Assuming the height of the window is 600 pixels

        if (cabezaBounds.left < wallLeft || cabezaBounds.left + cabezaBounds.width > wallRight ||
            cabezaBounds.top < wallTop || cabezaBounds.top + cabezaBounds.height > wallBottom)
        {
            return true;
        }

        // COLISION CON OTROS OBJETOS
        if (m_cabeza->getGlobalBounds().intersects(objeto.getGlobalBounds()))
        {
            return true;
        }
        return false;
    }
        
    
    void Crecer(const sf::Vector2f &direccion, const sf::Texture &textura)
    {
        sf::Sprite nuevaPieza;
        nuevaPieza.setTexture(*(m_cuerpo.begin()->getTexture()));
        nuevaPieza.setPosition(m_cabeza->getPosition() + direccion);
        m_cabeza->setTexture(textura);
        m_cabeza = m_cuerpo.insert(++m_cabeza, nuevaPieza);
    }

    bool AutoColision() const
    {
        bool flag = false;

        for (auto piece = m_cuerpo.begin(); piece != m_cuerpo.end(); ++piece)
        {
            if (m_cabeza != piece)
            {
                flag = Colision(*piece);

                if (flag)
                {
                    break;
                }
            }
        }

        return flag;
    }

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override
    {
        for(auto &piece : m_cuerpo)
        {
            target.draw(piece);
        }
    }

};