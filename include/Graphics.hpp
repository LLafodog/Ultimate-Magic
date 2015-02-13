#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SFML/Graphics.hpp>

#include<Defines.hpp>
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
    /// ========== DRAWING METHODS ===========
        const void draw();
        const void clear() {m_window->clear(BDC);}
        static bool needToRefresh;

    /// ========= INFO ===========
        const void getInfo();

    ///========== UPDATE =========
        void update();
        void setAllowDetails(bool b){m_details=b;}

    /// ========= CAMERA =========
        Camera* getCamera() {return m_camera;}
        virtual ~Graphics();



    protected:
    // Init
    void initObjects();
    void initTiles();
    // Update
    void updateTiles();
    void updateObjects();
    void sortObjects();
    bool needResort;
    // Draw
    const void drawAll();
    const void drawTile(EntityGraphic*t);
    const void drawVisibleArea();
    const void drawVisibleObjects();
    const void drawObject(VObject* o);

    // vars
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
