#include "Tile.h"

#include "textureEngine.h"
#include "Global.h"
#include "Animation.h"
#include "AnimationEngine.h"

using namespace sf;

Tile::Tile(int id, int x, int y,bool visible, float width, float height):Positionnable(x,y,width, height)
{
    m_id=id;
    m_visible=visible;

    initSquare(width,height);
    m_cs.setPosition(x,y);
    m_animation=AnimationEngine::get(id);
}

Tile::Tile(int x, int y, Animation* a, bool visible, float width, float height) : Positionnable(x,y,width, height)
{
    m_visible=visible;
    m_animation=a;
    initSquare(width,height);
    m_cs.setPosition(x,y);
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

const sf::ConvexShape* Tile::getApparence()
{
    if(m_animation!=nullptr)m_cs.setTexture(m_animation->getCurrentFrame());
    else{m_cs.setTexture(TextureEngine::get("error"));}
    return &m_cs;
}

void Tile::update()
{
    if(m_animation!=nullptr)
    {
        m_animation->update();
        m_cs.setTexture(m_animation->getCurrentFrame());
    }
    else{m_cs.setTexture(TextureEngine::get("error"));}
    m_cs.setPosition(getPosition());
}


Tile::~Tile()
{
    //dtor
}
