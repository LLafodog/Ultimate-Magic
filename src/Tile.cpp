#include "Tile.h"

#include "textureEngine.h"
#include "Global.h"

using namespace sf;

Tile::Tile(int id, int x, int y,bool visible, float width, float height):Positionnable(x,y,width, height)
{
    m_id=id;
    m_visible=visible;

    initSquare(m_width,m_height);
    m_cs.setPosition(m_x,m_y);



    if(TextureEngine::get(id,0)!=nullptr){m_cs.setTexture(TextureEngine::get(id,0));}
        else{m_cs.setFillColor(Global::BDC);}

}

void Tile::initSquare(float width, float height)
{
    sf::ConvexShape cs;
    cs.setPointCount(4);
    cs.setPoint(0,Vector2f(0,0));
    cs.setPoint(1,Vector2f(width,0));
    cs.setPoint(2,Vector2f(width, height));
    cs.setPoint(3,Vector2f(0,height));
    m_cs= cs;

}

Tile::~Tile()
{
    //dtor
}
