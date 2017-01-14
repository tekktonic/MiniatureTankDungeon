#include <stdbool.h>

#include <SDL2/SDL.h>

#include "entity.h"
#include "direction.h"
#include "keyboard.h"
#include "sprite.h"
#include "team.h"

typedef struct {
    double xSpeed;
    double ySpeed;
    Team t;
    Direction d;
} Bullet;


static void render(Entity *self, SDL_Renderer *r) {
    draw_sprite(r, SS_CHARACTER, 6, 11, &self->position);
}

static void update(Entity *self, int dt) {
    Bullet *p = (Bullet*)self->data;
    self->position.x += p->xSpeed;
    self->position.y += p->ySpeed;
}

static void cleanup(Entity *self) {
    free(self->data);
}

Entity *new_bullet(int x, int y, double xSpeed, double ySpeed,
                   Direction direction, Team team) {
    Entity *ret = malloc(sizeof(Entity));
    ret->update = update;
    ret->render = render;
    ret->cleanup = cleanup;
    ret->position = (SDL_Rect){.x = x, .y = y, .w = 16, .h = 16};
    ret->health = 1;

    ret->data = malloc(sizeof(Bullet));
    Bullet *b = (Bullet*)ret->data;
    b->xSpeed = xSpeed;
    b->ySpeed = ySpeed;
    switch (direction) {
    case DIR_S:
        b->ySpeed += 16.;
        break;
    case DIR_W:
        b->xSpeed -= 16.;
        break;
    case DIR_E:
        b->xSpeed += 16.;
        break;
    case DIR_N:
        b->ySpeed -= 16.;
        break;
    }
    
    b->d = direction;
    b->t = team;
    return ret;
}
