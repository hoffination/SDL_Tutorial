//
// Created by Ben Hofferber on 2022-08-28.
//
#include <SDL.h>
#include <string>

#ifndef SDL_TUTORIAL_LTEXTURE_H
#define SDL_TUTORIAL_LTEXTURE_H


class LTexture {
public:
    //Initializes variables
    LTexture();

    //Deallocates memory
    ~LTexture();

    //Loads image at specified path
    bool loadFromFile( std::string path, SDL_Renderer* gRenderer );

    //Deallocates texture
    void free();

    //Set color modulation
    void setColor( Uint8 red, Uint8 green, Uint8 blue );

    //Set blending
    void setBlendMode( SDL_BlendMode blending );

    //Set alpha modulation
    void setAlpha( Uint8 alpha );

    //Renders texture at given point
    void render( SDL_Renderer* gRenderer, int x, int y, SDL_Rect* clip = NULL );

    //Gets image dimensions
    int getWidth();
    int getHeight();

private:
    //The actual hardware texture
    SDL_Texture* mTexture;

    //Image dimensions
    int mWidth;
    int mHeight;
};


#endif //SDL_TUTORIAL_LTEXTURE_H
