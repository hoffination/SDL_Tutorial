//
// Created by Ben Hofferber on 2022-08-28.
//
#include <SDL.h>
#include <SDL_ttf.h>
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

    //Creates image from font string
    bool loadFromRenderedText( TTF_Font* gFont, SDL_Renderer* gRenderer, std::string textureText, SDL_Color textColor );

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

    //Renders at a point with scaling
    void render( SDL_Renderer* gRenderer, int x, int y, int w, int h, SDL_Rect* clip = NULL );


    //Renders texture at given point with rotation/flipping
    void renderSpin( SDL_Renderer *gRenderer, int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );

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
