#ifndef ENTITY_H
#define ENTITY_H
#include <SDL2/SDL.h>
#include "event.h"
struct Entity;

//typedef void (*renderfun)(struct Entity *self, struct SDL_Renderer *r);

typedef struct Entity {
    /* renderfun render; */
    /* updatefun update; */
    /* cleanupfun cleanup; */
    /* SDL_Rect position; */
    /* int health; */
    int id;
    
    EventQueue events;

    Component *render;
    ComponentHash *components;
} Entity;

Entity *entities[64];
#endif
