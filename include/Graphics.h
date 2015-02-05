#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SFML/Graphics.hpp>

#include "Defines.h"
#include <vector>

class Player;
class World;
class EntityGraphic;
class Object;
class Camera;
class VObject;
class ParticlesPrinter;

using namespace sf;
using namespace std;

class Graphics
/**
    Graphics Engine, each and every visual you have is drawn HERE !
**/
{
    public:
        Graphics(RenderWindow* w, World* wo=0);
    /// ========== INITIALIZATION ============
        void init();
            void initObjects();
            void initTiles();
    /// ========== DRAWING METHODS ===========
        const void draw();
            const void drawAll();
            const void drawTile(EntityGraphic*t);
            const void drawVisibleArea();
                void drawTileParticles(EntityGraphic* t);
            const void drawVisibleObjects();
            const void drawObject(VObject* o);
                const void drawAboutAlive(VObject* );
            const void drawLifeBar(VObject* o);
        const void clear() {m_window->clear(BDC);}
        static bool needToRefresh;

    /// ========= INFO ===========
        const void getInfo();

    ///========== UPDATE =========
        void update();
            void updateTiles();
            void updateObjects();
        void sortObjects();
            bool needResort;
        void setAllowDetails(bool b){m_details=b;}

    /// ========= CAMERA =========
        Camera* getCamera() {return m_camera;}
        virtual ~Graphics();



    protected:
    int m_time;
    const int m_refreshTime=600 ; // 10 minutes

    vector<vector<EntityGraphic*>> m_tiles;
    vector<VObject*> m_objects;
    vector<VObject*> m_visibleObjects;
    RenderWindow* m_window;
    World* m_world;
    Camera* m_camera;
    bool m_details; //allow to draw all details like lifebar

    EntityGraphic* m_error;
    RectangleShape* m_particle;
    ParticlesPrinter* m_pp;


};

#endif // GRAPHICS_H
