#ifndef TILE_H
#define TILE_H

#include <SFML/Graphics.hpp>
#include "Global.h"
#include "Positionnable.h"

class Animation;

class Tile : public Positionnable
{
    public:

        Tile(std::string id, int x=0, int y=0, bool visible=true, float width=Global::TILE_WIDTH, float height=Global::TILE_HEIGHT);

        void setVisible(bool b) {m_visible=b;}
        void initSquare(float width=Global::TILE_WIDTH, float height=Global::TILE_HEIGHT);

        const std::string getID() {return m_id;}
        const sf::ConvexShape* getShape() {return &m_cs;} //Modifier le cs pour qu'il ait la
        const sf::ConvexShape* getApparence();
        const bool isVisible() {return m_visible;}

        //Animation
        virtual void update();
        void setAnimation(Animation* anim) {m_animation=anim;}
        const Animation* getAnimation() {return m_animation;}

        virtual const bool isVObject() {return false;}


        virtual ~Tile();

        protected:
        sf::ConvexShape m_cs;

        bool m_visible;
        float m_width;
        float m_height;
        std::string m_id;
        Animation* m_animation;
};

#endif // TILE_H
