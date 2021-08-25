#include <SDL2/SDL.h>
#include "Tile.h"

Tile::Tile(int x, int y, SDL_Renderer renderer) {
    area.x = x;
    area.y = y;
    texture = new LTexture();
    texture.load_texture("../images/tile.png");
    area.w = texture.get_width();
    area.h = texture.get_height();
}

void Tile::expand(int left, int right, int up, int down) {
    area.x -= left;
    area.w += right;
    area.y -= up;
    area.h += down;
    if (area.x < 0) {
        area.x = 0;
    }
    if (area.y < 0) {
        area.y = 0;
    }
}



void Tile::render() {
    texture.render()
}