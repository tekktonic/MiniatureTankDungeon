#ifndef BULLET_H
#define BULLET_H

#include "direction.h"
#include "entity.h"
#include "team.h"

Entity *new_bullet(int x, int y, double xSpeed, double ySpeed,
                   Direction direction, Team team);
#endif
