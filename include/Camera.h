#ifndef CAMERA_H
#define CAMERA_H

#include <SFML/Graphics.hpp>

class Positionnable;

class Camera
{
    public:

        Camera(sf::RenderWindow* w, Positionnable* p);
        //Pos
        void setPositionnable (Positionnable* p) {m_pos=p;}
        Positionnable* getPos() {return m_pos;}
        //View
            //size
            void setViewSize(int w,int h) {m_view.setSize(w,h);}
            const sf::Vector2f getViewSize() {return m_view.getSize();}
            //update
            void updateView();
            //getter setter
            void setView(sf::View v) {m_view=v;}
            const sf::View getView() {return m_view;}



        virtual ~Camera();
    protected:
        sf::View m_view;
        sf::RenderWindow* m_window;
        Positionnable* m_pos;
};

#endif // CAMERA_H
