#ifndef CORE_H
#define CORE_H


#include <SFML/Graphics.hpp>

class Graphics;
class World;
class Controller;

class Core
{
    public:
        Core(){}
        Core(sf::RenderWindow* window);

        void run();
        virtual void init();
            void initGraphics();
            void initWorldFromFile(std::string pathfile, int players=1);
            void initWorld(int w, int h);
        void load();

        void update();
            void updateFPS();
        void draw();
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
