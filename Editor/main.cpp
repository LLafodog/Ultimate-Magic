#include <iostream>
#include <SFML/Graphics.hpp>

#include "Global.h"
#include "Editor.h"

#include<ctime>

using namespace std;
using namespace sf;

int main()
{

    srand(time(NULL));

    /** First, ay hello ! **/
    cout    << " ====================================== " << endl
            << " =======     Welcome in         ======= " << endl
            << " ======= Ultimate Magic Editor  ======= " << endl
            << " ====================================== " << endl;

    /** We are gonna ask for the general data about the world that's gonna be created by the user.
        First, ask for dimensions **/
    int w(0),h(0);

    while(w<=0 && h<=0) //secure
    {
        //width
        cout << endl <<" Please enter your world's width." << endl;
        cin >> w;

        //height
        cout << endl << " Please enter your world's height." << endl;
        cin >> h;
    }


    RenderWindow window(VideoMode(Global::WINDOW_WIDTH,Global::WINDOW_HEIGHT),"Useless title");
    Editor editor(&window,w,h);
    editor.run();


    return 0;
}
