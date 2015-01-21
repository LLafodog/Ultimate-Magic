#ifndef MOVABLE_H
#define MOVABLE_H

#include "Positionnable.h"

class World;

class Movable : public Positionnable
{
    public:

        Movable(World* w,float x=0, float y=0, float width=Global::TILE_WIDTH, float height=Global::TILE_HEIGHT);


        /// ============ GETTER =============
        const bool isMoving() {return m_isMoving;}
            const bool isMovingRight() {return m_isMoving && m_orientation=='e';}
            const bool isMovingLeft() {return m_isMoving && m_orientation=='w';}
            const bool isMovingUp() {return m_isMoving && m_orientation=='n';}
            const bool isMovingDown() {return m_isMoving && m_orientation=='s';}
        const void hasMoved() {m_isMoving=false;}
        const char getOrientation() {return m_orientation;}
        const float getSpeed() {return m_speed;}
        void setSpeedFactor(float factor) {m_speed*=factor;}
        /// ============ METHODS =============
        void moveOn(float x, float y, bool changeOrientation=true);
            void moveOnF(int nSpeedX, int nSpeedY, bool changeOrientation=true) {moveOn(nSpeedX*m_speed,nSpeedY*m_speed,changeOrientation);}

        virtual ~Movable();

    protected:

    World* m_world;
    float m_speed;
    bool m_isMoving;
    char m_orientation;
};

#endif // MOVABLE_H
