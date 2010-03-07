#include "Text.h"

Text::Text()
{
    font = NULL;
}

Text::~Text() {
    if (font)
        TTF_CloseFont(font);

}

void Text::Load(std::string Filename) {
    if (font)
        throw PicrossException("Font already loaded, Text::Load cannot be called twice.");

    font = TTF_OpenFont(Filename.c_str(), 18);

    if (!font)
        throw PicrossException(TTF_GetError());
}

void Text::Blit(std::string txt, Point p, unsigned int justify) {
    if (!font)
        throw PicrossException("Text::Blit failed, no font loaded.");

    SDL_Color c = {0,0,0};
    SDL_Rect to;
    SDL_Surface *s = NULL;

    s = TTF_RenderText_Solid(
            font,
            txt.c_str(),
            c);

    to.w = to.h = 1000; //should be enough to draw all strings
    to.y = p.y;
    if (justify == JUSTIFY_R)
        to.x = p.x - s->w;
    else if (justify == JUSTIFY_C)
        to.x = p.x - s->w / 2;
    else
        to.x = p.x;

    if (!s)
        throw PicrossException("Text::Blit failed, TTF_RenderText failed");

    SDL_BlitSurface(s, NULL, Screen, &to);
    SDL_FreeSurface(s);
}
