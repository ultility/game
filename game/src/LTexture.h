#include <SDL2/SDL.h>
#include <string>

class LTexture {
    public:
        LTexture();
        ~LTexture();
        SDL_Texture* get_texture();
        void free();
        bool load_texture(std::string path, SDL_Renderer* renderer);
        bool load_texture(std::string path, SDL_Renderer* renderer, Uint8 r, Uint8 g, Uint8 b);
        int get_width();
        int get_height();
        void render(SDL_Renderer*, int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );
    private:
        SDL_Texture* texture;
        int width;
        int height;
        SDL_Renderer renderer;
};