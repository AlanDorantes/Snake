#pragma once
#include <SFML/System/Time.hpp>

namespace Engine
{
    class State
    {
    public:
        State(){};
        virtual ~State(){};
        virtual void Inicializar() = 0;
        virtual void ProcesarEntrada() = 0;
        virtual void Actualizar(sf::Time deltaTime) = 0;
        virtual void Dibujar() = 0;
        virtual void Pausar() {};
        virtual void Iniciar() {};
    };
}