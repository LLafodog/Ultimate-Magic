#ifndef TILE_H
#define TILE_H

#include <SFML/Graphics.hpp>
#include "global.h"
#include "Positionnable.h"

class Tile : public Positionnable
{
    public:

        Tile(int id, int x=0, int y=0, bool visible=true, float width=Global::TILE_WIDTH, float height=Global::TILE_HEIGHT);

        void setVisible(bool b) {m_visible=b;}
        void initSquare(float width=Global::TILE_WIDTH, float height=Global::TILE_HEIGHT);

        const int getID() {return m_id;}
        const sf::ConvexShape* getShape() {return &m_cs;}
        const bool isVisible() {return m_visible;}

        //Animation
        void update();

        virtual ~Tile();

        protected:
        sf::ConvexShape m_cs;

        bool m_visible;
        float m_width;
        float m_height;
        int m_id;
};

#endif // TILE_H
