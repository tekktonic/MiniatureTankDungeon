#ifndef ENTITY_H
#define ENTITY_H
#include <SDL2/SDL.h>

struct Entity;

typedef void (*renderfun)(struct Entity *self, SDL_Renderer *r);
typedef void (*updatefun)(struct Entity *self, int dt);
typedef void (*cleanupfun)(struct Entity *self);

typedef struct Entity {
    renderfun render;
    updatefun update;
    cleanupfun cleanup;
    SDL_Rect position;
    int health;
    int id;
    void *data;
} Entity;

Entity *entities[64];
#endif
