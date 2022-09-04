//
// Created by Ben Hofferber on 2022-09-03.
//
#include <SDL.h>
#include <string>
#include <vector>
#include "LTexture.h"
#include "LAnimationSheet.h"

#ifndef SDL_TUTORIAL_LANIMATEDTEXTURE_H
#define SDL_TUTORIAL_LANIMATEDTEXTURE_H


class LAnimatedTexture {
public:
    //Initializes variables
    LAnimatedTexture( std::string path, int frameCount, int w, int h, int renderW, int renderH, int fps );
    explicit LAnimatedTexture( const AnimationSheet& sheet );

    //Deallocates Memory
    ~LAnimatedTexture();

    void load( SDL_Renderer* renderer );

    void render( SDL_Renderer* renderer, int x, int y, Uint32 currentTicks );

    void free();

    int getHeight();
    int getWidth();
private:
    std::string filename;
    int frameCount, currentFrame, w, h, renderW, renderH, fps;
    LTexture gTexture;
    std::vector<SDL_Rect> gSpriteClips;
    float lastUpdate;
};


#endif //SDL_TUTORIAL_LANIMATEDTEXTURE_H
