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
    GamePlay(std::shared_ptr<Control> &control);
    ~GamePlay() {}

        void Init() override;
        void ProcessInput() override;
        void Update(sf::Time deltaTime) override;
        void Draw() override;
        void Pause() override;
        void Start() override;
    
};