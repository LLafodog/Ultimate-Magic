#ifndef DEFINES_INCLUDED
#define DEFINES_INCLUDED

#define TEXTURE_DEBUG 1
    #define TEXTURE_DEBUG_DETAILS 0
#define LOADER_DEBUG 1
    #define LOADER_DEBUG_DETAILS 0
#define IMPORTANT_DEBUG 1
#define TECHNICAL_DEBUG 1

#include<string>
#include<SFML/Graphics.hpp> //...

        static const int WINDOW_WIDTH=600;
        static const int WINDOW_HEIGHT=480;
        static const int TILE_WIDTH=32;
        static const int TILE_HEIGHT=32;
        const sf::Color BDC=sf::Color(4,139,154);
        const std::string TEXTURE_FILE="dat/textures_loading.txt";
        const std::string TILE_PROPERTIES_FILE="tile_properties.txt";
        const std::string BIOME_PROBABILITIES_FILE="biomes.txt";

#endif // DEFINES_INCLUDED
