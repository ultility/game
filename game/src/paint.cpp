#include <SDL2/SDL.h>
#include <stdio.h>
#include <SDL2/SDL_ttf.h>
#include <string>

using std::string;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//Key press surfaces constants
enum KeyPressSurfaces
{
    KEY_PRESS_SURFACE_DEFAULT,
    KEY_PRESS_SURFACE_UP,
    KEY_PRESS_SURFACE_DOWN,
    KEY_PRESS_SURFACE_LEFT,
    KEY_PRESS_SURFACE_RIGHT,
    KEY_PRESS_SURFACE_TOTAL
};

enum coloringBrushs
{
    WHITE,
    RED,
    BLUE,
    BLACK,
    PURPLE,
    BROWN,
    GREEN,
    COLORS_TOTAL
};

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

// loads colors
bool loadColors();

SDL_Color getColor(Uint8,Uint8,Uint8);

//Loads individual image
SDL_Surface* loadSurface( string path );

//The window we'll be rendering to
SDL_Window* gWindow = NULL;
    
//The surface contained by the window
SDL_Surface* gScreenSurface = NULL;

//The images that correspond to a keypress
SDL_Surface* gKeyPressSurfaces[ KEY_PRESS_SURFACE_TOTAL ];

//Current displayed image
SDL_Surface* gCurrentSurface = NULL;

SDL_Color colors[COLORS_TOTAL];

/*int main() {
    //Start up SDL and create window
	if( !init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
		//Load media
		if( !loadMedia() )
		{
			printf( "Failed to load media!\n" );
		}
		else
		{
            //Main loop flag
            bool quit = false;

            //Event handler
            SDL_Event e;

            //Set default current surface
            gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_DEFAULT ];

            //While application is running
            while( !quit )
            {
                //Handle events on queue
                while( SDL_PollEvent( &e ) != 0 )
                {
                    //User requests quit
                    if( e.type == SDL_QUIT )
                    {
                        quit = true;
                    }
                    //User presses a key
                    else if( e.type == SDL_KEYDOWN )
                    {
                        //Select surfaces based on key press
                        switch( e.key.keysym.sym )
                        {
                            case SDLK_UP:
                            gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_UP ];
                            break;
                            case SDLK_DOWN:
                            gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_DOWN ];
                            break;
                            case SDLK_LEFT:
                            gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_LEFT ];
                            break;
                            case SDLK_RIGHT:
                            gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_RIGHT ];
                            break;
                            default:
                            gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_DEFAULT ];
                            break;
                        }
                    }
                }
                //Apply the current image
                SDL_BlitSurface( gCurrentSurface, NULL, gScreenSurface, NULL );
                //Update the surface
                SDL_UpdateWindowSurface( gWindow );
            }
        }
    }
    //Free resources and close SDL
	close();

	return 0;
}*/

int main() {
    if (!init()) {
        printf("failed to initiate");
    }
    else {
        if (!loadColors()) {
            printf("failed to load colors");
        }
        else
        {
            // the main program exit flag;
            bool quit = false;
            // is mouse pressed
            bool pressed = false;;
            // rectangle representing pixel for drawing
            SDL_Rect pixel;
            pixel.w = 1;
            pixel.h = 1;
            // current color representation
            SDL_Rect current_color;
            current_color.h = 15;
            current_color.w = 15;
            current_color.x = SCREEN_WIDTH - current_color.w - 2;
            current_color.y = SCREEN_HEIGHT - current_color.h - 2;
            // border for the color display
            SDL_Rect border;
            border.h = current_color.h + 4;
            border.w = current_color.w + 4;
            border.x = current_color.x - 2;
            border.y = current_color.y - 2;
            // main loop
            int color = 0;
            SDL_FillRect(gScreenSurface, &(gScreenSurface->clip_rect), UINT32_MAX);
            while(!quit) {
                SDL_Event e;
                while (SDL_PollEvent(&e) != 0) {
                    switch (e.type)
                    {
                    case SDL_QUIT:
                        quit = true;
                        break;
                    case SDL_KEYDOWN:
                        switch (e.key.keysym.sym)
                        {
                        case SDLK_LEFT:
                            color--;
                            if (color < 0) {
                                color = COLORS_TOTAL - 1;
                            }
                            break;
                        case SDLK_RIGHT:
                            color++;
                            if (color == COLORS_TOTAL) {
                                color = 0;
                            }
                            break;
                        default:
                            break;
                        }
                        break;
                    case SDL_MOUSEBUTTONDOWN:
                        pressed = true;
                    case SDL_MOUSEMOTION:
                        if (pressed) {
                            pixel.x = e.motion.x;
                            pixel.y = e.motion.y;
                            SDL_FillRect(gScreenSurface, &pixel, SDL_MapRGB(gScreenSurface->format, colors[color].r, colors[color].g, colors[color].b));
                        }
                        break;
                    case SDL_MOUSEBUTTONUP:
                        pressed = false;
                    default:
                        break;
                    }
                    SDL_FillRect(gScreenSurface, &border, 2155905279);
                    SDL_FillRect(gScreenSurface, &current_color, SDL_MapRGB(gScreenSurface->format, colors[color].r, colors[color].g, colors[color].b));
                    SDL_UpdateWindowSurface( gWindow );
                }
            }
        }
    }
    return 0;
}

