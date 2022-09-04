//
// Created by Ben Hofferber on 2022-09-04.
//

#ifndef SDL_TUTORIAL_LCHARACTER_H
#define SDL_TUTORIAL_LCHARACTER_H

#include <string>
#include <unordered_map>
#include "LAnimatedTexture.h"
#include "Renderer.h"
#include "LAnimationSheet.h"

enum CharacterDirection {
    DOWN_LEFT,
    DOWN_RIGHT,
    UP_RIGHT,
    UP_LEFT,
};

class LCharacter {
public:
    LCharacter( PointF position );
    ~LCharacter();

    void load( SDL_Renderer* renderer, const std::vector<AnimationSheet>& animationSheets );

    void setDestination(PointF destination);

    void render( SDL_Renderer* renderer, int offsetX, int offsetY, Uint32 currentTicks );

    void free();

    int getHeight();
    int getWidth();

    static std::vector<AnimationSheet> parseAnimations(std::string animationFilePath);

private:
    PointF mPosition;
    PointF mDestination;
    float mSpeed = 0;
    Uint32 lastUpdate;
    CharacterDirection mDirection = DOWN_LEFT;

    std::unordered_map<CharacterDirection, LAnimatedTexture*> mIdleTextures;
    std::unordered_map<CharacterDirection, LAnimatedTexture*> mWalkTextures;


    void walkTowardDestination( Uint32 currentTicks );
};


#endif //SDL_TUTORIAL_LCHARACTER_H
