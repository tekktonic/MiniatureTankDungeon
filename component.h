#ifndef COMPONENT_H
#define COMPONENT_H

struct Entity;
struct Component;
typedef void (*updatefun)(struct Component *c, struct Entity *e, int dt);
typedef void (*cleanupfun)(struct Component *c);

typedef struct Component {
    updatefun update;
    cleanupfun cleanup;
} Component;

struct ComponentHash;
typedef void (*ch_iterator)(struct Entity *e, Component *c, void *data);

void ch_delete(struct ComponentHash *h, char *string);
Component *ch_get(struct ComponentHash *h, char *string);
void ch_insert(struct ComponentHash *h, const char *key, Component c);
//void ch_iter(struct ComponentHash *h, ch_iterator i, void *data);

struct ComponentHash *new_component_hash(void);
typedef struct ComponentHash ComponentHash;
#endif