SDL_Surface* loadSurface( string path )
{
    //Load image at specified path
    SDL_Surface* loadedSurface = SDL_LoadBMP( path.c_str() );
    if( loadedSurface == NULL )
    {
        printf( "Unable to load image %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
    }

    return loadedSurface;
}

bool loadMedia()
{
    //Loading success flag
    bool success = true;

    //Load default surface
    gKeyPressSurfaces[ KEY_PRESS_SURFACE_DEFAULT ] = loadSurface( "../images/press.bmp" );
    if( gKeyPressSurfaces[ KEY_PRESS_SURFACE_DEFAULT ] == NULL )
    {
        printf( "Failed to load default image!\n" );
        success = false;
    }

    //Load up surface
    gKeyPressSurfaces[ KEY_PRESS_SURFACE_UP ] = loadSurface( "../images/up.bmp" );
    if( gKeyPressSurfaces[ KEY_PRESS_SURFACE_UP ] == NULL )
    {
        printf( "Failed to load up image!\n" );
        success = false;
    }

    //Load down surface
    gKeyPressSurfaces[ KEY_PRESS_SURFACE_DOWN ] = loadSurface( "../images/down.bmp" );
    if( gKeyPressSurfaces[ KEY_PRESS_SURFACE_DOWN ] == NULL )
    {
        printf( "Failed to load down image!\n" );
        success = false;
    }

    //Load left surface
    gKeyPressSurfaces[ KEY_PRESS_SURFACE_LEFT ] = loadSurface( "../images/left.bmp" );
    if( gKeyPressSurfaces[ KEY_PRESS_SURFACE_LEFT ] == NULL )
    {
        printf( "Failed to load left image!\n" );
        success = false;
    }

    //Load right surface
    gKeyPressSurfaces[ KEY_PRESS_SURFACE_RIGHT ] = loadSurface( "../images/right.bmp" );
    if( gKeyPressSurfaces[ KEY_PRESS_SURFACE_RIGHT ] == NULL )
    {
        printf( "Failed to load right image!\n" );
        success = false;
    }

    return success;
}

bool init()
{
    
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Create window
		gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Get window surface
			gScreenSurface = SDL_GetWindowSurface( gWindow );
		}
	}

	return success;
}

bool loadColors() {
    colors[WHITE] = getColor(255,255,255);
    colors[RED] = getColor(255,0,0);
    colors[BLUE] = getColor(0,0,255);
    colors[BLACK] = getColor(0,0,0);
    colors[PURPLE] = getColor(128,0,128);
    colors[BROWN] = getColor(165,42,42);
    colors[GREEN] = getColor(0,255,0);
    for (int i = 0; i < COLORS_TOTAL; i++) {
        if (&colors[i] == NULL) {
            return false;
        }
    }
    return true;
}

void close()
{
	//Deallocate surfaces
	for( int i = 0; i < KEY_PRESS_SURFACE_TOTAL; ++i )
	{
		SDL_FreeSurface( gKeyPressSurfaces[ i ] );
		gKeyPressSurfaces[ i ] = NULL;
	}

	//Destroy window
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;

	//Quit SDL subsystems
	SDL_Quit();
}

SDL_Color getColor(Uint8 r, Uint8 g, Uint8 b) {
    SDL_Color c;
    c.r = r;
    c.g = g;
    c.b = b;
    return c;
}

