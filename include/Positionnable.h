#ifndef POSITIONNABLE_H
#define POSITIONNABLE_H

#include <SFML/Graphics.hpp>

#include "Global.h"

class Positionnable
{
    public:
        Positionnable(float x=0, float y=0, float width=Global::TILE_WIDTH, float height=Global::TILE_HEIGHT);

        virtual ~Positionnable();

        virtual const float  getPositionX() {return m_x;}
        virtual const float getPositionY() {return m_y;}
        virtual sf::Vector2f getPosition() {return sf::Vector2f(m_x,m_y);}

        void setPositionX(float x) {m_x=x;}
        void setPositionY(float y) {m_y=y;}
        void setPosition(float x, float y) {m_x=x;m_y=y;}
        void setPosition(sf::Vector2f v){m_x=v.x;m_y=v.y;}

        const sf::Vector2f getSize() {return sf::Vector2f(m_width,m_height);}
        void setSize(float  w,float h) {m_width=w;m_height=h;}
        void setSize(sf::Vector2f v) {setSize(v.x,v.y);}

    protected:
        float m_x;
        float m_y;
        float  m_width;
        float m_height;
};

#endif // POSITIONNABLE_H
