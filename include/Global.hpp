#ifndef GLOBAL_H
#define GLOBAL_H

#include <SFML/Graphics.hpp>

#include <vector>
#include <iostream>
#include <string>

using namespace std;
using namespace sf;

class WorldManager;
class TextureEngine;



class Global
/**
    Sort of a Sick bordel that is used for constant or some algo i wrote and didn't find a parent.
**/
{
    public:
       static float FPS;
       static const Color BDC;
       static const string TO_DATA;

        ///Programming tools C/C
        static bool Proba(float p);
        static float strtoi(string number);

/*
no known conversion for argument 2 from
‘void (WorldManager::*)(string) {aka void (WorldManager::*)(basic_string<char>)}’ to
‘void (*)              (string) {aka void (*)              (basic_string<char>)}’|
*/

        typedef void( WorldManager::*WMf)(string);
        static bool readFile(string path, WMf);

        typedef void( TextureEngine::*TEf)(string);
        static bool readFile(string path, TEf);



    protected:
    private:
         Global();
        virtual ~Global();
};

#endif // GLOBAL_H
