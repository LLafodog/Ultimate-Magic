#ifndef CAMERA_H
#define CAMERA_H

#include <SFML/Graphics.hpp>

class Positionnable;
class World;

using namespace sf;

class Camera
/**
    This class control the view of the window, the main one with the player centered.
**/
{
    public:

        Camera(RenderWindow* w, Positionnable* p, World* wo);

        /// ========== CASUAL METHODS ========
        void updateView();
        void zoom(float f);
        bool move(float x, float y);
        bool isIn(float x, float y);

        /// ========== SETTER ========
        void setPositionnable (Positionnable* p) {m_pos=p;}
        void setViewSize(int w,int h) {m_view.setSize(w,h);}
        void setView(View v) {m_view=v;}

        /// ========== GETTER ========
        Positionnable* getPos() {return m_pos;}
        const Vector2f getViewSize() {return m_view.getSize();}
        View getView() {return m_view;}

        virtual ~Camera();

    protected:
        View m_view;
        RenderWindow* m_window;
        Positionnable* m_pos;
        World* m_world;
};

#endif // CAMERA_H
