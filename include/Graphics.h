#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SFML/Graphics.hpp>

#include "Global.h"

class Player;
class World;
class Tile;
class Camera;

class Graphics
{
    public:
        Graphics(sf::RenderWindow* w, World* wo=0);
    //drawing
        void draw();
            void drawAll();
            void drawTile(Tile*t);
            void drawTilesAround();
            void drawPlayers();
        void clear() {m_window->clear(Global::BDC);}
        static bool needToRefresh;
    //for testing
        void drawAllTextures();
        void getInfo();
    //MaJ
        void update();
    //Camera
//        Camera* getCamera() {return m_camera;}
        virtual ~Graphics();



    protected:
    int m_time;
    int m_refreshTime;
    sf::RenderWindow* m_window;
    World* m_world;
    //Camera* m_camera;

};

#endif // GRAPHICS_H
