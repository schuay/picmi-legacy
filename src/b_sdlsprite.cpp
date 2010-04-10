/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "b_sdlsprite.h"
namespace BoardGame {
SDLSprite::SDLSprite()
{
}

void SDLSprite::SetAsIcon() {
    SDL_WM_SetIcon(Surface.get(), NULL);
}

void SDLSprite::Load(std::string Filename, unsigned int ZoomFactor, unsigned int Rotation) {

    Surface.reset(IMG_Load(Filename.c_str()), SDL_FreeSurface);

    if (!Surface)
        throw Exception("Loading sprite failed.");

    if (ZoomFactor != 1)
        Zoom(ZoomFactor);

    if (Rotation != 0)
        Rotate(Rotation);
}

void SDLSprite::Zoom(unsigned int ZoomFactor) {
    if (!Surface)
        return;

    boost::shared_ptr<SDL_Surface> tmpSurface(
            rotozoomSurface(Surface.get(), 0, ZoomFactor, 0), SDL_FreeSurface);

    if (!tmpSurface)
        throw Exception("Zooming sprite %s failed.");
    else
        Surface = tmpSurface;
}
void SDLSprite::Rotate(unsigned int Rotation) {

    if (!Surface)
        throw Exception("Rotating sprite failed: No sprite to rotate.");
    if (!(Rotation < 360 && Rotation%90 == 0))
        throw Exception("Rotating sprite failed: Invalid angle.");

    SDL_Rect from, to;
    boost::shared_ptr<SDL_Surface> tmpSurface(
            rotozoomSurface(Surface.get(), Rotation, 1, 0), SDL_FreeSurface);

    tmpSurface->flags = 0;  /* reset flags - blitting alpha transp image over another alpha transp image doesn't work */

    from.h = tmpSurface->h;
    from.w = tmpSurface->w;

    to.h = Surface->h;
    to.w = Surface->w;
    to.x = 0;
    to.y = 0;

    if (!tmpSurface)
        throw Exception("Rotating sprite failed.");
    else {
        boost::shared_ptr<SDL_Surface> oldSurface(Surface);
        Surface.reset(SDL_CreateRGBSurface(
                oldSurface->flags,
                oldSurface->h,
                oldSurface->w,
                oldSurface->format->BitsPerPixel,
                oldSurface->format->Rmask,
                oldSurface->format->Gmask,
                oldSurface->format->Bmask,
                oldSurface->format->Amask), SDL_FreeSurface);

        switch (Rotation) { /* rotozoom doesn't handle rotating even sized images correctly */
        case 90:            /* which is why we need this custom handling */
            from.x = 0;
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

        SDL_FillRect(Surface.get(), NULL, 0);
        SDL_BlitSurface(tmpSurface.get(),
                        &from,
                        Surface.get(),
                        &to);
    }
}

void SDLSprite::Blit(boost::shared_ptr<SDL_Surface> target, Point p, int justify) {
    SDL_Rect to, from;

    to.x = p.x;
    to.y = p.y;
    to.w = Surface->w;
    to.h = Surface->h;

    switch (justify) {
    case JUSTIFY_LT:
        from.x = from.y = 0;
        break;
    case JUSTIFY_LB:
        from.x = 0;
        from.y = Surface->h > target->h ?
                 Surface->h - target->h : 0;
        break;
     case JUSTIFY_RT:
         from.x = Surface->w > target->w ?
                  Surface->w - target->w : 0;
         from.y = 0;
         break;
    case JUSTIFY_RB:
        from.x = Surface->w > target->w ?
                 Surface->w - target->w : 0;
        from.y = Surface->h > target->h ?
                 Surface->h - target->h : 0;
        break;
    }

    from.w = Surface->w;
    from.h = Surface->h;

    if ( SDL_BlitSurface( Surface.get(), &from, target.get(), &to) < 0 )
        throw Exception(SDL_GetError());
}
}
