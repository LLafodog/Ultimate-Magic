#ifndef EDITOR_H
#define EDITOR_H

#include "Core.h"

class Movable;


class Editor : public Core
{
    public:
 public:
        Editor(sf::RenderWindow* window, int w, int h);

        void run();
        void init(int w, int h);
            void createTemplateWorld(int w,int h);
            void initGraphics();
            void initWorld(std::string pathfile, int players=1);

        void update();
            void updateFPS();
        void draw();

        virtual ~Editor();
    protected:

};

#endif // EDITOR_H
