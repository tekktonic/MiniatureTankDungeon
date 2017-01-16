#include "entity.h"

static head = 0;
void add_entity(Entity *e) {
    e->id = head;
    entities[head++] = e;
}

// THIS LEAKS MEMORY
void delete_entity(int id) {
    for (int i = id + 1; i < 256; i++) {
        entities[i-1] = entities[i];
    }
}
    
