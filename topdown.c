#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "sprite.h"
#include "entity.h"
#include "player.h"

const unsigned char *keyboard;

void render_base_room(SDL_Renderer *r) {
    SDL_Rect dstrect;
    for (int i = 16; i < (768); i += 32){
        for (int ii = 16; ii < 1024; ii += 32) {
            dstrect.y = i;
            dstrect.x = ii;
            if (i == 16 || i == 768-16
                || ii == 16 || ii == 1024-16) {
                
                draw_sprite(r, SS_BASIC, 0, 0, &dstrect);
            }
            else {
                draw_sprite(r, SS_BASIC, 0, 1, &dstrect);   
            }
        }
    }
}


int main(int argc, char **argv) {
    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_PNG);

    srand(time(NULL));

    SDL_Window *w = SDL_CreateWindow("Topdown", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1024, 768, 0);

    SDL_Renderer *r = SDL_CreateRenderer(w, -1, SDL_RENDERER_ACCELERATED);

    init_spritesheets(r);
    bool done = false;
    Entity *player = new_player(512, 384);
    while (!done) {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {done = true;}
        }

        keyboard = SDL_GetKeyboardState(NULL);
        player->update(player, 1000/60);
        if (entities[0])
            entities[0]->update(entities[0], 1000/60);
        SDL_RenderClear(r);
    
        render_base_room(r);

        player->render(player, r);
        if (entities[0])
            entities[0]->render(entities[0], r);
        SDL_RenderPresent(r);
        SDL_Delay(1000/60);
//        SDL_Delay(2000);
    }
    IMG_Quit();
    SDL_Quit();
}
