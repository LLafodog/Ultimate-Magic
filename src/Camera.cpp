#include "Camera.h"

using namespace sf;
using namespace std;

#include "Positionnable.h"

Camera::Camera(RenderWindow* w, Positionnable* p)
{
    //m_window=w;
    m_pos=p;
    //m_view=View(p->getPosition(),Vector2f(10*Global::TILE_WIDTH,10*Global::TILE_HEIGHT));*/
}

void Camera::updateView()
{
    //m_view.setCenter(m_pos->getPosition());
}

Camera::~Camera()
{
    //dtor
}
