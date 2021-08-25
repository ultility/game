#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include "window.h"
#include "player.h"

using std::cout;
using std::endl;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDL_Window* window = NULL;

SDL_Renderer* renderer = NULL;

int main() {
    if (init()) {
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
        if (renderer == NULL) {
            cout << "failed to create renderer, error:" << SDL_GetError() << endl;
        }
        else {
        Player p(renderer);
        p.set_coordinates(0, SCREEN_HEIGHT - p.get_height());
        bool quit = false;
        while (!quit) {
            SDL_Event e;
            while (SDL_PollEvent(&e) != 0) {
                if (e.type == SDL_QUIT) {
                    quit = true;
                }
                else if (e.type == SDL_KEYDOWN) {
                    switch (e.key.keysym.sym)
                    {
                    case SDLK_d:
                        p.move(p.get_width(),0);
                        break;
                    case SDLK_a:
                        p.move(-p.get_width(), 0);
                        break;
                    default:
                        break;
                    }
                }
            }
            SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
            SDL_RenderClear(renderer); 
            p.render();
            
            SDL_RenderPresent(renderer);
            SDL_ShowWindow(window);   
        }
        }
    }

    close();
    return 0;
}

bool init() {
    bool success = true;

    if (SDL_Init( SDL_INIT_VIDEO) < 0) {
        cout << "SDL failed to load, error:" << SDL_GetError() << endl;
        success = false;
    }
    else {
        int img_flags = IMG_INIT_JPG | IMG_INIT_PNG;
        if (IMG_Init(img_flags) != img_flags) {
            cout << "SDL_image failed to load, error:" << IMG_GetError() << endl;
            success = false;
        }
        else {
            window = SDL_CreateWindow("game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
            if (window == NULL) {
                cout << "window failed to load, error:" << SDL_GetError() << endl;
                success = false;
            }
        }
    }
    return success;
}

void close() {
    SDL_DestroyWindow(window);
    window = NULL;

    SDL_Quit();
    IMG_Quit();
}