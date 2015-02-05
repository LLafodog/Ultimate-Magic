#ifndef TEXTUREENGINE_H
#define TEXTUREENGINE_H


#include <SFML/Graphics.hpp>
#include <string>

#include<unordered_map>

class TextureEngine
{
    public:

        /// ========== STATIC =========
        static TextureEngine* getInstance();
        void free();



        /* ============ LOADING =============== */
         void load();
             void readLine(std::string line);
             void test(std::string line);
             bool loadPNG(std::string line, bool particles=false);
        /* ============ ANIMATION ============= */
        void const createAnimations();

        /* ============= GETTER =============== */
         sf::Texture* get(std::string name, unsigned int j=0);
         const unsigned int getMax() {return m_textures.size();}
         const unsigned int getMax(std::string id) {return m_textures[id].size();}
            virtual ~TextureEngine();

    protected:
        TextureEngine();
        static TextureEngine* m_self;
        std::unordered_map<std::string,std::vector<sf::Texture*>> m_textures;
};

#endif // TEXTUREENGINE_H
