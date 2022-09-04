//
// Created by Ben Hofferber on 2022-09-04.
//

#include "LCharacter.h"
#include "Renderer.h"

#include <utility>

LCharacter::LCharacter(std::string idlePath, std::string walkDownPath, PointF position) {
    mPosition = position;
    mIdleDownPath = std::move(idlePath);
    mIdleDownTexture = NULL;
    mWalkDownPath = std::move(walkDownPath);
    mWalkDownTexture = NULL;
}

LCharacter::~LCharacter() {
    free();
}

void LCharacter::load(SDL_Renderer *renderer, AnimationSheet idleSheet, AnimationSheet walkSheet) {
    mIdleDownTexture = new LAnimatedTexture(mIdleDownPath, idleSheet.frameCount, idleSheet.w, idleSheet.h, idleSheet.renderW, idleSheet.renderH);
    mIdleDownTexture->load(renderer);
    mWalkDownTexture = new LAnimatedTexture(mWalkDownPath, walkSheet.frameCount, walkSheet.w, walkSheet.h, walkSheet.renderW, walkSheet.renderH);
    mWalkDownTexture->load(renderer);
}

void LCharacter::render(SDL_Renderer *renderer, int offsetX, int offsetY, Uint32 currentTicks) {
    Point renderPosition = Renderer::mapToScreenF(mPosition);
    mWalkDownTexture->render(renderer, renderPosition.x + offsetX, renderPosition.y + offsetY - ( getHeight() - 20 ), currentTicks);
}

void LCharacter::free() {
    mIdleDownTexture->free();
    mIdleDownTexture = NULL;
    mWalkDownTexture->free();
    mWalkDownTexture = NULL;
}

int LCharacter::getHeight() {
    return mIdleDownTexture->getHeight();
}

int LCharacter::getWidth() {
    return mIdleDownTexture->getWidth();
}