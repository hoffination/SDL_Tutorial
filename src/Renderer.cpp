//
// Created by Ben Hofferber on 2022-09-01.
//

#include "Renderer.h"

Point Renderer::mapToScreen(Point mapCoordinate, int tileWidth, int tileHeight) {
    int x = (mapCoordinate.x - mapCoordinate.y) * (tileWidth / 2);
    int y = (mapCoordinate.x + mapCoordinate.y) * (tileHeight / 2);
    return { x, y };
}
