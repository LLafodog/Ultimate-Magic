#ifndef CORE_H
#define CORE_H


#include <SFML/Graphics.hpp>

class Graphics;
class World;
class Controller;
class TextureEngine;
class WorldManager;
class AnimationEngine;

using namespace std;
using namespace sf;

class Core
/**
    The real core of the game, each and every engine is part of it.
    It loads everything, update everything, order to draw everything... Say hello to our GOD !
**/
{
    public:
        Core(RenderWindow* window);

        /// ======== CONSTRUCTION =============
        bool load();

        /// ======== UPDATE =============
        void update();

        /// ======== CASUAL METHODS =============
        void run();
        void draw();

        /// ======== INFO =============
        void showInfo();


        static Controller* m_controller;
        virtual ~Core();

    protected:

        virtual void init();
        void updateFPS();

        RenderWindow* m_window;
        Graphics* m_graphics;
        World* m_world;
        Clock m_clock;
        float m_FPS;
        int m_timeStart;
};

#endif // CORE_H
