#ifndef ENTITY_H
#define ENTITY_H
#include <SDL2/SDL.h>
#include "component.h"
#include "event.h"
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

Entity *entities[256];

void add_entity(Entity *e);

void delete_entity(int id);
#endif
