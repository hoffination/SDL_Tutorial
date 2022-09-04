//
// Created by Ben Hofferber on 2022-09-01.
//

#ifndef SDL_TUTORIAL_RENDERER_H
#define SDL_TUTORIAL_RENDERER_H

struct Point {
    int x;
    int y;
};

struct PointF {
    float x;
    float y;
};

const int TILE_WIDTH = 32;
const int TILE_HEIGHT = 16;

class Renderer {
public:
    static Point mapToScreen(Point mapCoordinate);
    static Point mapToScreenF(PointF mapCoordinate);

    static Point screenToMap(Point screenCoordinate);
};


#endif //SDL_TUTORIAL_RENDERER_H
