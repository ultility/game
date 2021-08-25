#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include "window.h"
#include "player.h"

using std::cout;
using std::endl;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int FRAMES_PER_JUMP = 8;
const int JUMP_HEIGHT = 20;
const int PARTIAL_JUMP_HEIGHT = 5; 

SDL_Window* window = NULL;

SDL_Renderer* renderer = NULL;

int main() {
    if (init()) {
        int dy = 0;
        int partial_jumps = 0;
        int frame_counter = 0;
        int jump_frame_start = 0;
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
                    case SDLK_w:
                        if (p.is_touching(0,SCREEN_HEIGHT,SCREEN_WIDTH, SCREEN_HEIGHT)) {
                            dy = (JUMP_HEIGHT / PARTIAL_JUMP_HEIGHT);
                            jump_frame_start = frame_counter % (FRAMES_PER_JUMP / (JUMP_HEIGHT / PARTIAL_JUMP_HEIGHT));
                        }
                        cout << "w was pressed" << endl;
                    default:
                        break;
                    }
                }
            }
            if (dy != 0 && frame_counter % (FRAMES_PER_JUMP / (JUMP_HEIGHT / PARTIAL_JUMP_HEIGHT)) == jump_frame_start) {
                cout << "jump" << dy << endl;
                p.move(0,dy);
                partial_jumps++;
                if (partial_jumps == JUMP_HEIGHT / PARTIAL_JUMP_HEIGHT) {
                    dy = -dy;
                }
                else if (partial_jumps == JUMP_HEIGHT / PARTIAL_JUMP_HEIGHT * 2) {
                    dy = 0;
                    partial_jumps = 0;
                }
            }
            SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
            SDL_RenderClear(renderer); 
            p.render();
            
            SDL_RenderPresent(renderer);
            SDL_ShowWindow(window);   
            frame_counter++;
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