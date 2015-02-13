#include<EntityGraphic.hpp>
/*
#include<TextureEngine.hpp>
#include<Global.hpp>
#include<Animation.hpp>
#include<AnimationEngine.hpp>
#include<Tile.hpp>
#include<Object.hpp>
*/

using namespace sf;


#include<Tile.hpp>
#include<AnimationEngine.hpp>
EntityGraphic::EntityGraphic(Tile* t, int x, int y, bool visible, float width, float height) : Positionnable(x,y,width,height),
m_tile(t),
m_visible(visible)
/**
    World is based on a 2D map of tiles that has properties like effects, solidity etc, here is the most used contructor.
**/
{
    if(t!=nullptr)
    {
        m_tile=t;
        m_id=t->getID();
        m_visible = visible;

        initSquare(width,height);
        m_cs.setPosition(x,y);

        /// VObject has its own system of animation (animation*[4])
        if(!isVObject()){m_animation=AnimationEngine::getInstance()->get(m_id);}
    }
}

#include<Object.hpp>
EntityGraphic::EntityGraphic(Object* o) : Positionnable(o->getPositionX(),o->getPositionY(),o->getSize().x, o->getSize().y)
/**
    VObject are classes that manage the visual of an object, so as its mother, entitygraphics must adapter itself.
**/
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

EntityGraphic::EntityGraphic(string particle) : Positionnable(-TILE_WIDTH,-TILE_HEIGHT,TILE_WIDTH,TILE_HEIGHT)
/**
    Some effects need to be visual (fire, wet etc) so this constructor is usefull to draw it easily without all this position ...
**/
{
    m_id=particle;
    m_tile=nullptr;
    m_visible=true;
    initSquare();
    if(!isVObject()){m_animation=AnimationEngine::getInstance()->get(m_id);}//if it is a tile, not an object.
}


void EntityGraphic::initSquare(float width, float height)
/**
    All the square visual of the game is based on this square methode.
**/
{
    sf::ConvexShape cs;
    cs.setPointCount(4);
    cs.setPoint(0,Vector2f(0,0));
    cs.setPoint(1,Vector2f(width,0));
    cs.setPoint(2,Vector2f(width, height));
    cs.setPoint(3,Vector2f(0,height));
    m_cs= cs;

}

void EntityGraphic::setShapeSize(Vector2f v)
/// Allow to resize a tile (used in particles printer)
{
    initSquare(v.x,v.y);
}

#include<Defines.hpp>
#include<TextureEngine.hpp>
const sf::ConvexShape* EntityGraphic::getApparence()
/// Allows a window to draw the Entity by puting a texture on the shape.
{
    if(m_animation!=nullptr)m_cs.setTexture(m_animation->getCurrentFrame());
    else{if(IMPORTANT_DEBUG)cerr<< " [Tile::getApparence] Problem with id: " << m_id << endl; m_cs.setTexture(TextureEngine::getInstance()->get("error"));}
    return &m_cs;
}

void EntityGraphic::update()
/**
    Actualize the visual (animation) and the position of an entity.
**/
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

}
