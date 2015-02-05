#include <iostream>
#include <SFML/Graphics.hpp>

#include "Global.h"
#include "Core.h"

#include<ctime>

using namespace std;
using namespace sf;

int main()
{
    // init random
    srand(time(NULL));

    // the game window starts
    RenderWindow window(VideoMode(Global::WINDOW_WIDTH,Global::WINDOW_HEIGHT),"Useless title");

    // let's play !
    Core core(&window);


    return 0;
}
