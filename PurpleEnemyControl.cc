#include "PurpleEnemiesControl.h"

__BEGIN_API

std::shared_ptr<Sprite> purpleShipSprite;

PurpleEnemiesControl::PurpleEnemiesControl()
{
    this->loadSprites();
    this->DELAY_SHIPS_SPAWN = 500;
    this->shipsSpawnTimer = std::make_shared<Timer>(60);
    this->shipsSpawnTimer->create();
    this->shipsSpawnTimer->startTimer();
}

PurpleEnemiesControl::~PurpleEnemiesControl() {}

void PurpleEnemiesControl::run()
{
    this->loadSprites();
    while (!this->_window->finished)
    {
        if (this->_window == nullptr || this->_collision == nullptr)
        {
            Thread::yield();
            continue;
        }

        this->processLoop();
        Thread::yield();
    }
}

void PurpleEnemiesControl::processLoop()
{
    // Há uma dependência aqui do timer ser maior do que o tempo para o ultimo sair da tela por causa de referência de ponteiros
    if (this->shipsSpawnTimer->getCount() > this->DELAY_SHIPS_SPAWN)
        this->createShips();
    // this->handleShips();
}

void PurpleEnemiesControl::handleShips()
{
    for (auto shipItem = this->ships.begin(); shipItem != this->ships.end();)
    {
        Enemy *ship = *shipItem;
        shipItem++;
    }
}

void PurpleEnemiesControl::createShips()
{
    this->ships.clear();

    // Cria os 5 ships purple
    PurpleEnemy *ship1 = new PurpleEnemy(Point(800, 300), Vector(-180, 0), this->purpleShipSprite, this->enemyExplosionSprite);
    PurpleEnemy *ship2 = new PurpleEnemy(Point(900, 350), Vector(-180, 0), this->purpleShipSprite, this->enemyExplosionSprite);
    PurpleEnemy *ship3 = new PurpleEnemy(Point(900, 250), Vector(-180, 0), this->purpleShipSprite, this->enemyExplosionSprite);
    PurpleEnemy *ship4 = new PurpleEnemy(Point(1000, 400), Vector(-180, 0), this->purpleShipSprite, this->enemyExplosionSprite);
    PurpleEnemy *ship5 = new PurpleEnemy(Point(1000, 200), Vector(-180, 0), this->purpleShipSprite, this->enemyExplosionSprite);
    PurpleEnemy *ship6 = new PurpleEnemy(Point(1100, 100), Vector(-180, 0), this->purpleShipSprite, this->enemyExplosionSprite);
    PurpleEnemy *ship7 = new PurpleEnemy(Point(1100, 500), Vector(-180, 0), this->purpleShipSprite, this->enemyExplosionSprite);

    // Manda para o objeto collision
    this->_collision->addEnemies(ship1);
    this->_collision->addEnemies(ship2);
    this->_collision->addEnemies(ship3);
    this->_collision->addEnemies(ship4);
    this->_collision->addEnemies(ship5);
    this->_collision->addEnemies(ship6);
    this->_collision->addEnemies(ship7);

    // Manda para o objeto window
    this->_window->addDrawableItem(ship1);
    this->_window->addDrawableItem(ship2);
    this->_window->addDrawableItem(ship3);
    this->_window->addDrawableItem(ship4);
    this->_window->addDrawableItem(ship5);
    this->_window->addDrawableItem(ship6);
    this->_window->addDrawableItem(ship7);

    // Guarda na referência dos ships
    this->ships.push_front(ship1);
    this->ships.push_front(ship2);
    this->ships.push_front(ship3);
    this->ships.push_front(ship4);
    this->ships.push_front(ship5);
    this->ships.push_front(ship6);
    this->ships.push_front(ship7);

    // Reset o timer
    this->shipsSpawnTimer->srsTimer();
}

void PurpleEnemiesControl::loadSprites()
{
    // Go to resources directory
    ALLEGRO_PATH *path = al_get_standard_path(ALLEGRO_RESOURCES_PATH);
    al_append_path_component(path, "resources");
    al_change_directory(al_path_cstr(path, '/'));

    this->purpleShipSprite = std::make_shared<Sprite>("EnemyBasic.png");
    this->enemyExplosionSprite = std::make_shared<Sprite>("explode.png");
    al_destroy_path(path);
}

__END_API