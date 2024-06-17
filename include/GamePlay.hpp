#pragma once

#include <array>
#include <memory>
#include <stdlib.h>
#include <time.h>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Window/Event.hpp>

#include "GameOver.hpp"
#include "GameSnake.hpp"
#include "State.hpp"
#include "Snake.hpp"


class GamePlay : public Engine::State
{
private:
    std::shared_ptr<Control> m_control;
    sf::Sprite m_mapa;
    sf::Sprite m_manzana;
    std::array<sf::Sprite, 4 > m_muro;
    Snake m_snake;

    sf::Vector2f m_snakeDireccion;
    sf::Time m_tiempoTranscurrido;

public:
    GamePlay(std::shared_ptr<Control> &control)
        : m_control(control), 
          m_snakeDireccion({16.f, 0.f}), 
          m_tiempoTranscurrido(sf::Time::Zero)
    {
        srand(time(nullptr));
    } 
    ~GamePlay() 
    {

    }

    void Init() override
    {
        m_control->m_assets->AddTexture(MAPA, "assets/images/mapa.png", true);
        m_control->m_assets->AddTexture(MANZANA, "assets/images/manzana.png");
        m_control->m_assets->AddTexture(MURO, "assets/images/muro.png", true);
        m_control->m_assets->AddTexture(SNAKE, "assets/images/snake.png");
        m_control->m_assets->AddTexture(SNAKE_HEAD_I, "assets/images/snake_cab_i.png");
        m_control->m_assets->AddTexture(SNAKE_HEAD_D, "assets/images/snake_cab_d.png");
        m_control->m_assets->AddTexture(SNAKE_HEAD_AR, "assets/images/snake_cab_ar.png");
        m_control->m_assets->AddTexture(SNAKE_HEAD_AB, "assets/images/snake_cab_ab.png");

        m_mapa.setTexture(m_control->m_assets->GetTexture(MAPA));
        m_mapa.setTextureRect(m_control->m_window->getViewport(m_control->m_window->getDefaultView()));

        for(auto &muro : m_muro)
        {
            muro.setTexture(m_control->m_assets->GetTexture(MURO));
        }

        m_muro[0].setTextureRect({0, 0, m_control->m_window->getSize().x, 16});
        m_muro[1].setTextureRect({0, 0, m_control->m_window->getSize().x, 16});
        m_muro[1].setPosition(0, m_control->m_window->getSize().y - 16);

        m_muro[2].setTextureRect({0, 0, 16, m_control->m_window->getSize().y});
        m_muro[3].setTextureRect({0, 0, 16, m_control->m_window->getSize().y});
        m_muro[3].setPosition(m_control->m_window->getSize().x - 16, 0);

        m_manzana.setTexture(m_control->m_assets->GetTexture(MANZANA));
        m_manzana.setPosition(m_control->m_window->getSize().x / 2, m_control->m_window->getSize().y / 2);

        m_snake.Init(m_control->m_assets->GetTexture(SNAKE), m_control->m_assets->GetTexture(SNAKE_HEAD_D));
        

    }
    void ProcessInput() override
    {
        sf::Event event;
        while (m_control->m_window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                m_control->m_window->close();
            }
            else if (event.type == sf::Event::KeyPressed)
            {
                sf::Vector2f newDireccion = m_snakeDireccion;
                switch (event.key.code)
                {
                case sf::Keyboard::Up:
                    newDireccion = {0.f, -16.f};
                    break;
                case sf::Keyboard::Down:
                    newDireccion = {0.f, 16.f};
                    break; 
                case sf::Keyboard::Left:    
                    newDireccion = {-16.f, 0.f};
                    break;
                case sf::Keyboard::Right:
                    newDireccion = {16.f, 0.f};
                    break;
                
                default:
                    break;
                }

                if(std::abs(m_snakeDireccion.x) != std::abs(newDireccion.x) || std::abs(m_snakeDireccion.y) != std::abs(newDireccion.y))
                {
                    m_snakeDireccion = newDireccion;
                }
            }
        }
    }
    void Update(sf::Time deltaTime) override
    {
        m_tiempoTranscurrido += deltaTime;

        if (m_tiempoTranscurrido.asSeconds() > .1)
        {
            bool colisionMuro = false;

            for(auto &muro : m_muro)
            {
                if(m_snake.Colision(muro))
                {
                    m_control->m_states->Add(std::make_unique<GameOver>(m_control), true);
                    break;
                }
            }

            if(m_snake.Colision(m_manzana))
            {
                m_snake.Crecer(m_snakeDireccion);

                int x = 0, y = 0;
                x = std::clamp<int>(rand() % m_control->m_window->getSize().x, 16, m_control->m_window->getSize().x - 2*16) / 16;
                y = std::clamp<int>(rand() % m_control->m_window->getSize().y, 16, m_control->m_window->getSize().y - 2*16) / 16;

                m_manzana.setPosition(x * 16, y * 16);
            }
            else
            {
                m_snake.Mover(m_snakeDireccion);
            }
            m_tiempoTranscurrido = sf::Time::Zero;
        }
    }
    void Draw() override
    {
        m_control->m_window->clear();
        m_control->m_window->draw(m_mapa);

        for(auto &muro : m_muro)
        {
            m_control->m_window->draw(muro);
        }

        m_control->m_window->draw(m_manzana);
        m_control->m_window->draw(m_snake);
        m_control->m_window->display();
    }
    void Pause() override
    {

    }
    void Start() override
    {

    }
    
};