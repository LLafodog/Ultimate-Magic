#ifndef POSITIONNABLE_H
#define POSITIONNABLE_H

#include <SFML/Graphics.hpp>

#include "Global.h"

class Positionnable
{
    public:
        Positionnable(float x=0, float y=0, int width=Global::TILE_WIDTH, int height=Global::TILE_HEIGHT);

        virtual ~Positionnable();

        const int getPositionX() {return m_x;}
        const int getPositionY() {return m_y;}
        const sf::Vector2f getPosition() {return sf::Vector2f(m_x,m_y);}

        void setPositionX(float x) {m_x=x;}
        void setPositionY(float y) {m_y=y;}
        void setPosition(float x, float y) {m_x=x;m_y=y;}
        void setPosition(sf::Vector2f v){m_x=v.x;m_y=v.y;}

        const sf::Vector2f getSize() {return sf::Vector2f(m_width,m_height);}
        void setSize(int w,int h) {m_width=w;m_height=h;}
        void setSize(sf::Vector2f v) {setSize(v.x,v.y);}

    protected:
        float m_x;
        float m_y;
        int m_width;
        int m_height;
};

#endif // POSITIONNABLE_H
