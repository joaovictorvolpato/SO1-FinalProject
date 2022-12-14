#ifndef MISSILE_H
#define MISSILE_H

#include <allegro5/allegro.h>
#include <memory>
#include <vector>

#include "traits.h"
#include "Point.h"
#include "Vector.h"
#include "Sprite.h"
#include "Projectile.h"

__BEGIN_API

class Missile : public Projectile
{
public:
    Missile(Point point, ALLEGRO_COLOR color, Vector vector, bool isPlayerShot);
    ~Missile();

    void draw();
    void update(double diffTime);
    int getSize();

private:
    double angle;

    // Sprites
    void loadSprites();
    int currentSpriteIndex = 0;
    static std::vector<std::shared_ptr<Sprite>> sprites;
    static int SPRITES_VECTOR_MAX_INDEX;
};

__END_API

#endif