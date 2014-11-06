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



Global::~Global()
{
    //dtor
}
