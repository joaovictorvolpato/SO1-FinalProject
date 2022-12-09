#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <allegro5/allegro.h>
#include <memory>
#include <string>
#include "thread.h"
#include "traits.h"

#include "PlayerShip.h"
#include "Sprite.h"
#include "Vector.h"
#include "Action.h"
#include "Window.h"

__BEGIN_API

class Keyboard
{

public:
    typedef act::KbKey KbKey;

    void setWindowReference(Window *window) { this->_window = window; }
    Keyboard();
    ~Keyboard();

    void init();
    void run();
    bool getKbKeyIsPressed(KbKey key);

private:
    // Methods
    void updateKeyboardStatus();

    // Time variables
    float startTime = 0;
    float currentTime = 0;
    Window *_window;
    // Allegro objects
    ALLEGRO_KEYBOARD_STATE kBoard;
    ALLEGRO_EVENT_QUEUE *_eventQueue;
};

__END_API

#endif
