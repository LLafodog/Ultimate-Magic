#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <SFML/Graphics.hpp>

class Controller
{
    public:
        Controller();

        //iddle
        virtual bool noOp()=0;
        //gameplay
        virtual bool action()=0;
        //moov
        virtual bool right()=0;
        virtual bool left()=0;
        virtual bool up()=0;
        virtual bool down()=0;

        //access
        virtual sf::Event* getEvent()=0;


        virtual ~Controller();
        sf::Event m_event;
    protected:
    private:
};

#endif // CONTROLLER_H
