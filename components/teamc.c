#include "teamc.h"

typedef struct {
    Teams t;
}Team;

void update(Component *c, Entity *e, int dt){}
void cleanup(Component *c){}

void receive(Component *c, int type){}

Component new_teamc(Entity *e, Teams team) {
    Component ret = c_make(e, update, cleanup, receive, NULL);
    return ret;
}
