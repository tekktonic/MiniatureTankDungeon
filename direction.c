#include "direction.h"

Direction swap_direction(Direction d)
{
    int north = d & 1;
    int east = d & 2;
    int west = d & 4;
    int south = d & 8;

    return (north << 3) | (east << 1) | (west >> 1) | (south >> 3);
}
