#pragma once
#include <map>
#include <memory>
#include <string>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Font.hpp>

namespace Motor
{
    class Assets
    {
    private:
        std::map<int, std::unique_ptr<sf::Texture>> m_textures;
        std::map<int, std::unique_ptr<sf::Font>> m_fonts;

    public:
        Assets()
        {
        }
        
        ~Assets()
        {
        }
        
        void AgregarTextura(int id, const std::string &filePath, bool wantRepeated = false)
        {
            auto texture = std::make_unique<sf::Texture>();

            if (texture->loadFromFile(filePath))
            {
              texture->setRepeated(wantRepeated);
              m_textures[id] = std::move(texture);
            }
        }

        const sf::Texture &GetTexture(int id) const
        {
            return *(m_textures.at(id).get());
        }

    };
}