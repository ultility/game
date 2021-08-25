#include "LTexture.h"
#include <SDL2/SDL_image.h>
#include <iostream>

LTexture::LTexture() {
    texture = NULL;
    width = 0;
    height = 0;
}

LTexture::~LTexture() {
    free();
}

SDL_Texture* LTexture::get_texture() {
    return texture;
}

bool LTexture::load_texture(std::string path, SDL_Renderer* renderer, Uint8 r, Uint8 g, Uint8 b) {
    bool success = true;
    free();
    SDL_Surface* surface = IMG_Load(path.c_str());
    if (surface == NULL) {
        printf("error, failed loading surface. path:%s\nerror:%s\n", path.c_str(), IMG_GetError());
        success = false;
    }
    else {
        SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, r, g, b));
        texture = SDL_CreateTextureFromSurface(renderer, surface);
        if (texture == NULL) {
            printf("error, failed loading texture. error:%s\n",SDL_GetError());
            success = false;
        }
        else {
            width = surface->w;
            height = surface->h;
            
        }

        SDL_FreeSurface(surface);
    }

    return success;
}

bool LTexture::load_texture(std::string path, SDL_Renderer* renderer) {
    bool success = true;
    free();
    SDL_Surface* surface = IMG_Load(path.c_str());
    if (surface == NULL) {
        printf("error, failed loading surface. path:%s\nerror:%s\n", path.c_str(), IMG_GetError());
        success = false;
    }
    else {
        texture = SDL_CreateTextureFromSurface(renderer, surface);
        if (texture == NULL) {
            printf("error, failed loading texture. error:%s\n",SDL_GetError());
            success = false;
        }
        else {
            width = surface->w;
            height = surface->h;
            
        }

        SDL_FreeSurface(surface);
    }

    return success;
}

void LTexture::free() {
    SDL_DestroyTexture(texture);
    texture = NULL;

    width = 0;
    height = 0;
}

int LTexture::get_width() {
    return width;
}

int LTexture::get_height() {
    return height;
}

void LTexture::render(SDL_Renderer* renderer, int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip) {
    SDL_Rect render_area = {x, y, width, height};
    //Set clip rendering dimensions
    if( clip != NULL )
    {
        render_area.w = clip->w;
        render_area.h = clip->h;
    }
    SDL_RenderCopyEx(renderer, texture, clip, &render_area, angle, center, flip);
}