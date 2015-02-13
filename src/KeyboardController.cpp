#include<KeyboardController.hpp>

using namespace sf;

KeyboardController::KeyboardController()
{
    //ctor
}

bool KeyboardController::noOp()
{
    return (!up() && !action() && !right() && !left() && !up() && !down());
}

bool KeyboardController::action()
{
    return Keyboard::isKeyPressed(Keyboard::Space);
}
//moov
bool KeyboardController::right()
{
    return Keyboard::isKeyPressed(Keyboard::Right);
}
bool KeyboardController::left()
{
    return Keyboard::isKeyPressed(Keyboard::Left);
}
bool KeyboardController::up()
{
    return Keyboard::isKeyPressed(Keyboard::Up);
}
bool KeyboardController::down()
{
    return Keyboard::isKeyPressed(Keyboard::Down);
}

KeyboardController::~KeyboardController()
{
    //dtor
}
