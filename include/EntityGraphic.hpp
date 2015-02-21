#ifndef ENTITYGRAPHICS_H
#define ENTITYGRAPHICS_H


#include<Positionnable.hpp>
#include<Global.hpp>

class Animation;
class Tile;
class Object;

using namespace std;
using namespace sf;

class EntityGraphic : public Positionnable
/**
    Here is the basic entity drawable in the game. Everything will come from it.
    It has a convexshape (allowing to use isometric maybe futher) and an animation to draw on it.
**/
{
    public:

        EntityGraphic(Tile* t, int x, int y, bool visible=false, float width=TILE_WIDTH, float height=TILE_HEIGHT);
        EntityGraphic(Object* o); // VObject herits from entity
        EntityGraphic(string particle); // Fire, poison, wind  etc.

        /** ========== CASUAL METHODS ========== **/
        virtual void update();


        /** ================== SETTER ================ **/
        void setVisible(bool b) {m_visible=b;}
        void setAnimation(Animation* anim) {delete m_animation; m_animation=anim;}
        void setShapeSize(Vector2f v);

        /** ==================== GETTER ================ **/
        const Animation* getAnimation() {return m_animation;}
        Tile* getTile() {return m_tile;}
        const string getID() {return m_id;}
        const ConvexShape* getShape() {return &m_cs;} //Modifier le cs pour qu'il ait la
        const ConvexShape* getApparence();
        const bool isVisible() {return m_visible;}

        /** ======= CONVERSION ========== **/
        virtual const bool isVObject() {return false;}


        virtual ~EntityGraphic();

        protected:
        void initSquare(float width=TILE_WIDTH, float height=TILE_HEIGHT);

        ConvexShape m_cs;
        bool m_visible;
        string m_id;
        Animation* m_animation;
        Tile* m_tile;
};

#endif // ENTITYGRAPHICS_H
