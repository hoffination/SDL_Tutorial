//
// Created by Ben Hofferber on 2022-09-04.
//

#include "LCharacter.h"
#include "Renderer.h"
#include "LAnimationSheet.h"

#include <cmath>
#include <fstream>
#include <sstream>
#include <utility>

LCharacter::LCharacter(PointF position) {
    mPosition = position;
}

LCharacter::~LCharacter() {
    free();
}

void LCharacter::load(SDL_Renderer *renderer, const std::vector<AnimationSheet>& animationSheets) {
    mIdleTextures[DOWN_LEFT] = new LAnimatedTexture(animationSheets[0]);
    mIdleTextures[DOWN_LEFT]->load(renderer);
    mIdleTextures[DOWN_RIGHT] = new LAnimatedTexture(animationSheets[1]);
    mIdleTextures[DOWN_RIGHT]->load(renderer);
    mIdleTextures[UP_RIGHT] = new LAnimatedTexture(animationSheets[2]);
    mIdleTextures[UP_RIGHT]->load(renderer);
    mIdleTextures[UP_LEFT] = new LAnimatedTexture(animationSheets[3]);
    mIdleTextures[UP_LEFT]->load(renderer);

    mWalkTextures[DOWN_LEFT] = new LAnimatedTexture(animationSheets[4]);
    mWalkTextures[DOWN_LEFT]->load(renderer);
    mWalkTextures[DOWN_RIGHT] = new LAnimatedTexture(animationSheets[5]);
    mWalkTextures[DOWN_RIGHT]->load(renderer);
    mWalkTextures[UP_RIGHT] = new LAnimatedTexture(animationSheets[6]);
    mWalkTextures[UP_RIGHT]->load(renderer);
    mWalkTextures[UP_LEFT] = new LAnimatedTexture(animationSheets[7]);
    mWalkTextures[UP_LEFT]->load(renderer);
}

void LCharacter::setDestination(PointF destination) {
    mDestination = destination;
}

void LCharacter::render(SDL_Renderer *renderer, int offsetX, int offsetY, Uint32 currentTicks) {
    walkTowardDestination(currentTicks);
    Point renderPosition = Renderer::mapToScreenF(mPosition);

    std::unordered_map<CharacterDirection, LAnimatedTexture*> currentMap;
    if (mSpeed > 0.0f) {
        currentMap = mWalkTextures;
    } else {
        currentMap = mIdleTextures;
    }

    currentMap[mDirection]->render(renderer, renderPosition.x + offsetX, renderPosition.y + offsetY - (getHeight() - 20), currentTicks);
}

void LCharacter::free() {
    for (const auto& kv : mIdleTextures) {
        kv.second->free();
    }
    mIdleTextures.clear();
    for (const auto& kv : mWalkTextures) {
        kv.second->free();
    }
    mWalkTextures.clear();

    mSpeed = 0.0f;
}

int LCharacter::getHeight() {
    if (mSpeed > 0.0f) {
        return mIdleTextures[mDirection]->getHeight();
    } else {
        return mWalkTextures[mDirection]->getHeight();
    }
}

int LCharacter::getWidth() {
    if (mSpeed > 0.0f) {
        return mIdleTextures[mDirection]->getWidth();
    } else {
        return mWalkTextures[mDirection]->getWidth();
    }
}

std::vector<AnimationSheet> LCharacter::parseAnimations(std::string animationFilePath) {
    std::vector<AnimationSheet> animationVector;
    std::ifstream animationFile(animationFilePath );
    if( !animationFile.is_open() )
    {
        printf("Could not open file\n");
        return animationVector;
    }

    std::string line, val;
    if( animationFile.good() )
    {
        // Read first line in the file and ignore
        getline(animationFile, line);
    }

    // Read data, line by line
    while( getline(animationFile, line) )
    {
        // get a stream of the inner line
        std::stringstream ss(line);
        std::vector<std::string> outputs;

        while( ss.good() )
        {
            // split line by commas
            getline(ss, val, ',');
            outputs.push_back(val);
        }

        // if formatted correctly, add to the map
        if (outputs.size() > 6) {
            animationVector.push_back({ outputs[0], stoi(outputs[1]), stoi(outputs[2]), stoi(outputs[3]), stoi(outputs[4]), stoi(outputs[5]), stoi(outputs[6])});
        }
    }

    animationFile.close();
    return animationVector;
}

void LCharacter::walkTowardDestination(Uint32 currentTicks) {
    float dT = (currentTicks - lastUpdate) / 1000.0f;
    if (mDestination.x != -1) {
        if (mSpeed < 2.0f) {
            mSpeed += 0.1f;
        }
        float deltaY = mDestination.y - mPosition.y;
        float deltaX = mDestination.x - mPosition.x;

        // Check if the character has arrived at their destination
        if (abs(deltaX) < 0.1f && abs(deltaY) < 0.1f) {
            mPosition.y = mDestination.y;
            mPosition.x = mDestination.x;
            mSpeed = 0.0f;
            mDestination = { -1, -1 };
            return;
        }

        auto normalizedDistance = (float)sqrt(pow(deltaY, 2) + pow(deltaX, 2));

        // determine direction (math here is hard)
        // ||u||
        auto vectorLength = (float)sqrt(2.0f);
        // U*V
        auto dotProduct = (1.0f * deltaX) + (-1.0f * deltaY);
        // det = x1*y2 - y1*x2
        auto determinant = (1.0f * deltaY) - (-1.0f * deltaX);
        // angle = atan2(det, dot)
        auto angle = atan2(determinant, dotProduct) * 180.0f / 3.1415f;
        if (angle < 90 && angle > 0) {
            mDirection = DOWN_RIGHT;
            printf("down right\n");
        }
        else if (angle > 90 && angle < 180) {
            mDirection = DOWN_LEFT;
            printf("down left\n");
        }
        else if ((angle < 0 && angle > -90) || (angle > 270) ) {
            mDirection = UP_RIGHT;
            printf("up right\n");
        } else {
            mDirection = UP_LEFT;
            printf("up left\n");
        }

//        printf("angle(%f) realAngle(%f) normComp(%f) dotProduct(%f) direction(%d)\n", angle, vectorLength, dotProduct);

        // calculateY distance
        float distanceY = (deltaY / normalizedDistance) * mSpeed * dT;
        float distanceX = (deltaX / normalizedDistance) * mSpeed * dT;

        mPosition.x += distanceX;
        mPosition.y += distanceY;
    }

    lastUpdate = currentTicks;
}