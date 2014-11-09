#include "Animation.h"

using namespace sf;
using namespace std;

#include<iostream>

Animation::Animation(float frameD, float animD)
{
    m_frameDelay=frameD;
    m_animationDelay=animD;
    m_current=0;
    m_clocky.restart();
}


void Animation::update()
{
    int time=m_clocky.getElapsedTime().asMilliseconds();
    if(m_textures!=vector<Texture*>()) //If isn't empty
    {
        if(m_current!=m_textures.size()-1) //if didn't reach the end
        {
            if(time>m_frameDelay)
            {
                m_current++;
                m_clocky.restart();
            }else{}
        }else
        {
            if(time>m_frameDelay+m_animationDelay) // added the frameDelay cuz the last one is skipped otherwise
            {
                m_current=0;
                m_clocky.restart();
            }
        }


        /*
        if(time<=m_frameDelay*m_textures.size())
        {
            if(time%(int)m_frameDelay==0)
            {
                m_current++;
                m_current%=m_textures.size();
            }
        }
        else if(time>=m_frameDelay*m_textures.size()+m_animationDelay)
        {
            m_clocky.restart();
        }
*/
    }
}

Animation::~Animation()
{
    //dtor
}
