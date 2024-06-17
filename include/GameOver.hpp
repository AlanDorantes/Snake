#pragma once

#include <memory>

#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Event.hpp>


#include <GameSnake.hpp>
#include <Control.hpp>

#include <GamePlay.hpp>
#include <State.hpp>
#include <StateCtrl.hpp>

class GameOver : public Engine::State
{
    private:
        //Puntero a la clase control
        std::shared_ptr<Control> m_control;

        sf::Text m_gameOverTitulo;
        sf::Text m_reintentar;
        sf::Text m_salir;

        bool m_reintentarSelected;
        bool m_salirSelected;
        bool m_reintentarPressed;
        bool m_salirPressed;

    public:
        GameOver(std::shared_ptr<Control> &control) 
        : m_control(control) , m_reintentarSelected(true), 
          m_reintentarPressed(false), m_salirSelected(false), 
          m_salirPressed(false)
        {
        }
        ~GameOver()
        {
        }

        void Init() override
        {
            //Configura el mensaje de game over
            m_gameOverTitulo.setFont(m_control->m_assets->GetFont(MAIN_FONT));
            m_gameOverTitulo.setString("GAME OVER");
            m_gameOverTitulo.setCharacterSize(50);
            m_gameOverTitulo.setOrigin(m_gameOverTitulo.getLocalBounds().width / 2, m_gameOverTitulo.getLocalBounds().height / 2);
            m_gameOverTitulo.setPosition(m_control->m_window->getSize().x / 2, m_control->m_window->getSize().y / 4);


            //Configura el boton reintentar
            m_reintentar.setFont(m_control->m_assets->GetFont(MAIN_FONT));
            m_reintentar.setString("REINTENTAR");
            m_reintentar.setOrigin(m_reintentar.getLocalBounds().width / 2, m_reintentar.getLocalBounds().height / 2);
            m_reintentar.setPosition(m_control->m_window->getSize().x / 2, m_control->m_window->getSize().y / 2 + 25.f);

            //Configura el boton salir
            m_salir.setFont(m_control->m_assets->GetFont(MAIN_FONT));
            m_salir.setString("EXIT");
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
                else if(event.type == sf::Event::KeyPressed)
                {
                    switch (event.key.code)
                    {
                        case sf::Keyboard::Up:    
                        {
                            if(!m_reintentarSelected)
                            {
                                m_reintentarSelected = true;
                                m_salirSelected = false;
                            }
                            break;
                        }
                        case sf::Keyboard::Down:    
                        {
                            if(!m_salirSelected)
                            {
                                m_reintentarSelected = false;
                                m_salirSelected = true;
                            }
                            break;
                        }
                        case sf::Keyboard::Return:    
                        {
                            m_reintentarPressed = false;
                            m_salirPressed = false;
                            if(m_reintentarSelected)
                            {
                                m_reintentarPressed = true;
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
            if(m_reintentarSelected)
            {
                m_reintentar.setFillColor(sf::Color::Red);
                m_salir.setFillColor(sf::Color::White);
            }
            else
            {
                m_reintentar.setFillColor(sf::Color::White);
                m_salir.setFillColor(sf::Color::Red);
            }

            if(m_reintentarPressed)
            {
            /////////////
            }
            else if(m_salirPressed)
            {
                m_control->m_window->close();
            }
        }

        void Draw() override
        {
            m_control->m_window->clear();
            m_control->m_window->draw(m_gameOverTitulo);
            m_control->m_window->draw(m_reintentar);
            m_control->m_window->draw(m_salir);
            m_control->m_window->display();
        }
};

