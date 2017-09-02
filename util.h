#ifndef UTIL_H
#define UTIL_H
#include <stdio.h>
#define ORDIE(v, message) do{if (!(v)) {fprintf(stderr, "%s\n", (message));}}while(0)

#define MIN(MIN_SPECIAL_x,MIN_SPECIAL_y) (MIN_SPECIAL_x<MIN_SPECIAL_y?MIN_SPECIAL_x:MIN_SPECIAL_y)
#endif
