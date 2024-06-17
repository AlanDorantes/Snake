#pragma once

#include <memory>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/CircleShape.hpp>

#include <StateCtrl.hpp>
#include <AssetCtrl.hpp>
#include <MenuPr.hpp>

//Ayuda a identificar los recursos que se cargan en el juego, el ID de los recursos
enum AssetID
{   
    MAIN_FONT = 0,
    MAPA,
    MANZANA,
    MURO,
    SNAKE,
    SNAKE_HEAD_AB,
    SNAKE_HEAD_AR,
    SNAKE_HEAD_D,
    SNAKE_HEAD_I
};

//Estructura que contiene los controles de la aplicacion 
//Ventana, control de estados y control de recursos
struct Control
{
    std::unique_ptr<sf::RenderWindow> m_window;
    std::unique_ptr<Engine::StateCtrl> m_states;
    std::unique_ptr<Engine::AssetCtrl> m_assets;

    //Constructor que inicializa los punteros unicos
    Control()
    {
        m_window = std::make_unique<sf::RenderWindow>();
        m_states = std::make_unique<Engine::StateCtrl>();
        m_assets = std::make_unique<Engine::AssetCtrl>();
    }
};