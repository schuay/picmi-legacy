#ifndef SPRITE_H
#define SPRITE_H

#include <string>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_gfxPrimitives.h>
#include <SDL/SDL_rotozoom.h>
#include "PicrossException.h"
#include "GB_Globals.h"

class Sprite
{
public:
    Sprite();
    ~Sprite();

    void Load(std::string Filename, unsigned int Zoom, unsigned int Rotation);
    void Blit(int x, int y);

private:

    void Zoom(unsigned int Zoom);
    void Rotate(unsigned int Rotation); /* customized for my needs, 90/180/270 degrees and square sprites only */

    SDL_Surface *Surface;
};

#endif // SPRITE_H
