#pragma once
#include <Posicion.hpp>
#include <Manzana.hpp>

class Snake
{
private:
    int tamaño;

public:
    void MoverIzquierda(Posicion) {}
    void MoverDerecha(Posicion) {}
    void MoverArriba(Posicion) {}
    void MoverAbajo(Posicion) {}
    void Comer(Manzana) {}
    Snake(/* args */) {}
    ~Snake() {}
};