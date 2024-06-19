#pragma once

#include <memory>

#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Event.hpp>

#include <GameSnake.hpp>
#include <Control.hpp>

#include <GamePlay.hpp>
#include <State.hpp>
#include <StateCtrl.hpp>
#include <Snake.hpp>

class GameOver : public Engine::State
{
private:
    // Puntero a la clase control
    std::shared_ptr<Control> m_control;

    sf::Text m_gameOverTitulo;
    sf::Text m_salir;
    sf::Sprite m_fondo;

    bool m_salirSelected;
    bool m_salirPressed;

public:
    GameOver(std::shared_ptr<Control> &control)
        : m_control(control), m_salirSelected(false),
          m_salirPressed(false)
    {
    }
    ~GameOver()
    {
    }

    void Init() override
    {
        // Carga fondo
        m_fondo.setTexture(m_control->m_assets->GetTexture(FONDO));

        // Configura el mensaje de game over
        m_gameOverTitulo.setFont(m_control->m_assets->GetFont(MAIN_FONT));
        m_gameOverTitulo.setString("GAME OVER");
        m_gameOverTitulo.setCharacterSize(80);
        m_gameOverTitulo.setFillColor(sf::Color::Red);
        m_gameOverTitulo.setStyle(sf::Text::Bold);
        m_gameOverTitulo.setOutlineColor(sf::Color::Black);
        m_gameOverTitulo.setOutlineThickness(3);
        m_gameOverTitulo.setOrigin(m_gameOverTitulo.getLocalBounds().width / 2, m_gameOverTitulo.getLocalBounds().height / 2);
        m_gameOverTitulo.setPosition(m_control->m_window->getSize().x / 2, m_control->m_window->getSize().y / 4);

        // Configura el boton salir
        m_salir.setFont(m_control->m_assets->GetFont(MAIN_FONT));
        m_salir.setString("EXIT");
        m_salir.setCharacterSize(40);
        m_salir.setFillColor(sf::Color::Red);
        m_salir.setOutlineThickness(2);
        m_salir.setOutlineColor(sf::Color::Black);
        m_salir.setOrigin(m_salir.getLocalBounds().width / 2, m_salir.getLocalBounds().height / 2);
        m_salir.setPosition(m_control->m_window->getSize().x / 2, m_control->m_window->getSize().y / 2 + 75.f);
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
                m_salirSelected = true;

                if (sf::Keyboard::Enter == event.key.code)
                {
                    m_salirPressed = true;
                }
                else
                {
                    m_salirPressed = false;
                }
            }
        }
    }

    void Update(sf::Time deltaTime) override
    {
        if (m_salirPressed)
        {
            m_control->m_window->close();
        }
    }

    void Draw() override
    {
        m_control->m_window->clear();
        m_control->m_window->draw(m_fondo);
        m_control->m_window->draw(m_gameOverTitulo);
        m_control->m_window->draw(m_salir);
        m_control->m_window->display();
    }
};
