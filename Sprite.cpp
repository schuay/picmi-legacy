#include "Sprite.h"

Sprite::Sprite()
{
    Surface = NULL;
}

Sprite::~Sprite() {
    if (Surface)
        SDL_FreeSurface(Surface);
}

void Sprite::Load(std::string Filename, unsigned int ZoomFactor, unsigned int Rotation) {

    if (Surface) {
        SDL_FreeSurface(Surface);
        Surface = NULL;
    }

    Surface = IMG_Load(Filename.c_str());

    if (!Surface) {
        throw PicrossException("Loading sprite failed.");
    }

    if (ZoomFactor != 1)
        Zoom(ZoomFactor);

    if (Rotation != 0)
        Rotate(Rotation);
}

void Sprite::Zoom(unsigned int ZoomFactor) {
    if (!Surface)
        return;

    SDL_Surface *tmpSurface = NULL;

    tmpSurface = rotozoomSurface(Surface, 0, ZoomFactor, 0);

    if (!tmpSurface) {
        throw PicrossException("Zooming sprite failed.");
    }
    else {
        if (Surface)
            SDL_FreeSurface(Surface);
        Surface = tmpSurface;
    }
}

void Sprite::Rotate(unsigned int Rotation) {

    if (!Surface)
        throw PicrossException("Rotating sprite failed: No sprite to rotate.");
    if (!(Rotation < 360 && Rotation%90 == 0))
        throw PicrossException("Rotating sprite failed: Invalid angle.");
    if (Surface->w != Surface->h)
        throw PicrossException("Rotating sprite failed: Sprite is not a square.");

    SDL_Rect from, to;
    SDL_Surface *tmpSurface =
            rotozoomSurface(Surface, Rotation, 1, 0);

    tmpSurface->flags = 0;

    from.h = tmpSurface->h;
    from.w = tmpSurface->w;

    to.h = Surface->h;
    to.w = Surface->w;
    to.x = 0;
    to.y = 0;

    if (!tmpSurface) {
        throw PicrossException("Rotating sprite failed.");
    }
    else {
        switch (Rotation) {
        case 90:
            from.x = 0; //rotozoom doesn't handle rotating even sized images correctly which is why we need this custom handling
            from.y = 1;
            break;
        case 180:
            from.x = 2;
            from.y = 2;
            break;
        case 270:
            from.x = 2;
            from.y = 1;
            break;
        }

        SDL_FillRect(Surface, NULL, 0);
        SDL_BlitSurface(tmpSurface,
                        &from,
                        Surface,
                        &to
                        );
    }

    SDL_FreeSurface(tmpSurface);
}

void Sprite::Blit(int x, int y) {
    SDL_Rect to;

    to.x = x;
    to.y = y;
    to.w = Surface->w;
    to.h = Surface->h;

    if ( SDL_BlitSurface( Surface, NULL, Screen, &to) < 0 )
        throw PicrossException(( "!Error! Blit Surface error: %s.\n", SDL_GetError() ));

}
