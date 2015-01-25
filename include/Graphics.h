#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SFML/Graphics.hpp>

#include "Global.h"
#include <vector>

class Player;
class World;
class EntityGraphic;
class Object;
class Camera;
class VObject;

class Graphics
{
    public:
        Graphics(sf::RenderWindow* w, World* wo=0);
    ///init
        void init();
            void initObjects();
            void initTiles();
    ///drawing
        const void draw();
            const void drawAll();
            const void drawTile(EntityGraphic*t);
            const void drawVisibleArea();
                void drawShadow(EntityGraphic* t);
                void drawTileParticles(EntityGraphic* t);
            const void drawVisibleObjects();
            const void drawObject(VObject* o);
                const void drawAboutAlive(VObject* );
            const void drawLifeBar(VObject* o);
        const void clear() {m_window->clear(Global::BDC);}
        static bool needToRefresh;

    ///for testing
        const void getInfo();

    ///MaJ
        void update();
            void updateTiles();
            void updateObjects();
        void sortObjects();
            bool needResort;
        void setAllowDetails(bool b){m_details=b;}
    ///Camera
        Camera* getCamera() {return m_camera;}
        virtual ~Graphics();



    protected:
    int m_time;
    int m_refreshTime;

    vector<vector<EntityGraphic*>> m_tiles;
    vector<VObject*> m_objects;
    vector<VObject*> m_visibleObjects;
    sf::RenderWindow* m_window;
    World* m_world;
    Camera* m_camera;
    bool m_details; //allow to draw all details like lifebar

    EntityGraphic* m_error;
    sf::RectangleShape* m_shadow;
    sf::RectangleShape* m_particle;

};

#endif // GRAPHICS_H
