#include <stdbool.h>

#include <SDL2/SDL.h>

#include "entity.h"
#include "direction.h"
#include "keyboard.h"
#include "sprite.h"


#include "components/drawc.h"
#include "components/positionc.h"
#include "components/team_collidec.h"
#include "components/teamc.h"
typedef struct {
    double xSpeed;
    double ySpeed;
    Direction d;
    int health;
} Bullet;


/*static void render(Component *self, SDL_Renderer *r) {
    draw_sprite(r, SS_CHARACTER, 6, 11, &((Bullet*)self->data)->position);
    }*/

static void update(Component *self, Entity *e, int dt) {
    Bullet *p = (Bullet*)self->data;
    SDL_Rect mov = {.x = p->xSpeed, .y = p->ySpeed};
    Component *position = ch_get(e->components, "position");
    c_send(position, (Event){.t=POSITIONC_MOVE_REL, .d = &mov});
//    render(self, p->r);
}

static void cleanup(Component *self) {
    free((Bullet*)self->data);
}

Entity *new_bullet(SDL_Renderer *r, int x, int y, double xSpeed, double ySpeed,
                   Direction direction, Teams team, Entity **entities) {
    Entity *ret = malloc(sizeof(Entity));
    ret->render = malloc(sizeof(Component));
    *ret->render = new_drawc(ret, r, SS_CHARACTER, 6, 11);

    ret->components = new_component_hash();
    ch_insert(ret->components, "bullet",
              (Component){.update = update, .cleanup = cleanup});

    ch_insert(ret->components, "position", new_positionc(ret, x, y, 16, 16));

    ch_insert(ret->components, "collide", new_team_collidec(ret, entities));
    ch_insert(ret->components, "team", new_teamc(ret, TEAM_PLAYER));
    
    Component *self = ch_get(ret->components, "bullet");
    self->data = malloc(sizeof(Bullet));
    Bullet *b = (Bullet*)self->data;

    b->xSpeed = xSpeed;
    b->ySpeed = ySpeed;
    b->health = 1;
    
    switch (direction) {
    case DIR_S:
        b->ySpeed += 1.;
        break;
    case DIR_W:
        b->xSpeed -= 1.;
        break;
    case DIR_E:
        b->xSpeed += 1.;
        break;
    case DIR_N:
        b->ySpeed -= 1.;
        break;
    }
    
    b->d = direction;
    return ret;
}
