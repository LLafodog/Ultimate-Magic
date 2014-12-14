#include <iostream>
#include <SFML/Graphics.hpp>

#include "Global.h"
#include "Core.h"

#include<ctime>

using namespace std;
using namespace sf;

int main()
{
    srand(time(NULL));

    RenderWindow window(VideoMode(Global::WINDOW_WIDTH,Global::WINDOW_HEIGHT),"Useless title");
    Core core(&window);
    core.run();


    return 0;
}
