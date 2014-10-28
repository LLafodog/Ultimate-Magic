#ifndef TEXTUREENGINE_H
#define TEXTUREENGINE_H


#include <SFML/Graphics.hpp>

class TextureEngine
{
    public:

        /* TO DO */

        static void load();
        static bool loadPNG(std::string fileName, int nbWidth, int nbHeight, int widthTile=16, int heightTile=16);
        static sf::Texture* get(int i, int j);
        static const unsigned int getMax() {return m_textures.size();}


    protected:
        static std::vector< std::vector<sf::Texture> > m_textures; // Double pour animations

        TextureEngine();
        virtual ~TextureEngine();
};

#endif // TEXTUREENGINE_H
