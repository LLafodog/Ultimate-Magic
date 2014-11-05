#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SFML/Graphics.hpp>

#include "Global.h"
#include <vector>

class Player;
class World;
class Tile;
class Camera;

class Graphics
{
    public:
        Graphics(sf::RenderWindow* w, World* wo=0);
        void initTiles();
    //drawing
        void draw();
            void drawAll();
            void drawTile(Tile*t);
            void drawVisibleArea();
            void drawTilesAround();
            void drawPlayers();
        void clear() {m_window->clear(Global::BDC);}
        static bool needToRefresh;

    //for testing
        void drawAllTextures();
        void getInfo();

    //MaJ
        void update();
        void updateTiles();

    //Camera
        Camera* getCamera() {return m_camera;}
        virtual ~Graphics();



    protected:
    int m_time;
    int m_refreshTime;
    std::vector<vector<Tile*>> m_tiles;
    sf::RenderWindow* m_window;
    World* m_world;
    Camera* m_camera;

};

#endif // GRAPHICS_H
