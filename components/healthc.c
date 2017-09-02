#include "healthc.h"

#include <stdbool.h>

#include "../util.h"

typedef struct {
    int currentHealth;
    int maxHealth;
    bool invincible;
}Health;

static void cleanup(Component *self) {
    free(self->data);
}

static void heal(Component *self, EventData d) {
    ((Health*)self)->currentHealth = MIN(((Health*)self)->currentHealth + d.i,
                                         ((Health*)self)->maxHealth);
}

static void harm(Component *c, EventData d) {

}
static void heal(Component *c, EventData d) {
    
}
static void receive(Component *c, Event e) {
    
}

static void *query(Component *c, HealthQuery type) {
    Health *data = (Health*)c->data;
    switch (HealthQuery) {
    HEALTH_CURRENT:
        return data->maxHealth;
        break;
    HEALTH_MAX:
        return data->currentHealth;
        break;
    HEALTH_INVINCIBLE:
        return data->invincible;
        break;
    }
}

Component new_healthc(Entity *e, int maxhealth) {
    Health *data = malloc(sizeof(Health));

    *data = (Health){.maxHealth = maxhealth,
                     .currentHealth=maxhealth, .invincible=false};

    Component ret = {.data=data, .receive=receive, .cleanup=cleanup,.query=query};
    return ret;
    
}
