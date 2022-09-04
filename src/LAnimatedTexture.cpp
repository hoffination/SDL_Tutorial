//
// Created by Ben Hofferber on 2022-09-03.
//

#include <SDL.h>
#include "LAnimatedTexture.h"

LAnimatedTexture::LAnimatedTexture(std::string path, int frameCount, int w, int h, int renderW, int renderH) {
    this->filename = path;
    this->frameCount = frameCount;
    this->currentFrame = 0;
    this->w = w;
    this->h = h;
    this->renderW = renderW;
    this->renderH = renderH;
    this->gSpriteClips = new SDL_Rect[frameCount];
}

LAnimatedTexture::~LAnimatedTexture() {
    gTexture.free();
    delete [] gSpriteClips;
}

void LAnimatedTexture::load(SDL_Renderer* renderer) {
    // Load file based on saved filename
    gTexture.loadFromFile( filename, renderer );

    if (!gSpriteClips) {
        return;
    }

    //Initialize all clips from the texture
    for (int frame = 0; frame < this->frameCount; ++frame) {
        gSpriteClips[frame] = { w * frame, 0, w, h };
    }
}

void LAnimatedTexture::render(SDL_Renderer* renderer, int x, int y ) {
    SDL_Rect* currentClip = &gSpriteClips[currentFrame];
    gTexture.render( renderer, x, y, renderW, renderH, currentClip );
    currentFrame = (currentFrame + 1) % frameCount;
}

int LAnimatedTexture::getHeight() {
    return renderH;
}

int LAnimatedTexture::getWidth() {
    return renderW;
}