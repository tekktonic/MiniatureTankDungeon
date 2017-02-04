#include "entity.h"
#include "component.h"

#include "components/basic_collidec.h"
#include "components/drawc.h"
#include "components/positionc.h"

Entity *new_wall(SDL_Renderer *r, Entity **entities) {
    Entity *ret = malloc(sizeof(Entity));

    ret->render = malloc(sizeof(Component));
    *ret->render = new_drawc(ret, r, SS_BASIC, 0, 2);

    ret->components = new_component_hash();
    ch_insert(ret->components, "position",
              new_positionc(ret, 32, 32, 32, 256));
    ch_insert(ret->components, "collide",
              new_basic_collidec(ret, entities));

    return ret;
}
