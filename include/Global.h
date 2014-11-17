#ifndef GLOBAL_H
#define GLOBAL_H

#include <SFML/Graphics.hpp>

#include <vector>
#include <iostream>
#include <vector>

using namespace std;

class Tile;

class Global
{
    public:

       static const int WINDOW_WIDTH=600;
       static const int WINDOW_HEIGHT=480;
       static const int TILE_WIDTH=16;
       static const int TILE_HEIGHT=16;

       static float FPS;
       static const sf::Color BDC;

       static const std::string convertId(int id);

///Programming tools C/C
/*
    isInTheRect:    (xt>=xr && xt<=xr+wr && yt>=yr && yt<=yr+hr)
    inVectorDouble: (y<v.size() && y>=0 && x<v[y].size() && y>=0)
    distanceAtoB:   sqrt( pow(xa-xb,2) + pow(ya-yb,2) )
    signOf:         if(a!=0)abs(a)/a;







*/
    protected:
    private:
         Global();
        virtual ~Global();
};

#endif // GLOBAL_H
