#include "LTexture.h"

class Tile {
    public:
        Tile(int x, int y);
        void expand(int left, int right, int up, int down);
        void render();
    private:
        SDL_Rect area;
        LTexture texture;
}