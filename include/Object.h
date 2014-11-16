#ifndef OBJECT_H
#define OBJECT_H

#include "Positionnable.h"
#include "Global.h"

class Object :public Positionnable
{
    public:
        Object();
        Object( int id, float x=0, float y=0,float width=Global::TILE_WIDTH, float height=Global::TILE_HEIGHT, bool visible=true);


        const int getId() {return m_id;}
        const char getOrientation() {return m_orientation;}
        const bool isVisible() {return m_visible;}

        virtual ~Object();

    protected:
        bool m_visible;
        char m_orientation;
        int m_id;

};

#endif // OBJECT_H
