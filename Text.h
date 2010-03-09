#ifndef TEXT_H
#define TEXT_H

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <string>

#include "Point.h"
#include "PicrossException.h"
#include "Globals.h"

#define JUSTIFY_C   0
#define JUSTIFY_L   1
#define JUSTIFY_R   2

class Text
{
public:
    Text();
    ~Text();

    void Load(std::string Filename);
    void Blit(std::string txt, Point p, unsigned int justify = JUSTIFY_L);
    void Blit(std::string txt, Point p, SDL_Color c, unsigned int justify = JUSTIFY_L);

    static const unsigned int Size = 18;

private:
    TTF_Font *font;
};

#endif // TEXT_H
