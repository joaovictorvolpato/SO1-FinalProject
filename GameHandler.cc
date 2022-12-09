#include "GameHandler.h"

__BEGIN_API

Thread *GameHandler::playerShipThread;
Thread *GameHandler::windowThread;
Thread *GameHandler::keyboardThread;
Thread *GameHandler::collisionThread;
Thread *GameHandler::purpleShipsControlThread;

PlayerShip *GameHandler::playerShipObj;
Window *GameHandler::window;
Keyboard *GameHandler::kBoardObj;
Collision *GameHandler::collisionObj;
PurpleEnemiesControl *GameHandler::purpleShipsControlObj;

__END_API
