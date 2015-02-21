#ifndef TEXTUREENGINE_H
#define TEXTUREENGINE_H


#include <SFML/Graphics.hpp>
#include<unordered_map>

// DEBUG
#define TEXTURE_DEBUG 1
#define TEXTURE_DEBUG_DETAILS 1


using namespace std;
using namespace sf;

class TextureEngine
/**
    This class is responsible for every texture that appears in the game. This is quite the most important class and is loaded in an assert.
**/
{
    public:
        static TextureEngine* getInstance();
        void free();

        /// ============ LOADING ===============
         void load();
             void readLine(string line);
             void test(string line);
             bool loadPNG(string line, bool particles=false);

        /// ============ ANIMATION =============
        void const createAnimations();

        /// ============= GETTER ===============
         Texture* get(string name, unsigned int j=0);
         const unsigned int getMax() {return m_textures.size();}
         const unsigned int getMax(string id) {return m_textures[id].size();}

        virtual ~TextureEngine();

    protected:
        TextureEngine();
        static TextureEngine* m_self;
        unordered_map<string,vector<Texture*>> m_textures;
};

#endif // TEXTUREENGINE_H
