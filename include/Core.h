#ifndef CORE_H
#define CORE_H


#include <SFML/Graphics.hpp>

class Graphics;
class World;
class Controller;

class Core
{
    public:
        Core(sf::RenderWindow* window);

        void run();
        void init();
            void initGraphics();
            void initWorld(int width, int height, int players=1);
        void load();

        void update();
            void updateFPS();
        void showInfo();

        static Controller* m_controller;

        virtual ~Core();

    protected:
        sf::RenderWindow* m_window;
        Graphics* m_graphics;
        World* m_world;
        sf::Clock m_clock;
        float m_fps;
        int m_timeStart;
};

#endif // CORE_H
