#include "Global.h"

#include <SFML/Graphics.hpp>
#include <cmath>

using namespace std;

const sf::Color Global::BDC=sf::Color(4,139,154);

Global::Global()
{
    //ctor
    FPS=0;
}

const void Global::showVector(vector<vector<int>> v)
{
    for (int i(0);i<v.size();i++)
    {
        for  (int j(0); j<v[i].size();j++)
        {
            cout<<"x: " << j << "  y: " << i<< "  val: "<<v[j][i]<<endl;
        }
    }
}

const bool Global::isInTheRect(float xt,float yt,float xr,float yr,float wr,float hr)
{
    return(xt>=xr && xt<=xr+wr && yt>=yr && yt<=yr+hr);
}

const float Global::distanceFromAtoB(float xa, float ya, float xb, float yb)
{
    return sqrt( pow(xa-xb,2) + pow(ya-yb,2) );
}

const int  Global::signOf(float a)
{
    if(a!=0)return abs(a)/a;
    return 0;
}

//template<typename T> const bool Global::inVectorDouble(int y, int x, vector<vector<T>> v)
const bool Global::inVectorDouble(int y, int x, vector<vector<Tile*>> v)
{
    return (y<v.size() && y>=0 && x<v[y].size() && y>=0);

}



Global::~Global()
{
    //dtor
}
