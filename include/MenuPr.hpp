#pragma once

#include <memory>

#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Event.hpp>

#include <State.hpp>
#include <GameSnake.hpp>
#include <Control.hpp>

class MenuPr : public Engine::State
{
    private:
        //Puntero a la clase control
        std::shared_ptr<Control> m_control;

        sf::Text m_titulo;
        sf::Text m_jugar;
        sf::Text m_salir;

        bool m_jugarSelected;
        bool m_salirSelected;
        bool m_jugarPressed;
        bool m_salirPressed;

    public:
        MenuPr(std::shared_ptr<Control> &control) : 
        m_control(control) , m_jugarSelected(true), 
        m_salirSelected(false), m_jugarPressed(false), 
        m_salirPressed(false)
        {
            
        }
        ~MenuPr()
        {
        }
        
        void Init() override
        {
            //Carga la fuente
            m_control->m_assets->AddFont(MAIN_FONT, "assets/fonts/RetroGaming.ttf");

            //Configura el titulo
            m_titulo.setFont(m_control->m_assets->GetFont(MAIN_FONT));
            m_titulo.setString("SNAKE GAME");
            m_titulo.setCharacterSize(50);
            m_titulo.setOrigin(m_titulo.getLocalBounds().width / 2, m_titulo.getLocalBounds().height / 2);
            m_titulo.setPosition(m_control->m_window->getSize().x / 2, m_control->m_window->getSize().y / 4);


            //Configura el boton jugar
            m_jugar.setFont(m_control->m_assets->GetFont(MAIN_FONT));
            m_jugar.setString("PLAY");
            m_jugar.setOrigin(m_jugar.getLocalBounds().width / 2, m_jugar.getLocalBounds().height / 2);
            m_jugar.setPosition(m_control->m_window->getSize().x / 2, m_control->m_window->getSize().y / 2 + 25.f);

            //Configura el boton salir
            m_salir.setFont(m_control->m_assets->GetFont(MAIN_FONT));
            m_salir.setString("EXIT");
            m_salir.setOrigin(m_jugar.getLocalBounds().width / 2, m_jugar.getLocalBounds().height / 2);
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
                else if(event.type == sf::Event::KeyPressed)
                {
                    switch (event.key.code)
                    {
                        case sf::Keyboard::Up:    
                        {
                            if(!m_jugarSelected)
                            {
                                m_jugarSelected = true;
                                m_salirSelected = false;
                            }
                            break;
                        }
                        case sf::Keyboard::Down:    
                        {
                            if(!m_salirSelected)
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
                            if(m_jugarSelected)
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

        void Update(sf::Time deltaTime) override
        {
            if(m_jugarSelected)
            {
                m_jugar.setFillColor(sf::Color::Red);
                m_salir.setFillColor(sf::Color::White);
            }
            else
            {
                m_jugar.setFillColor(sf::Color::White);
                m_salir.setFillColor(sf::Color::Red);
            }

            if(m_jugarPressed)
            {
                // Todo:
                // Go to Play State
            }
            else if(m_salirPressed)
            {
                m_control->m_window->close();
            }
        }

        void Draw() override
        {
            m_control->m_window->clear();
            m_control->m_window->draw(m_titulo);
            m_control->m_window->draw(m_jugar);
            m_control->m_window->draw(m_salir);
            m_control->m_window->display();
        }
};