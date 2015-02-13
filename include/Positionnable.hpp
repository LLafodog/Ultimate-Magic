#ifndef POSITIONNABLE_H
#define POSITIONNABLE_H

#include <SFML/Graphics.hpp>

#include<Defines.hpp>

using namespace sf;

class Positionnable
/**
    In suc ha game we need to save a position, so everything that must have a position is (by def) a positionnable.
    Within this context, everything that must be placed, must be seen, so must have a size.. :)
**/
{
    public:
        Positionnable(float x=0, float y=0, float width=TILE_WIDTH, float height=TILE_HEIGHT);

        virtual ~Positionnable();

        /// ============ GETTER =================
        virtual const float  getPositionX() {return m_x;}
        virtual const float getPositionY() {return m_y;}
        virtual Vector2f getPosition() {return Vector2f(m_x,m_y);}
        virtual const Vector2f getSize() {return Vector2f(m_width,m_height);}
        /// ============ SETTER =================
        virtual void setPositionX(float x) {m_x=x;}
        virtual void setPositionY(float y) {m_y=y;}
        virtual void setPosition(float x, float y) {m_x=x;m_y=y;}
        virtual void setPosition(Vector2f v){m_x=v.x;m_y=v.y;}
        virtual void setSize(float  w,float h) {m_width=w;m_height=h;}
        virtual void setSize(Vector2f v) {setSize(v.x,v.y);}

    protected:
        float m_x;
        float m_y;
        float m_width;
        float m_height;
};

#endif // POSITIONNABLE_H
