//
// Created by Ben Hofferber on 2022-09-03.
//

#include <SDL.h>
#include "LAnimatedTexture.h"

const float ANIMATED_FPS = 10.0f;

LAnimatedTexture::LAnimatedTexture(std::string path, int frameCount, int w, int h, int renderW, int renderH) {
    this->filename = path;
    this->frameCount = frameCount;
    this->currentFrame = 0;
    this->w = w;
    this->h = h;
    this->renderW = renderW;
    this->renderH = renderH;
}

LAnimatedTexture::~LAnimatedTexture() {
    free();
}

void LAnimatedTexture::load(SDL_Renderer* renderer) {
    // Load file based on saved filename
    gTexture.loadFromFile( filename, renderer );

    //Initialize all clips from the texture
    for (int frame = 0; frame < this->frameCount; ++frame) {
        gSpriteClips.push_back({ w * frame, 0, w, h });
    }
}

void LAnimatedTexture::render(SDL_Renderer* renderer, int x, int y, Uint32 currentTicks ) {
    SDL_Rect* currentClip = &gSpriteClips[currentFrame];
    gTexture.render( renderer, x, y, renderW, renderH, currentClip );

    float dt = (currentTicks - lastUpdate) / 1000.0f;
    int framesToUpdate = floor(dt / (1.0f / ANIMATED_FPS));
    if (framesToUpdate > 0) {
        lastUpdate = currentTicks;
        currentFrame = (currentFrame + 1) % frameCount;
    }
}

void LAnimatedTexture::free() {
    gTexture.free();
    gSpriteClips.clear();
}

int LAnimatedTexture::getHeight() {
    return renderH;
}

int LAnimatedTexture::getWidth() {
    return renderW;
}