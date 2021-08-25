#include "player.h"
#include <SDL2/SDL_image.h>
#include <iostream>

Player::Player(SDL_Renderer* renderer, double x, double y) {
    (*this).x = x;
    (*this).y = y;
    (*this).renderer = renderer;
    look_direction = RIGHT;
    current_animation = STANDING;
    texture = new LTexture();
    texture->load_texture("../images/player.png",renderer);
}

void Player::render() {
    SDL_Rect player_area;
    player_area.w = texture->get_width() / ANIMATION_TOTAL;
    player_area.h = texture->get_height();
    player_area.x = player_area.w * current_animation;
    player_area.y = 0;
    SDL_RendererFlip flip;
    if (look_direction == RIGHT) {
        flip = SDL_FLIP_NONE;
    }
    else {
        flip = SDL_FLIP_HORIZONTAL;
    }
    texture->render(renderer,x,y, &player_area ,0 , NULL, flip);
}

int Player::get_height() {
    return texture->get_height();
}

int Player::get_width() {
    return texture->get_width() / ANIMATION_TOTAL;
}

bool Player::set_coordinates(double x, double y) {
    int max_width;
    int max_height;
    SDL_GetRendererOutputSize(renderer, &max_width, &max_height);
    if (x >= 0 && x <= max_width && y >= 0 && y <= max_height) {
        (*this).x = x;
        (*this).y = y;
        return true;
    }
    return false;
}

void Player::move(double dx, double dy) {
    int max_width;
    int max_height;
    SDL_GetRendererOutputSize(renderer, &max_width, &max_height);
    if (x + dx > 0 && x + dx <= max_width && y - dy> 0 && y - dy <= max_height) {
        x += dx;
        y -= dy;
        current_animation++;
        current_animation %= 2;
        if (dx < 0) {
            look_direction = LEFT;
        }
        else if (dx > 0){
            look_direction = RIGHT;
        }
    }
}