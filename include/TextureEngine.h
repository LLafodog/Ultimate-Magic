#ifndef TEXTUREENGINE_H
#define TEXTUREENGINE_H


#include <SFML/Graphics.hpp>
#include <string>

#include "Global.h"

class TextureEngine
{
    public:

        /* ============ LOADING =============== */
        static void load();
            static bool loadPNG(std::string fileName, int nbWidth, int nbHeight, int widthTile=Global::TILE_WIDTH, int heightTile=Global::TILE_HEIGHT);
            static bool loadBasicPNG(std::string fileName, int nbWidth, int nbHeight, int widthTile, int heightTile);

        /* ============= GETTER =============== */
        static sf::Texture* get(unsigned int i, unsigned int j);
        static sf::Texture* get(std::string name, unsigned int j=0);
        static std::vector<sf::Texture*> getAllOf(std::string name);
        static const unsigned int getMax() {return m_textures.size();}
        static const unsigned int getMax(unsigned int i) {if(i<m_textures.size())return m_textures[i].size();return 0;}

    protected:
        static std::vector< std::vector<sf::Texture> > m_textures; // Double pour animations
        TextureEngine();
        virtual ~TextureEngine();
};

#endif // TEXTUREENGINE_H
