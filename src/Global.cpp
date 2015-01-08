#include "Global.h"

#include <SFML/Graphics.hpp>
#include <cmath>

using namespace std;

const vector<string> Global::TEXTURE_NAMES={"grass_tl","grass_t","grass_tr","grass_l","grass","grass_r","grass_bl","grass_b","grass_br", //9 en tout
                                            "light_grass", //10
                                            "desert", //11
                                            "dragon_down","dragon_left","dragon_right","dragon_up", //15
                                            "error", //16
                                            "pine_tree",  //17
                                            "invisible" //18
                                            };


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
