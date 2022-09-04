//
// Created by Ben Hofferber on 2022-09-04.
//

#ifndef SDL_TUTORIAL_LANIMATIONSHEET_H
#define SDL_TUTORIAL_LANIMATIONSHEET_H

#include <string>

struct AnimationSheet {
    std::string filepath;
    int frameCount;
    int w;
    int h;
    int renderW;
    int renderH;
    int fps;
};
#endif //SDL_TUTORIAL_LANIMATIONSHEET_H
