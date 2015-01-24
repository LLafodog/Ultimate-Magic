#include "EntityGraphic.h"

#include "TextureEngine.h"
#include "Global.h"
#include "Animation.h"
#include "AnimationEngine.h"
#include "Tile.h"
#include "Object.h"

using namespace sf;

/*
EntityGraphic::EntityGraphic(std::string id, int x, int y,bool visible, float width, float height):Positionnable(x,y,width, height)
{
    m_id=id;
    m_visible=visible;

    initSquare(width,height);
    m_cs.setPosition(x,y);

    //if(!isVObject()){m_animation=AnimationEngine::getInstance()->getAllOf(id)[0];}//if it is a tile, not an object.
    if(!isVObject()){m_animation=AnimationEngine::getInstance()->get(id);}//if it is a tile, not an object.

}
*/

EntityGraphic::EntityGraphic(Tile* t, int x, int y, bool visible, float width, float height) : Positionnable(x,y,width,height)
{
    if(t!=nullptr)
    {

        //cout << " ID : " << t->getID() << endl;
        m_tile=t;
        m_id=t->getID();
        m_visible = visible;

        initSquare(width,height);
        m_cs.setPosition(x,y);

        if(!isVObject()){m_animation=AnimationEngine::getInstance()->get(m_id);}//if it is a tile, not an object.
    }
}

EntityGraphic::EntityGraphic(Object* o) : Positionnable(o->getPositionX(),o->getPositionY(),o->getSize().x, o->getSize().y)
{
    if(o!=nullptr)
    {
        m_id=o->getID();
        m_tile=new Tile(o->getID(),100,o->isSolid());
        m_visible=o->isVisible();

        initSquare(o->getSize().x,o->getSize().y);
        m_cs.setPosition(o->getPositionX(),o->getPositionY());
    }
}


void EntityGraphic::initSquare(float width, float height)
{
    sf::ConvexShape cs;
    cs.setPointCount(4);
    cs.setPoint(0,Vector2f(0,0));
    cs.setPoint(1,Vector2f(width,0));
    cs.setPoint(2,Vector2f(width, height));
    cs.setPoint(3,Vector2f(0,height));
    m_cs= cs;

}

const sf::ConvexShape* EntityGraphic::getApparence()
{
    if(m_animation!=nullptr)m_cs.setTexture(m_animation->getCurrentFrame());
    else{cerr<< " [Tile::getApparence] Problem with id: " << m_id << endl; m_cs.setTexture(TextureEngine::getInstance()->get("error"));}
    return &m_cs;
}

void EntityGraphic::update()
{
    if(m_animation!=nullptr && m_animation->getTextures().size()!=0)
    {
        m_animation->update();
        m_cs.setTexture(m_animation->getCurrentFrame());
    }
    else{m_cs.setTexture(TextureEngine::getInstance()->get("error"));}
    m_cs.setPosition(getPosition());
}


EntityGraphic::~EntityGraphic()
{
    delete m_tile;
}
