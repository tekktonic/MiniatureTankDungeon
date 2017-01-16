#include "event.h"

bool eq_enqueue(EventQueue *q, Event e){
    if (q->head >= 256)
        return false;
    q->queue[head++] = e;
    q->count++;
    return true;
}

Event *eq_dequeue(EventQueue *q) {
    if (q->head == 0)
        return NULL;
    Event *ret = &(q->queue[--q->head]);

    return ret;
}
