#include "team_collidec.h"
#include "collidec.h"

#include "positionc.h"
#include "../entity.h"

static Direction check_collision(Entity *self, Entity *that) {
    Direction ret = 0;
    SDL_Rect first = *(SDL_Rect*)ch_get(self->components, "position")->data;
    SDL_Rect other = *(SDL_Rect*)ch_get(that->components, "position")->data;
    
    // my x, my y, etc
    int mx = first.x;
    int my = first.y;
    int mx2 = first.x + first.w;
    int my2 = first.y + first.h;

    int ox = other.x;
    int oy = other.y;
    int ox2 = other.x + other.w;
    int oy2 = other.y + other.h;
           
    if ((mx <= (ox2 + 1) && mx2 >= ox)) {
        ret |= DIR_W;
    }
    else if (((ox - 1) <= mx2 && ox2 >= mx)) {
        ret |= DIR_E;
    }

    if (((oy - 1) <= my2 && oy2 >= my)) {
        ret |= DIR_S;
    }    
    else if ((my <= (oy2 + 1) && my2 >= oy)) {
        ret |= DIR_N;
    }
    
    
    if (!((ret & (DIR_S | DIR_N))&& (ret & (DIR_E | DIR_W))))
        ret = 0;

    
    return ret;
}

static void collide_basic(Component *self, EventData ed) {
    CollisionData data = *(CollisionData*)ed.data;
    Component *position = ch_get(self->owner->components, "position");
    Component *other_position = data.position;
    Direction d = data.direction;

    SDL_Rect *other_rect = (SDL_Rect*)other_position->data;
    SDL_Rect new_position = *(SDL_Rect*)position->data;

    printf("Being invoked %x\n", d);
    
    if (d & DIR_W) {
        new_position.x = other_rect->x + other_rect->w + 1;
    }
    if (d & DIR_S) {
        new_position.y = other_rect->y - new_position.h - 1;
    }

    if (d & DIR_N) {
        new_position.y = other_rect->y + other_rect->h + 1;
    }
    if (d & DIR_E) {
        new_position.x = other_rect->x - new_position.w - 1;
    }

    c_send(position, (Event){.t=POSITIONC_MOVE, .d=(EventData){.data=&new_position}});
}

static void collide_null(Component *self, EventData ed) {}

static void receive(Component *self, Event e) {
    receivecb callbacks[] = {collide_basic, collide_null};

    callbacks[e.t](self, e.d);
}

static void cleanup(Component *c) {}

static void update(Component *c, Entity *e, int dt) {
    Component *other_collide;
    
    Entity **entities = (Entity**)c->data;
    //This is a minor optimization; later on it may be worth
    //Optimizing more via a spatial hash, but for now deal with n^2
    
    for(int i = 0; i < 256 && entities[i]; i++) {
        if ((other_collide = ch_get(entities[i]->components, "collide"))) {
            // A component with collide *must* have a position
            Direction checked;
            if ((checked = check_collision(c->owner, other_collide->owner))) {

                if (!ch_get(other_collide->owner->components, "team")) {
                Component *other_position = ch_get(other_collide->owner->components,
                                                  "position");

                printf("Found a collision: %d\n", i);
                CollisionData our_collide = {.position=other_position, .direction=checked},
                    their_collide = {ch_get(c->owner->components,"position"),
                                     swap_direction(checked)};
                    
                c_send(other_collide, (Event){.t=COLLIDE_TEAM,
                            .d=(EventData){.data=&their_collide}});

                c_send(c, (Event){.t=(ch_get(other_collide->owner->components, "team")
                                      ? COLLIDE_TEAM : COLLIDE_BASIC),
                                      .d=(EventData){.data=&our_collide}});
                
            }
            }
        }
    }
}

Component new_team_collidec(Entity *e, Entity **entities) {
    Component ret = c_make(e, update, cleanup, receive, NULL);
    ret.data = entities;
    return ret;
}
