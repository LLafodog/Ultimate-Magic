#ifndef DEFINES_INCLUDED
#define DEFINES_INCLUDED

#define IMPORTANT_DEBUG 1
#define TECHNICAL_DEBUG 1

#include<string>
#include<SFML/Graphics/Color.hpp> 

static const int WINDOW_WIDTH=600;
static const int WINDOW_HEIGHT=480;
static const int TILE_WIDTH=32;
static const int TILE_HEIGHT=32;
const sf::Color BDC=sf::Color(4,139,154);
const std::string TEXTURE_FILE="all_textures.txt";
const std::string TILE_PROPERTIES_FILE="all_tile_properties.txt";
const std::string BIOME_PROBABILITIES_FILE="biomes.txt";
const std::string WORLD_TYPE_FILE="all_wdat.txt";
const std::string TO_DATA="../data/";

#endif // DEFINES_INCLUDED
