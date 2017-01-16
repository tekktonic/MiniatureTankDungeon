#include "component.h"

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct ComponentNode {
    Component c;
    char *key;
    struct ComponentNode *next;
} ComponentNode;

#define BUCKET_SIZE 32

typedef struct ComponentHash {
    ComponentNode components[BUCKET_SIZE];
}ComponentHash;

static uint32_t hash(const char *string, uint32_t modvalue) {
    uint32_t star_prime = 3313;
    uint32_t h = 0;

    uint32_t len = strlen(string);

    for (int i = 0; string[i]; i++) {
        h += string[i] * (uint32_t)pow(star_prime, len - i);
    }

    return h % modvalue;
}

void ch_delete(struct ComponentHash *h, char *string) {
    uint32_t offset = hash(string, BUCKET_SIZE);

    ComponentNode *cur = &(h->components[offset]), *tail = NULL;

    while (cur) {
        if (cur->key && !strcmp(cur->key, string)) {
            if (tail) {
                tail->next = cur->next;
            }
            else {
                h->components[offset] = *cur->next;
                free(cur->next);
            }
            break;
        }
        tail = cur;
        cur = cur->next;
    }

    if (cur) {
        cur->c.cleanup(&(cur->c));
        free(cur->key);
        free(cur);
    }
}

Component *ch_get(struct ComponentHash *h, char *string) {
    uint32_t offset = hash(string, BUCKET_SIZE);
    ComponentNode *cur = &(h->components[offset]);
    while (cur) {
        if (cur->key && !strcmp(cur->key, string))
            return &cur->c;
        cur = cur->next;
    }

    return NULL;
}

void ch_insert(struct ComponentHash *h, const char *key, Component c) {
    uint32_t offset = hash(key, BUCKET_SIZE);

    ComponentNode *cur = h->components[offset].next, *tail = &(h->components[offset]);
    while (cur) {
        tail = cur;
        cur = cur->next;
    }

    tail->next = malloc(sizeof(ComponentNode));
    cur = tail->next;
    cur->key = strdup(key);
    cur->c = c;
}

struct ComponentHash *new_component_hash(void) {
    ComponentHash *ret = malloc(sizeof(ComponentHash));
    // Could also memcpy
    for (int i = 0; i < BUCKET_SIZE; i++) {
        ret->components[i] = (ComponentNode){0};
    }

    return ret;
}
