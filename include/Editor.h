#ifndef EDITOR_H
#define EDITOR_H

#include "Core.h"

class Movable;


class Editor : public Core
{
    public:
        Editor(sf::RenderWindow* window, int w, int h);

        ///MAIN
        void run();
        /// INITIALISATION
        void init(int w, int h);
            void createTemplateWorld(int w,int h);
            void initGraphics();
            void initWorld(std::string pathfile, int players=1);
        /// UPDATE
        void update();
            void updateFPS();
        /// EDITOR
        void draw();
        void modifyTile(sf::Vector2f v);
        const void saveWorld(World* w);
        void loadWorld();
        bool command();
        bool youAgree();

        virtual ~Editor();
    protected:
        int m_actual;

};

#endif // EDITOR_H
