#include "GamePlay.hpp"

GamePlay::GamePlay(std::shared_ptr<Control> &control)
    : m_control(control)
{
}
GamePlay:: ~GamePlay()
{
}

void GamePlay::Init()
{
    m_control->m_assets->AddTexture(MAPA, "assets/textures/mapa.png", true);
    m_control->m_assets->AddTexture(MANZANA, "assets/textures/manzana.png");
    m_control->m_assets->AddTexture(MURO, "assets/textures/muro.png", true);
    m_control->m_assets->AddTexture(SNAKE, "assets/textures/snake.png");

    m_mapa.setTexture(m_control->m_assets->GetTexture(MAPA));
    m_mapa.setTextureRect(m_control->m_window->getViewport(m_control->m_window->getDefaultView()))
}
void GamePlay::ProcessInput()
{
}
void GamePlay::Update(sf::Time deltaTime)
{
}
void GamePlay::Draw()
{
    m_control->m_window->clear();
    m_control->m_window->draw(m_mapa);
    m_control->m_window->display();
}
void GamePlay::Pause()
{
}
void GamePlay::Start()
{
}