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

       static const void showVector(vector<vector<int>> v);
       static const bool isInTheRect(float xt,float yt,float xr,float yr,float wr,float hr);
       static const float distanceFromAtoB(float xa, float ya, float xb, float yb);
       static const int  signOf(float a);
       //template<typename T> static const bool inVectorDouble(int a, int b, vector<vector<T>> v);
       static const bool inVectorDouble(int a, int b, vector<vector<Tile*>> v);

    protected:
    private:
         Global();
        virtual ~Global();
};

#endif // GLOBAL_H
