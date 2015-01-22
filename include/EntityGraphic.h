#ifndef ENTITYGRAPHICS_H
#define ENTITYGRAPHICS_H


#include "Positionnable.h"
#include"Global.h"
class Animation;
class Tile;
class Object;

class EntityGraphic : public Positionnable
{
    public:

        //EntityGraphic(std::string id, int x=0, int y=0, bool visible=true, float width=Global::TILE_WIDTH, float height=Global::TILE_HEIGHT);
        EntityGraphic(Tile* t, int x, int y, bool visible=false, float width=Global::TILE_WIDTH, float height=Global::TILE_HEIGHT);
        EntityGraphic(Object* o);


        void initSquare(float width=Global::TILE_WIDTH, float height=Global::TILE_HEIGHT);

        const std::string getID() {return m_id;}
        const sf::ConvexShape* getShape() {return &m_cs;} //Modifier le cs pour qu'il ait la
        const sf::ConvexShape* getApparence();
        const bool isVisible() {return m_visible;}

        //Animation
        virtual void update();

        void setVisible(bool b) {m_visible=b;}
        void setAnimation(Animation* anim) {m_animation=anim;}

        /* ==================== GETTER ================ */
        const Animation* getAnimation() {return m_animation;}
        Tile* getTile() {return m_tile;}

        virtual const bool isVObject() {return false;}


        virtual ~EntityGraphic();

        protected:
        sf::ConvexShape m_cs;

        bool m_visible;
        float m_width;
        float m_height;
        std::string m_id;
        Animation* m_animation;
        Tile* m_tile;
};

#endif // ENTITYGRAPHICS_H
