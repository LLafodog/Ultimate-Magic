#ifndef OBJECT_H
#define OBJECT_H

#include "Positionnable.h"
#include "Global.h"

class Object :public Positionnable
{
    public:
        Object();
        Object( int id, float x=0, float y=0,float width=Global::TILE_WIDTH, float height=Global::TILE_HEIGHT, bool visible=true);

        virtual ~Object();

    protected:
        bool m_visible;

};

#endif // OBJECT_H
