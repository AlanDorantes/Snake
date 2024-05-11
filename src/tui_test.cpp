#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>
#include <ftxui/screen/color.hpp>
#include <iostream>
#include <string>
#include <thread>
#include <experimental/random>
#include <list>
#include <fstream>

using namespace std;
using namespace ftxui;

int main(int argc, char const *argv[])
{
    list<string> textos;
    fstream imagen;
    imagen.open("./assets/Derecha.txt");

    string linea;
    while (getline(imagen, linea))
    {
        textos.push_back(linea);
    }
    imagen.close();

    int fotograma = 0;

    string reset;
    int posX = 1;
    int posY = 6;
    int anchoMayor = 70;
    int altoMayor = 25;
    while (true)
    {

        Decorator colorFondo = bgcolor(Color::DarkGreen);
        Decorator colorTexto = color(Color::SkyBlue1);
        Element dibujo = border({hbox()}) | colorFondo | colorTexto;

        Dimensions Alto = Dimension::Fixed(25);
        Dimensions Ancho = Dimension::Fixed(70);

        Screen pantalla = Screen::Create(Ancho, Alto);
        Render(pantalla, dibujo);

        if (posX <= 20)
        {
            for (auto &&texto : textos)
            {
                int i = 0;
                for (auto &&letra : texto)
                {
                    pantalla.PixelAt(posX + i, 8).character = letra;
                    i++;
                }
            }
            posX++;
        }

        if (posX > 20)
        {
            if (posY <= 16)
            {
                for (auto &&texto : textos)
                {
                    int l = -3;
                    for (auto &&letra : texto)
                    {
                        pantalla.PixelAt(25, posY + l).character = letra;
                        l++;
                    }
                }
                posY++;
            }
        }

        if (posY > 16)
        {
            if (posX <= 64)
            {
                for (auto &&texto : textos)
                {
                    int i = -1;
                    for (auto &&letra : texto)
                    {
                        pantalla.PixelAt(posX + i, 18).character = letra;
                        i++;
                    }
                }
                posX++;
            }
        }

        pantalla.Print();
        reset = pantalla.ResetPosition();
        cout << reset;
        this_thread::sleep_for(0.40s);
    }

    return 0;
}