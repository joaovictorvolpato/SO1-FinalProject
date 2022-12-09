#ifndef window_h
#define window_h

#include <allegro5/allegro.h>
#include <memory>
#include <string>
#include <stdio.h>
#include <list>
#include "thread.h"
#include "traits.h"

#include "PlayerShip.h"
#include "KeyBoard.h"
#include "Sprite.h"
#include "Vector.h"
#include "Drawable.h"

__BEGIN_API

class PlayerShip;

class Window
{
public:
    bool finished;

    Window();
    Window(int width, int height, int fps);
    ~Window();
    void execute();

    void setPlayerShip(PlayerShip *playerShip) { _playerShip = playerShip; }
    void setKeyboard(Keyboard *keyBoard) { _keyBoard = keyBoard; }
    void addDrawableItem(Drawable *item) { this->drawableItens.push_back(item); }
    void removeDrawableItem(Drawable *item) { this->drawableItens.remove(item); }

private:
    std::list<Drawable *> drawableItens;

    // Methods
    void init();
    void draw();
    void loadSprites();
    void drawBackground();
    void verifyEvents();
    void updateBackGround(double diffTime);

    // Window variables
    int width;
    int height;
    int fps;

    // Game object
    PlayerShip *_playerShip;
    Keyboard *_keyBoard;

    // Time variables
    float previousTime;

    // Background
    Point bgMid; /**<point used by the background to draw from */
    Point fgMid;
    Point fg2Mid;
    Vector bgSpeed; /**<background movement speed */
    Vector fgSpeed;
    std::shared_ptr<Sprite> bgSprite; /**<shared pointer to background animation */
    std::shared_ptr<Sprite> fgSprite;

    // Allegro objects
    ALLEGRO_TIMER *_timer;
    ALLEGRO_EVENT_QUEUE *_eventQueue;
    ALLEGRO_DISPLAY *_display;
};

__END_API

#endif