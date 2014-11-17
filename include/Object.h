#ifndef OBJECT_H
#define OBJECT_H

#include "Positionnable.h"
#include "Global.h"

class Object :public Positionnable
{
    public:
        Object();
        Object( int id, float x=0, float y=0,float width=Global::TILE_WIDTH, float height=Global::TILE_HEIGHT, bool visible=true , sf::FloatRect hitbox=sf::FloatRect(0,0,Global::TILE_WIDTH,Global::TILE_HEIGHT));
        Object( std::string id, float x=0, float y=0,float width=Global::TILE_WIDTH, float height=Global::TILE_HEIGHT, bool visible=true , sf::FloatRect hitbox=sf::FloatRect(0,0,Global::TILE_WIDTH,Global::TILE_HEIGHT));


        const std::string getId() {return m_id;}
        const char getOrientation() {return m_orientation;}
        const bool isVisible() {return m_visible;}

        //getter setter
        const sf::FloatRect getHitbox() {return m_hitbox;}
        void setHitbox(sf::FloatRect f) {m_hitbox=f;}

        virtual ~Object();

    protected:
        bool m_visible;
        char m_orientation;
        std::string m_id;
        sf::FloatRect m_hitbox;

};

#endif // OBJECT_H
