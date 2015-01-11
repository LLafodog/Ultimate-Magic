#ifndef TEXTUREENGINE_H
#define TEXTUREENGINE_H


#include <SFML/Graphics.hpp>
#include <string>


class TextureEngine
{
    public:

        TextureEngine();
        /// ========== STATIC =========
        static TextureEngine* getInstance() {return m_self;}
        // TO IMPROVE
        static TextureEngine* m_self;
        static int convertID(std::string id);


        /* ============ LOADING =============== */
         void load();
             void readLine(std::string line);
             void test(std::string line);
             bool loadPNG(std::string line);
        /* ============ ANIMATION ============= */
        void const createAnimations();

        /* ============= GETTER =============== */
         sf::Texture* get(unsigned int i, unsigned int j);
         sf::Texture* get(std::string name, unsigned int j=0);
         const unsigned int getMax() {return m_textures.size();}
         const unsigned int getMax(unsigned int i) {if(i<m_textures.size())return m_textures[i].size();return 0;}
            virtual ~TextureEngine();

    protected:

        std::vector< std::vector<sf::Texture*> > m_textures; // Double pour animations

        static std::vector<std::string> m_names;
};

#endif // TEXTUREENGINE_H
