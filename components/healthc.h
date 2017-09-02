#ifndef HEALTHC_H
#define HEALTHC_H

#include "../component.h"
#include "../entity.h"

typedef enum {
    HEALTH_HEAL,
    HEALTH_HURT,
    HEALTH_UPGRADE
} HealthEvent;

typedef enum {
    HEALTH_CURRENT,
    HEALTH_MAX,
    HEALTH_INVINCIBLE
} HealthQuery;

Component new_healthc(Entity *e, int maxhealth);

#endif
