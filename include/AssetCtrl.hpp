// FINISHED

#pragma once
// Agrega mapas para almacenar y acceder a texturas y fuentes
#include <map>
#include <memory>

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Audio/SoundBuffer.hpp>

namespace Engine
{
    class AssetCtrl
    {
    private:
        // Contenedores de texturas y fuentes en map
        std::map<int, std::unique_ptr<sf::Texture>> m_textures;
        std::map<int, std::unique_ptr<sf::Font>> m_fonts;

    public:
        // Constructor sin cambios
        AssetCtrl()
        {
        }

        // Destructor sin cambios
        ~AssetCtrl()
        {
        }

        // Agrega textura
        // 1er parametro es el id de la textura
        // 2do parametro es la ruta del archivo de la textura
        // 3er parametro indica si se quiere que la textura se repita
        void AddTexture(int id, const std::string &filePath, bool wantRepeated = false)
        {
            // Crea una nueva textura con un puntero unico
            auto texture = std::make_unique<sf::Texture>();

            // Carga la textura del archivo e indica si se carga correctamente
            if (texture->loadFromFile(filePath))
            {
                // Indica si se quiere que la textura se repita
                texture->setRepeated(wantRepeated);

                // Guarda la textura en el map en el id correspondiente
                m_textures[id] = std::move(texture);
            }
        }

        // Agrega fuente
        // 1er parametro es el id de la fuente
        // 2do parametro es la ruta del archivo de la fuente
        void AddFont(int id, const std::string &filePath)
        {
            // Crea una nueva fuente con un puntero unico
            auto font = std::make_unique<sf::Font>();

            // Carga la fuente del archivo e indica si se carga correctamente
            if (font->loadFromFile(filePath))
            {
                // Guarda la fuente en el map en el id correspondiente
                m_fonts[id] = std::move(font);
            }
        }

        // Devuelve la textura cargada en el map
        // Se agrega const para que no se pueda modificar la textura
        const sf::Texture &GetTexture(int id) const
        {
            // Devuelve la textura con el id correspondiente
            return *(m_textures.at(id).get());
        }

        // Devuelve la fuente cargada en el map
        // Se agrega const para que no se pueda modificar la fuente
        const sf::Font &GetFont(int id) const
        {
            // Devuelve la fuente com el id correspondiente
            return *(m_fonts.at(id).get());
        }
    };
}