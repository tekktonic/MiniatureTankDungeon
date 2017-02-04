#include "basic_collidec.h"

#include "../direction.h"
#include "../event.h"

#include "collidec.h"

static void collide_team(Component *c, EventData d) {
}

static void receive(Component *self, Event e) {
    receivecb callbacks[] = {NULL, collide_team};

    callbacks[e.t](self, e.d);
}
static void cleanup(Component *c) {}

static void update(Component *c, Entity *e, int dt){}

Component new_basic_collidec(Entity *e, Entity **entities) {
    Component ret = c_make(e, update, cleanup, receive, NULL);
    ret.data = entities;
    return ret;

}
