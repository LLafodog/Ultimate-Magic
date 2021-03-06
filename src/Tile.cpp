#include "Tile.h"

#include "TextureEngine.h"
#include "Global.h"
#include "Animation.h"
#include "AnimationEngine.h"

using namespace sf;


Tile::Tile(std::string id, int x, int y,bool visible, float width, float height):Positionnable(x,y,width, height)
{
    m_id=id;
    m_visible=visible;

    initSquare(width,height);
    m_cs.setPosition(x,y);

    if(!isVObject())m_animation=AnimationEngine::get(id); //if it is a tile, not an object.

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
ń
const sf::ConvexShape* Tile::getApparence()
{
    if(m_animation!=nullptr)m_cs.setTexture(m_animation->getCurrentFrame());
    else{m_cs.setTexture(TextureEngine::get("error"));}
    return &m_cs;
}

void Tile::update()
{
    if(m_animation!=nullptr && m_animation->getTextures().size()!=0)
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
