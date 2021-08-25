#include <SDL2/SDL.h>
#include "LTexture.h"
enum look_directions {
    RIGHT,
    LEFT
};
enum animations {
    STANDING,
    WALKING,
    ANIMATION_TOTAL
};

class Player{
    public:
        Player( SDL_Renderer* renderer, double x = 0.0, double y = 0.0);
        void render();
        int get_width();
        int get_height();
        bool set_coordinates(double x, double y);
        void move(double dx, double dy);
        bool is_touching(double left, double top, double right, double bottom);
        bool is_touching(SDL_Rect* area);
    private:
        int look_direction;
        int current_animation;
        double x;
        double y;
        
        LTexture* texture;
        SDL_Renderer* renderer;
};