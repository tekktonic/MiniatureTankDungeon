#ifndef COLLIDEC_H
#define COLLIDEC_H
#include "../direction.h"
typedef enum {
    COLLIDE_BASIC,
    COLLIDE_TEAM
} CollideCEvents;

typedef struct {
    Component *position;
    Direction direction;
}CollisionData;
    
#endif
