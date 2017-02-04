#ifndef DIRECTION_H
#define DIRECTION_H
typedef enum {
    DIR_S = 1,
    DIR_W = 2,
    DIR_E = 4,
    DIR_N = 8
} Direction;

Direction swap_direction(Direction d);
#endif
