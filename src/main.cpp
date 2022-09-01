/*This source code copyrighted by Lazy Foo' Productions (2004-2022)
and may not be redistributed without written permission.*/

//Using SDL and standard IO
#include <SDL.h>
#include <SDL_image.h>
#include <cstdio>
#include <fstream>
#include <vector>
#include <sstream>
#include <unordered_map>
#include "LTexture.h"
#include "Renderer.h"
using namespace std;

struct TileData
{
    string name;
    SDL_Rect dimensions;
};

//Screen dimension constants
const int SCREEN_WIDTH = 860;
const int SCREEN_HEIGHT = 640;

// Starts up SDL and creates window
bool init();

// Loads tile csv file
bool loadTiles();

//Loads media
bool loadMedia();

// Creates map data
bool createMap();

//Frees media and shuts down SDL
void close();

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

//Scene textures
LTexture gBackgroundTexture;

// File Data
unordered_map<string, TileData> tileMap;

// Tile Map
string map[50][50];
Renderer renderer;

//Scene sprites
LTexture gIsometricSpriteSheetTexture;

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

bool loadTiles()
{
    ifstream tilesFile("resources/tiles.csv" );
    if( !tilesFile.is_open() )
    {
        printf("Could not open file\n");
        return false;
    }

    string line, colname, val;
    if( tilesFile.good() )
    {
        // Read first line in the file
        getline(tilesFile, line);
    }

    // Read data, line by line
    while( getline(tilesFile, line) )
    {
        // get a stream of the inner line
        stringstream ss(line);
        vector<string> outputs;

        while( ss.good() )
        {
            // split line by commas
            getline(ss, val, ',');
            outputs.push_back(val);
        }

        // if formatted correctly, add to the map
        if (outputs.size() > 2) {
            tileMap[outputs[0]] = {outputs[0], stoi(outputs[1]), stoi(outputs[2]), 32, 32};
        }
    }

    tilesFile.close();
    return true;
}

bool loadMedia()
{
    //Loading success flag
    bool success = true;

    if( !gBackgroundTexture.loadFromFile("resources/background.png", gRenderer ) )
    {
        printf( "Failed to load background texture image!\n" );
        success = false;
    }

    if( !gIsometricSpriteSheetTexture.loadFromFile( "resources/tiles.png", gRenderer ) )
    {
        printf( "Failed to load isometric tiles!\n" );
        success = false;
    }
    else
    {
        printf("load good\n");
    }

    return success;
}

bool createMap()
{
    int index = 0;
    string keys[10] = { "dirt", "grass", "lava", "metal_floor", "wood_floor", "ice", "patchy_grass", "brick_floor", "sand", "tall_grass"};
    for (auto & row : map) {
        for (auto & column : row) {
            column = keys[index % 10];
            index++;
        }
    }
    return true;
}

void close()
{
    //Free loaded image
    gBackgroundTexture.free();
    gIsometricSpriteSheetTexture.free();

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
        if ( !loadTiles() || !createMap() )
        {
            printf( "Failed to load tiles\n" );
        }
        else
        {
            //Load media
            if ( !loadMedia() )
            {
                printf("Failed to load media!\n");
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

                int offsetx = SCREEN_WIDTH / 2;
                int offsety = -SCREEN_HEIGHT / 2;

                // While application is running
                while (!quit) {
                    while (SDL_PollEvent(&e) != 0) {
                        // User requests quit
                        if (e.type == SDL_QUIT) {
                            quit = true;
                        }
                            //On keypress change rgb values
                        else if (e.type == SDL_KEYDOWN) {
                            switch (e.key.keysym.sym) {
                                    //Increase green
                                case SDLK_w:
                                    offsety += 10;
                                    break;

                                    //Decrease red
                                case SDLK_a:
                                    offsetx += 10;
                                    break;

                                    //Decrease green
                                case SDLK_s:
                                    offsety -= 10;
                                    break;

                                    //Decrease blue
                                case SDLK_d:
                                    offsetx -= 10;
                                    break;
                            }
                        }
                    }

                    //Clear screen
                    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
                    SDL_RenderClear(gRenderer);

                    //Render background texture to screen
                    gBackgroundTexture.render(gRenderer, 0, 0);

                    //Render isometric ground from
                    for (int row = 0; row < 50; row++) {
                        for (int column = 0; column < 50; column++) {
                            Point renderPosition = renderer.mapToScreen({ row, column }, 32, 16 );
                            TileData tile = tileMap[map[row][column]];
                            gIsometricSpriteSheetTexture.render(gRenderer, renderPosition.x + offsetx, renderPosition.y + offsety,&tile.dimensions);
                        }
                    }

                    //Update screen
                    SDL_RenderPresent(gRenderer);
                }
            }
        }
    }

    //Free resources and close SDL
    close();

    return 0;
}
