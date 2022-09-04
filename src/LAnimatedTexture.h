//
// Created by Ben Hofferber on 2022-09-03.
//
#include <SDL.h>
#include <string>
#include "LTexture.h"

#ifndef SDL_TUTORIAL_LANIMATEDTEXTURE_H
#define SDL_TUTORIAL_LANIMATEDTEXTURE_H


class LAnimatedTexture {
public:
    //Initializes variables
    LAnimatedTexture( std::string path, int frameCount, int w, int h, int renderW, int renderH );

    //Deallocates Memory
    ~LAnimatedTexture();

    void load( SDL_Renderer* renderer );

    void render( SDL_Renderer* renderer, int x, int y, Uint32 currentTicks );

    int getWidth();
    int getHeight();
private:
    std::string filename;
    int frameCount, currentFrame, w, h, renderW, renderH;
    LTexture gTexture;
    SDL_Rect *gSpriteClips = NULL;
    float lastUpdate;
};


#endif //SDL_TUTORIAL_LANIMATEDTEXTURE_H
