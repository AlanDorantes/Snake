#pragma once

#include <array>
#include <memory>

#include <SFML/Graphics/Sprite.hpp>

#include "GameSnake.hpp"
#include "State.hpp"

class GamePlay : public Engine::State
{
private:
    std::shared_ptr<Control> m_control;
    sf::Sprite m_mapa;
    sf::Sprite m_manzana;
    std::array<sf::Sprite, 4 > m_muro;

    //todo
    //added snake

public:
    GamePlay(std::shared_ptr<Control> &control)
        : m_control(control)
    {
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

        m_mapa.setTexture(m_control->m_assets->GetTexture(MAPA));
        m_mapa.setTextureRect(m_control->m_window->getViewport(m_control->m_window->getDefaultView()));
    }
    void ProcessInput() override
    {

    }
    void Update(sf::Time deltaTime) override
    {

    }
    void Draw() override
    {
        m_control->m_window->clear();
        m_control->m_window->draw(m_mapa);
        m_control->m_window->display();
    }
    void Pause() override
    {

    }
    void Start() override
    {

    }
    
};