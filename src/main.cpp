/*This source code copyrighted by Lazy Foo' Productions (2004-2022)
and may not be redistributed without written permission.*/

//Using SDL and standard IO
#include <SDL.h>
#include <SDL_image.h>
#include <cstdio>
#include "LTexture.h"

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

// Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

//Scene textures
LTexture gFooTexture;
LTexture gBackgroundTexture;

//Scene sprites
SDL_Rect gSpriteCircleClips[ 4 ];
LTexture gSpriteSheetTexture;

// Walking animation
const int WALKING_ANIMATION_FRAMES = 4;
SDL_Rect gSpriteClips[ WALKING_ANIMATION_FRAMES ];
LTexture gWalkingTexture;

bool init()
{
    // Initialization flag
    bool success = true;

    // Initialize SDL
    if (SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
        success = false;
    }
    else
    {
        //Set texture filtering to linear
        if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
        {
            printf( "Warning: Linear texture filtering not enabled!" );
        }

        gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if ( gWindow == NULL )
        {
            printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
            success = false;
        }
        else
        {
            //Create renderer for window (vsynced)
            gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
            if ( gRenderer == NULL )
            {
                printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
                success = false;
            }
            else
            {
                //Initialize renderer color
                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

                // Initialize PNG Loading
                int imgFlags = IMG_INIT_PNG;
                if ( !( IMG_Init(imgFlags) & imgFlags ) )
                {
                    printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
                    success = false;
                }
            }
        }
    }

    return success;
}

bool loadMedia()
{
    //Loading success flag
    bool success = true;

    if( !gFooTexture.loadFromFile("resources/foo.png", gRenderer ) )
    {
        printf( "Failed to load Foo' texture image!\n" );
        success = false;
    }
    else
    {
        gFooTexture.setBlendMode( SDL_BLENDMODE_BLEND );
    }

    if( !gBackgroundTexture.loadFromFile("resources/background.png", gRenderer ) )
    {
        printf( "Failed to load background texture image!\n" );
        success = false;
    }

    //Load sprite sheet texture
    if( !gSpriteSheetTexture.loadFromFile( "resources/dots.png", gRenderer ) )
    {
        printf( "Failed to load sprite sheet texture!\n" );
        success = false;
    }
    else
    {
        //Set top left sprite
        gSpriteCircleClips[ 0 ].x =   0;
        gSpriteCircleClips[ 0 ].y =   0;
        gSpriteCircleClips[ 0 ].w = 100;
        gSpriteCircleClips[ 0 ].h = 100;

        //Set top right sprite
        gSpriteCircleClips[ 1 ].x = 100;
        gSpriteCircleClips[ 1 ].y =   0;
        gSpriteCircleClips[ 1 ].w = 100;
        gSpriteCircleClips[ 1 ].h = 100;

        //Set bottom left sprite
        gSpriteCircleClips[ 2 ].x =   0;
        gSpriteCircleClips[ 2 ].y = 100;
        gSpriteCircleClips[ 2 ].w = 100;
        gSpriteCircleClips[ 2 ].h = 100;

        //Set bottom right sprite
        gSpriteCircleClips[ 3 ].x = 100;
        gSpriteCircleClips[ 3 ].y = 100;
        gSpriteCircleClips[ 3 ].w = 100;
        gSpriteCircleClips[ 3 ].h = 100;
    }

    //Load sprite sheet texture
    if( !gWalkingTexture.loadFromFile( "resources/foo_animated.png", gRenderer ) )
    {
        printf( "Failed to load walking animation texture!\n" );
        success = false;
    }
    else
    {
        //Set sprite clips
        gSpriteClips[ 0 ].x =   0;
        gSpriteClips[ 0 ].y =   0;
        gSpriteClips[ 0 ].w =  64;
        gSpriteClips[ 0 ].h = 205;

        gSpriteClips[ 1 ].x =  64;
        gSpriteClips[ 1 ].y =   0;
        gSpriteClips[ 1 ].w =  64;
        gSpriteClips[ 1 ].h = 205;

        gSpriteClips[ 2 ].x = 128;
        gSpriteClips[ 2 ].y =   0;
        gSpriteClips[ 2 ].w =  64;
        gSpriteClips[ 2 ].h = 205;

        gSpriteClips[ 3 ].x = 192;
        gSpriteClips[ 3 ].y =   0;
        gSpriteClips[ 3 ].w =  64;
        gSpriteClips[ 3 ].h = 205;
    }

    return success;
}

