//
// Created by Ben Hofferber on 2022-09-01.
//

#ifndef SDL_TUTORIAL_RENDERER_H
#define SDL_TUTORIAL_RENDERER_H

struct Point {
    int x;
    int y;
};

class Renderer {
public:
    static Point mapToScreen(Point mapCoordinate, int tileWidth, int tileHeight);
    static Point screenToMap(Point screenCoordinate, int tileWidth, int tileHeight);
};


#endif //SDL_TUTORIAL_RENDERER_H
