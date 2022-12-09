#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

#include "Window.h"

__BEGIN_API

Window::Window() { this->init(); }

Window::Window(int width, int height, int fps) : width(width), height(height), fps(fps), finished(false) 
{
    this->init();
}

Window::~Window()
{
    if (this->_timer != NULL)
        al_destroy_timer(this->_timer);
    if (this->_eventQueue != NULL)
        al_destroy_event_queue(this->_eventQueue);
    if (this->_display != NULL)
        al_destroy_display(this->_display);

    bgSprite.reset();
}

void Window::execute()
{
    while (!this->finished)
    {
        this->verifyEvents();
        Thread::yield();
    }
}

void Window::verifyEvents()
{
    ALLEGRO_EVENT event;

    // Get event
    al_wait_for_event(this->_eventQueue, &event);

    // Close display
    if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
    {
        finished = true;
        return;
    }

    // Timer
    if (event.type == ALLEGRO_EVENT_TIMER)
        this->draw();
}

void Window::draw()
{
    // Checa se é para desenhar e se a eventQueue está vazia
    if (al_is_event_queue_empty(this->_eventQueue))
    {
        // Atualiza o timer
        float currentTime = al_current_time();
        double diffTime = currentTime - this->previousTime;
        this->previousTime = currentTime;

        // Update e draw
        this->updateBackGround(diffTime);
        this->drawBackground();

        if (this->_playerShip != nullptr)
        {
            this->_playerShip->update(diffTime);
            this->_playerShip->draw();
        }

        // Para cada item para desenhar faz update, desenha e caso já tenha terminado então coloca numa outra lista para remover
        for (auto listItem = this->drawableItens.begin(); listItem != this->drawableItens.end();)
        {
            Drawable *drawableItem = *listItem;
            listItem++; // Já atualiza o ponteiro para o próximo

            drawableItem->update(diffTime);
            drawableItem->draw();
        }

        al_flip_display();
    }
}

void Window::updateBackGround(double dt)
{
    this->bgMid = this->bgMid + this->bgSpeed * dt;
    if (bgMid.x >= 800)
        bgMid.x = 0;
}

void Window::drawBackground() { bgSprite->draw_parallax_background(bgMid.x, 0); }

void Window::init()
{
    al_init();
    if ((this->_display = al_create_display(this->width, this->height)) == NULL)
    {
        std::cout << "Cannot initialize the display\n";
        exit(1);
    }
    al_init_primitives_addon();
    al_init_font_addon();
    al_init_ttf_addon();
    al_init_image_addon();
    if ((this->_timer = al_create_timer(1.0 / this->fps)) == NULL)
    {
        std::cout << "error, could not create timer\n";
        exit(1);
    }

    if ((this->_eventQueue = al_create_event_queue()) == NULL)
    {
        std::cout << "error, could not create event queue\n";
        exit(1);
    }

    al_register_event_source(this->_eventQueue, al_get_display_event_source(this->_display));
    al_register_event_source(this->_eventQueue, al_get_timer_event_source(this->_timer));
    al_start_timer(this->_timer);

    this->loadSprites();
}

void Window::loadSprites()
{
    ALLEGRO_PATH *path = al_get_standard_path(ALLEGRO_RESOURCES_PATH);
    al_append_path_component(path, "resources");
    al_change_directory(al_path_cstr(path, '/'));
    bgSprite = std::make_shared<Sprite>("BGstars.png");
    al_destroy_path(path);

    bgMid = Point(0, 0);
    fgMid = Point(800, 0);
    fg2Mid = Point(300, 300);
    bgSpeed = Vector(50, 0);
    fgSpeed = Vector(-90, 0);
}

__END_API