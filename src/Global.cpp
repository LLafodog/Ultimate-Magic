#include "Global.h"

#include <SFML/Graphics.hpp>
#include <cmath>
#include <fstream>
// test
#include "TextureEngine.h"

using namespace std;

bool Global::readFile(std::string path, WMf)
{
    fstream reader(path.c_str());
    if(!reader){cerr << " Problem loading " << path << "file"<<endl; return false;}
    else
    {
        string line;
        while(getline(reader,line))
        {
            WMf(line);
        }
        return true;
    }
}

void test(string test){cout << "pendant" ;}

const string Global::TO_DATA="../data/";

const sf::Color Global::BDC=sf::Color(4,139,154);

bool Global::Proba(float p)
{
    return(rand()%(int)(1/p)==0);
}

float Global::strtoi(string number)
{
    return atof(number.c_str());
}

Global::Global()
{
    //ctor
    FPS=0;
}


Global::~Global()
{
    //dtor
}
