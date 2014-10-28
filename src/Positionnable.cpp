#include "Positionnable.h"

Positionnable::Positionnable(float x, float y, int width, int height)
{
    m_x=x;
    m_y=y;
    m_width=width;
    m_height=height;
}

Positionnable::~Positionnable()
{
    //dtor
}
