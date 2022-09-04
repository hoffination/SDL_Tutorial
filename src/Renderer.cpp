//
// Created by Ben Hofferber on 2022-09-01.
//

#include "Renderer.h"
#include <math.h>

Point Renderer::mapToScreen(Point mapCoordinate, int tileWidth, int tileHeight) {
    int x = round((float)(mapCoordinate.x - mapCoordinate.y) * ((float)tileWidth / 2.0f));
    int y = round((float)(mapCoordinate.x + mapCoordinate.y) * ((float)tileHeight / 2.0f));
    return { x, y };
}

Point Renderer::screenToMap(Point screenCoordinate, int tileWidth, int tileHeight) {
    // need to offset to get the top of the block
    float screenX = (float)screenCoordinate.x - 16.0f;
    float screenY = (float)screenCoordinate.y - 18.0f;
    // maths to show how to get from prior functions to new ones
    // equations from mapToScreen
    // x = (mapx - mapy) * (tileW / 2)
    // y = (mapx + mapy) * (tileH / 2)

    // solve for mapx
    // x / (tileW / 2) = (mapx - mapy)
    // mapx = mapy + (x / (tileW / 2))

    // solve for mapy
    // y / (tileH / 2) = mapx + mapy
    // mapy = (y / (tileH / 2)) - mapx

    // replace map.y
    // mapx = (y / (tileH / 2)) - mapx + (x / (tileW / 2))
    // 2mapx = (y / (tileH / 2)) + (x / (tileW / 2))
    // mapx = ( (y / (tileH / 2)) + (x / (tileW / 2)) ) / 2
    int x = round(((screenY / ( (float)tileHeight / 2.0f )) + (screenX / ((float)tileWidth / 2.0f)) ) / 2.0f);

    // replace mapx
    // mapy = (y / (tileH / 2)) - mapy - (x / (tileW / 2))
    // 2mapy = (y / (tileH / 2)) - (x / (tileW / 2))
    // mapy = ( (y / (tileH / 2)) - (x / (tileW / 2)) ) / 2
    int y = round(((screenY / ( (float)tileHeight / 2.0f )) - (screenX / ((float)tileWidth / 2.0f )) ) / 2.0f);
    return { x, y };

}