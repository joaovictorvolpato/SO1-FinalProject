#ifndef WINDOW_H
#define WINDOW_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>

#include <memory>
#include "Action.h"
#include "Point.h"
#include "Vector.h"


struct Point;
struct Vector;
class Sprite;


class Window {
  public:
   int fps; 
   int width;
   int height;

   Window(int width, int height, int fps);
   ~Window();
   void run();
   void draw();
   void update();
};

#endif