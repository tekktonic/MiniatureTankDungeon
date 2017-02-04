#ifndef DRAWC_H
#define DRAWC_H
#include <SDL2/SDL.h>

#include "../component.h"
#include "../sprite.h"
#include "../entity.h"

typedef enum {
    DRAWC_ROW,
    DRAWC_COL,
    DRAWC_SHEET
} DrawCEvents;

Component new_drawc(Entity *e, SDL_Renderer *r, Spritesheets sheet, int row, int col);

#endif
