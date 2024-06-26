#pragma once

#include <memory>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/CircleShape.hpp>

#include <StateCtrl.hpp>
#include <MenuPr.hpp>
#include <Control.hpp>

class GameSnake
{
public:
    GameSnake() : m_control(std::make_shared<Control>())
    {
        // Crea una ventana de 640x352 pixeles
        m_control->m_window->create(sf::VideoMode(640, 352), "Snake Game", sf::Style::Close);
        m_control->m_states->Agregar(std::make_unique<MenuPr>(m_control));
    }

    ~GameSnake()
    {
    }

    void Correr()
    {

        sf::Clock clock;
        // Guarda el tiempo transcurrido desde la ultima actualizacion
        sf::Time timeSinceLastUpdate = sf::Time::Zero;

        while (m_control->m_window->isOpen())
        {
            // Reinicia el reloj y guarda el tiempo transcurrido
            timeSinceLastUpdate += clock.restart();

            // Controla que las actualizacion se realicen a 60fps
            while (timeSinceLastUpdate > timePerFrame)
            {
                timeSinceLastUpdate -= timePerFrame;

                // Cambio de estado antes de que se realice la actualizacion
                m_control->m_states->ProcesarCambioEstado();

                if (!m_control->m_states->ActivarVacio())
                {
                    // Toma el estado actual y le permite procesar entradas
                    m_control->m_states->DevolverActual()->ProcesarEntrada();
                    // El estado actual se actualiza
                    m_control->m_states->DevolverActual()->Actualizar(timePerFrame);
                    // Dibuja los sprites y textos en la ventana
                    m_control->m_states->DevolverActual()->Dibujar();
                }

                else
                {
                    m_control->m_window->close();
                }
            }
        }
    }

private:
    // Puntero compartido a la estructura de control
    std::shared_ptr<Control> m_control;
    // Variable para controlar el tiempo de actualizacion
    // 60 frames por segundo
    const sf::Time timePerFrame = sf::seconds(1.f / 60.f);
};