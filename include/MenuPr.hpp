#pragma once

#include <memory>

#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Color.hpp>

#include <State.hpp>
#include <GameSnake.hpp>
#include <Control.hpp>

#include "GamePlay.hpp"

class MenuPr : public Engine::State
{
private:
    // Puntero a la clase control
    std::shared_ptr<Control> m_control;

    sf::Text m_titulo;
    sf::Text m_jugar;
    sf::Text m_salir;
    sf::Sprite m_fondo;

    bool m_jugarSelected;
    bool m_salirSelected;
    bool m_jugarPressed;
    bool m_salirPressed;

public:
    MenuPr(std::shared_ptr<Control> &control) : m_control(control), m_jugarSelected(true),
                                                m_salirSelected(false), m_jugarPressed(false),
                                                m_salirPressed(false)
    {
    }
    ~MenuPr()
    {
    }

    void Inicializar() override
    {
        // Carga la fuente
        m_control->m_assets->AgregarFuente(MAIN_FONT, "assets/fonts/RetroGaming.ttf");

        // Carga fondo
        m_control->m_assets->AgregarTextura(FONDO, "assets/images/fondo_grass.png", true);
        m_fondo.setTexture(m_control->m_assets->TomarTextura(FONDO));

        // Configura el titulo
        m_titulo.setFont(m_control->m_assets->TomarFuente(MAIN_FONT));
        m_titulo.setString("SNAKE GAME");
        m_titulo.setFillColor(sf::Color::White);
        m_titulo.setCharacterSize(65);
        m_titulo.setStyle(sf::Text::Bold);
        m_titulo.setLetterSpacing(1);
        m_titulo.setOutlineColor(sf::Color::Black);
        m_titulo.setOutlineThickness(3);
        m_titulo.setOrigin(m_titulo.getLocalBounds().width / 2, m_titulo.getLocalBounds().height / 2);
        m_titulo.setPosition(m_control->m_window->getSize().x / 2, m_control->m_window->getSize().y / 4);

        // Configura el boton jugar
        m_jugar.setFont(m_control->m_assets->TomarFuente(MAIN_FONT));
        m_jugar.setString("PLAY");
        m_jugar.setCharacterSize(40);
        m_jugar.setOutlineColor(sf::Color::Black);
        m_jugar.setOutlineThickness(2);
        m_jugar.setOrigin(m_jugar.getLocalBounds().width / 2, m_jugar.getLocalBounds().height / 2);
        m_jugar.setPosition(m_control->m_window->getSize().x / 2, m_control->m_window->getSize().y / 2 + 25.f);

        // Configura el boton salir
        m_salir.setFont(m_control->m_assets->TomarFuente(MAIN_FONT));
        m_salir.setString("EXIT");
        m_salir.setCharacterSize(40);
        m_salir.setOutlineColor(sf::Color::Black);
        m_salir.setOutlineThickness(2);
        m_salir.setOrigin(m_jugar.getLocalBounds().width / 2, m_jugar.getLocalBounds().height / 2);
        m_salir.setPosition(m_control->m_window->getSize().x / 2, m_control->m_window->getSize().y / 2 + 75.f);
    }

    void ProcesarEntrada() override
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
                switch (event.key.code)
                {
                case sf::Keyboard::Up:
                {
                    if (!m_jugarSelected)
                    {
                        m_jugarSelected = true;
                        m_salirSelected = false;
                    }
                    break;
                }
                case sf::Keyboard::Down:
                {
                    if (!m_salirSelected)
                    {
                        m_jugarSelected = false;
                        m_salirSelected = true;
                    }
                    break;
                }
                case sf::Keyboard::Return:
                {
                    m_jugarPressed = false;
                    m_salirPressed = false;
                    if (m_jugarSelected)
                    {
                        m_jugarPressed = true;
                    }
                    else
                    {
                        m_salirPressed = true;
                    }
                    break;
                }
                }
            }
        }
    }

    void Actualizar(sf::Time deltaTime) override
    {
        if (m_jugarSelected)
        {
            m_jugar.setFillColor(sf::Color::Red);
            m_salir.setFillColor(sf::Color::White);
        }
        else
        {
            m_jugar.setFillColor(sf::Color::White);
            m_salir.setFillColor(sf::Color::Red);
        }

        if (m_jugarPressed)
        {
            // Todo:
            m_control->m_states->Agregar(std::make_unique<GamePlay>(m_control), true);
        }
        else if (m_salirPressed)
        {
            m_control->m_window->close();
        }
    }

    void Dibujar() override
    {
        m_control->m_window->clear();
        m_control->m_window->draw(m_fondo);
        m_control->m_window->draw(m_titulo);
        m_control->m_window->draw(m_jugar);
        m_control->m_window->draw(m_salir);
        m_control->m_window->display();
    }
};