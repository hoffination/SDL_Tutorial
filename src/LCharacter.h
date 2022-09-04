//
// Created by Ben Hofferber on 2022-09-04.
//

#ifndef SDL_TUTORIAL_LCHARACTER_H
#define SDL_TUTORIAL_LCHARACTER_H

#include <string>
#include "LAnimatedTexture.h"
#include "Renderer.h"

struct AnimationSheet {
    int frameCount;
    int w;
    int h;
    int renderW;
    int renderH;
};

class LCharacter {
public:
    LCharacter( std::string idlePath, std::string walkDownPath, PointF position );
    ~LCharacter();

    void load( SDL_Renderer* renderer, AnimationSheet idleSheet, AnimationSheet walkSheet );

    void render( SDL_Renderer* renderer, int offsetX, int offsetY, Uint32 currentTicks );

    void free();

    int getHeight();
    int getWidth();

private:
    PointF mPosition;
    std::string mIdleDownPath;
    LAnimatedTexture* mIdleDownTexture;
    std::string mWalkDownPath;
    LAnimatedTexture* mWalkDownTexture;
};


#endif //SDL_TUTORIAL_LCHARACTER_H
