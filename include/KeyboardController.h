#ifndef KEYBOARDCONTROLLER_H
#define KEYBOARDCONTROLLER_H

#include "Controller.h"


class KeyboardController : public Controller
{
    public:
        KeyboardController();
        //iddle
        bool noOp();
        //gameplay
        bool action();
        //moov
        bool right();
        bool left();
        bool up();
        bool down();

        //access
        sf::Event* getEvent() {return &m_event;}

        virtual ~KeyboardController();
    protected:
    private:
};

#endif // KEYBOARDCONTROLLER_H
