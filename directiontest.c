#include <stdio.h>
#include "direction.h"

int main(void){
    Direction directions[] = {DIR_N, DIR_E, DIR_S, DIR_W,
                              DIR_N|DIR_W, DIR_S|DIR_E, 0};
    for (int i = 0; directions[i]; i++) {
        printf("%x %x\n", directions[i], swap_direction(directions[i]));
    }
}
