#include "PurpleEnemy.h"

__BEGIN_API

int PurpleEnemy::DELAY_BETWEEN_SHOTS = 20;

PurpleEnemy::PurpleEnemy(Point point, Vector vector, std::shared_ptr<Sprite> shipSprite, std::shared_ptr<Sprite> deathSprite) : Enemy(point, vector, 1)
{
    this->_shipSprite = shipSprite;
    this->_deathSprite = deathSprite;
    this->deathSpriteTimer = 5;
    this->color = al_map_rgb(150, 0, 150);
    this->shotsTimer = std::make_shared<Timer>(60);
    this->shotsTimer->create();
    this->shotsTimer->startTimer();
}

void PurpleEnemy::draw()
{
    if (this->isDead())
    {
        this->deathSpriteTimer -= 1;
        this->_deathSprite->draw_death_anim(this->deathSpriteTimer, this->_point, 0);
    }
    else
    {
        this->_shipSprite->draw_tinted(this->_point, this->color, 0);
    }
}

void PurpleEnemy::update(double diffTime)
{
    this->_point = this->_point + this->_speed * diffTime;
    if (this->shotsTimer->getCount() > PurpleEnemy::DELAY_BETWEEN_SHOTS)
    {
        this->_canFire = true;
        this->shotsTimer->srsTimer();
    }
}

int PurpleEnemy::getSize() { return 16; }

bool PurpleEnemy::isOutside() { return this->_point.x < -40; }

void PurpleEnemy::attack() { this->_canFire = false; }

__END_API