#ifndef SPACESHOOTER_H
#define SPACESHOOTER_H

#include <iostream>
#include "cpu.h"
#include "traits.h"
#include "thread.h"
#include "semaphore.h"

#include "Window.h"
#include "KeyBoard.h"
#include "PlayerShip.h"
#include "Collision.h"
#include "PurpleEnemiesControl.h"

__BEGIN_API

class GameHandler
{
public:
    GameHandler() {}
    ~GameHandler() {}

    static void run(void *name)
    {
        windowThread = new Thread(windowExecutor);
        keyboardThread = new Thread(keyBoardFunc);
        playerShipThread = new Thread(playerShipFunc);
        collisionThread = new Thread(collisionFunc);
        purpleShipsControlThread = new Thread(purpleShipsFunc);

        playerShipThread->join();
        windowThread->join();
        keyboardThread->join();
        collisionThread->join();
        purpleShipsControlThread->join();

        delete playerShipThread;
        delete windowThread;
        delete keyboardThread;
        delete collisionThread;
        delete purpleShipsControlThread;
    }

    static void windowExecutor()
    {
        window = new Window(800, 600, 60);
        window->execute();
        delete window;
    }

    static void playerShipFunc()
    {
        playerShipObj = new PlayerShip(GameHandler::kBoardObj);
        window->setPlayerShip(playerShipObj);
        playerShipObj->setWindowReference(window);

        playerShipObj->run();
        // delete playerShipObj;
    }

    static void keyBoardFunc()
    {
        kBoardObj = new Keyboard();
        kBoardObj->setWindowReference(window);
        kBoardObj->run();
        // delete kBoardObj;
    }

    static void collisionFunc()
    {
        collisionObj = new Collision();
        collisionObj->setPlayerShip(playerShipObj);
        collisionObj->setWindow(window);
        playerShipObj->setCollisionReference(collisionObj);
        collisionObj->run();
    }

    static void purpleShipsFunc()
    {
        purpleShipsControlObj = new PurpleEnemiesControl();
        purpleShipsControlObj->setCollisionReference(collisionObj);
        purpleShipsControlObj->setWindowReference(window);
        purpleShipsControlObj->run();
    }

    static Thread *playerShipThread;
    static Thread *windowThread;
    static Thread *keyboardThread;
    static Thread *collisionThread;
    static Thread *purpleShipsControlThread;

    static PlayerShip *playerShipObj;
    static Window *window;
    static Keyboard *kBoardObj;
    static Collision *collisionObj;
    static PurpleEnemiesControl *purpleShipsControlObj;
};

__END_API

#endif