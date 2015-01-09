#ifndef GLOBAL_H
#define GLOBAL_H

#include <SFML/Graphics.hpp>

#include <vector>
#include <iostream>
#include <string>

using namespace std;

class Tile;
class WorldManager;

class Global
{
    public:

       static const int WINDOW_WIDTH=600;
       static const int WINDOW_HEIGHT=480;
       static const int TILE_WIDTH=32;
       static const int TILE_HEIGHT=32;

       static float FPS;
       static const sf::Color BDC;
       static const string TO_DATA;
       static const vector<string> TEXTURE_NAMES;

///Programming tools C/C
        static bool Proba(float p);
        static float strtoi(string number);

/*
no known conversion for argument 2 from
‘void (WorldManager::*)(std::string) {aka void (WorldManager::*)(std::basic_string<char>)}’ to
‘void (*)              (std::string) {aka void (*)              (std::basic_string<char>)}’|
*/
        typedef void( WorldManager::*PtrFonct )(string);
        static bool readFile(std::string path, PtrFonct);



    protected:
    private:
         Global();
        virtual ~Global();
};

#endif // GLOBAL_H