void close()
{
    //Free loaded image
    gFooTexture.free();
    gBackgroundTexture.free();
    gSpriteSheetTexture.free();
    gWalkingTexture.free();

    //Destroy window
    SDL_DestroyRenderer( gRenderer );
    SDL_DestroyWindow( gWindow );
    gWindow = NULL;
    gRenderer = NULL;

    //Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}

int main( int argc, char* args[] )
{
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
            bool quit = false;

            // Event handler
            SDL_Event e;

            //Modulation components
            Uint8 r = 255;
            Uint8 g = 255;
            Uint8 b = 255;
            Uint8 a = 255;

            //Current animation frame
            int frame = 0;

            // While application is running
            while ( !quit )
            {
                while (SDL_PollEvent( &e ) != 0 )
                {
                    // User requests quit
                    if( e.type == SDL_QUIT )
                    {
                        quit = true;
                    }
                        //On keypress change rgb values
                    else if( e.type == SDL_KEYDOWN )
                    {
                        switch( e.key.keysym.sym )
                        {
                            //Increase alpha on r
                            case SDLK_r:
                                if( a + 32 > 255 )
                                {
                                    a = 255;
                                }
                                else
                                {
                                    a += 32;
                                }
                                break;
                            case SDLK_f:
                                if( a - 32 < 0 )
                                {
                                    a = 0;
                                }
                                else
                                {
                                    a -= 32;
                                }
                                break;
                            //Increase red
                            case SDLK_q:
                                r += 32;
                                break;

                                //Increase green
                            case SDLK_w:
                                g += 32;
                                break;

                                //Increase blue
                            case SDLK_e:
                                b += 32;
                                break;

                                //Decrease red
                            case SDLK_a:
                                r -= 32;
                                break;

                                //Decrease green
                            case SDLK_s:
                                g -= 32;
                                break;

                                //Decrease blue
                            case SDLK_d:
                                b -= 32;
                                break;
                        }
                    }
                }

                //Clear screen
                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
                SDL_RenderClear( gRenderer );

                //Render background texture to screen
                gBackgroundTexture.setColor( r, g, b );
                gBackgroundTexture.render( gRenderer, 0, 0 );

                //Render Foo' to the screen
                gFooTexture.setAlpha(a);
                gFooTexture.render( gRenderer, 240, 190 );

                //Render top left sprite
                gSpriteSheetTexture.render( gRenderer, 0, 0, &gSpriteCircleClips[ 0 ] );

                //Render top right sprite
                gSpriteSheetTexture.render( gRenderer, SCREEN_WIDTH - gSpriteCircleClips[ 1 ].w, 0, &gSpriteCircleClips[ 1 ] );

                //Render bottom left sprite
                gSpriteSheetTexture.render( gRenderer, 0, SCREEN_HEIGHT - gSpriteCircleClips[ 2 ].h, &gSpriteCircleClips[ 2 ] );

                //Render bottom right sprite
                gSpriteSheetTexture.render( gRenderer, SCREEN_WIDTH - gSpriteCircleClips[ 3 ].w, SCREEN_HEIGHT - gSpriteCircleClips[ 3 ].h, &gSpriteCircleClips[ 3 ] );

                //Render current frame
                SDL_Rect* currentClip = &gSpriteClips[ frame / 4 ];
                gWalkingTexture.render( gRenderer, ( SCREEN_WIDTH - currentClip->w), ( SCREEN_HEIGHT - currentClip->h ) / 2, currentClip );

                //Update screen
                SDL_RenderPresent( gRenderer );

                //Go to next frame
                ++frame;

                //Cycle animation
                if( frame / 4 >= WALKING_ANIMATION_FRAMES )
                {
                    frame = 0;
                }
            }
        }
    }

    //Free resources and close SDL
    close();

    return 0;
}
