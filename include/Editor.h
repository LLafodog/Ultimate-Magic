#ifndef EDITOR_H
#define EDITOR_H

#include "Core.h"

class Movable;


class Editor : public Core
{
    public:
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

        virtual ~Editor();
    protected:
        int m_actual;

};

#endif // EDITOR_H
