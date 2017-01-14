#include <stdbool.h>

#include <SDL2/SDL.h>

#include "bullet.h"
#include "direction.h"
#include "entity.h"
#include "keyboard.h"
#include "sprite.h"
#include "team.h"

typedef struct {
    double xSpeed;
    double ySpeed;
    double timeout;
    Direction d;
    double invincible;
} Player;


static void render(Entity *self, SDL_Renderer *r) {
    Player *p = (Player*)self->data;

    static bool blinky = false;
    static int time = 0;
    {
        SDL_Rect heart = {.x = 20, .y = 20};
        for (int i = 0; i < self->health; i++) {
            draw_sprite(r, SS_THINGS, 6, 1, &heart);
            heart.x += 36;
        }
    }

    
    if (!p->invincible) {
        blinky = false;
        draw_sprite(r, SS_CHARACTER, 4+p->d, 1, &self->position);
    }
    else if (!blinky) {
        draw_sprite(r, SS_CHARACTER, 4+p->d, 1, &self->position);
        time = (time == 0 ? blinky = !blinky, 4 : time-1);
    }
    else
    {
        time = (time == 0 ? blinky = !blinky, 4 : time-1);
    }


}

static void update(Entity *self, int dt) {
    Player *p = (Player*)self->data;
    if (keyboard[SDL_SCANCODE_RIGHT])
        p->xSpeed = 6;
    if (keyboard[SDL_SCANCODE_LEFT])
        p->xSpeed = -6;
    if (!keyboard[SDL_SCANCODE_RIGHT] && !keyboard[SDL_SCANCODE_LEFT])
        p->xSpeed = 0;
    
    if (keyboard[SDL_SCANCODE_DOWN])
        p->ySpeed = 6;
    if (keyboard[SDL_SCANCODE_UP])
        p->ySpeed = -6;
    if (!keyboard[SDL_SCANCODE_DOWN] && !keyboard[SDL_SCANCODE_UP])
        p->ySpeed = 0;
    if (keyboard[SDL_SCANCODE_H] && !p->invincible) {
        self->health--;
        p->invincible = 60.;
    }
    else
        p->invincible = p->invincible == 0 ? p->invincible : p->invincible-1;

    if (keyboard[SDL_SCANCODE_W]) {
        entities[0] = new_bullet(self->position.x, self->position.y, p->xSpeed,
                                 p->ySpeed, DIR_N, TEAM_PLAYER);
    }
    else if (keyboard[SDL_SCANCODE_D]) {
        entities[0] = new_bullet(self->position.x, self->position.y, p->xSpeed,
                                 p->ySpeed, DIR_E, TEAM_PLAYER);        
    }
    else if (keyboard[SDL_SCANCODE_S]) {
        entities[0] = new_bullet(self->position.x, self->position.y, p->xSpeed,
                                 p->ySpeed, DIR_S, TEAM_PLAYER);
    }
    else if (keyboard[SDL_SCANCODE_A]) {
        entities[0] = new_bullet(self->position.x, self->position.y, p->xSpeed,
                                 p->ySpeed, DIR_W, TEAM_PLAYER);
    }

    self->position.x += p->xSpeed;
    self->position.y += p->ySpeed;
}

static void cleanup(Entity *self) {
    free(self->data);
}

Entity *new_player(int x, int y) {
    Entity *ret = malloc(sizeof(Entity));
    ret->update = update;
    ret->render = render;
    ret->cleanup = cleanup;
    ret->position = (SDL_Rect){.x = x, .y = y};
    ret->health = 8;

    ret->data = malloc(sizeof(Player));
    Player *p = (Player*)ret->data;
    p->xSpeed = p->ySpeed = 0;
    p->timeout = 0.;
    p->d = DIR_S;
    p->invincible = 0;
    return ret;
}
