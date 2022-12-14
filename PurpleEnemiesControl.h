#include <list>
#include <memory>
#include "thread.h"
#include "traits.h"

#include "Sprite.h"
#include "PurpleEnemy.h"
#include "Window.h"
#include "Collision.h"

__BEGIN_API

class PurpleEnemiesControl
{
public:
    PurpleEnemiesControl();
    ~PurpleEnemiesControl();
    void setWindowReference(Window *window) { this->_window = window; }
    void setCollisionReference(Collision *collision) { this->_collision = collision; }

    void run();

private:
    void loadSprites();
    void createShips();
    void processLoop();
    void handleShips();
    int DELAY_SHIPS_SPAWN;

    // ReferĂȘncias de Window e Collision para passar para as Ships
    Window *_window;
    Collision *_collision;

    // Sprites
    std::list<PurpleEnemy *> ships;
    std::shared_ptr<Timer> shipsSpawnTimer;
    std::shared_ptr<Sprite> purpleShipSprite;
    std::shared_ptr<Sprite> enemyExplosionSprite;
};

__END_API