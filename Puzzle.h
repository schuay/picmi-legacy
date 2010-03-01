#ifndef PUZZLE_H
#define PUZZLE_H

#include <string>

class Puzzle
{
public:
    Puzzle(unsigned int, unsigned int, std::string);
    ~Puzzle();

    char
            *Map,
            *BoardState;

    unsigned int
            Width,
            Height;
};

#endif // PUZZLE_H
