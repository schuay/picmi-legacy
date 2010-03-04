/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "Puzzle.h"

Puzzle::Puzzle(unsigned int w, unsigned int h, std::string map) :
        ColStreaks(NULL), RowStreaks(NULL), Map(NULL), BoardState(NULL)
{
    if (map.length() < w*h)
        throw PicrossException("Input map has incorrect size");

    Width = w;
    Height = h;

    Map = new char[w*h];
    BoardState = new char[w*h];

    for (unsigned int i=0; i < w*h; i++)
        BoardState[i] = MAP_CLEAN;

    for (unsigned int i=0; i < w*h; i++)
        if (map[i] == MAP_TRUE || map[i] == MAP_FALSE)
            Map[i] = map[i];
        else throw PicrossException("Illegal character in input map");

    CalculateStreaks();
}

Puzzle::~Puzzle() {

    if (Map)
        delete[] Map;
    if (BoardState)
        delete[] BoardState;

    if (ColStreaks)
        delete[] ColStreaks;
    if (RowStreaks)
        delete[] RowStreaks;
}

void Puzzle::CalculateStreaks() {
    unsigned int
            i, j,
            lenOfCurrRowStreak,
            lenOfCurrColStreak;

    RowStreaks = new std::vector<int>[Height];
    ColStreaks = new std::vector<int>[Width];

    /* calculate the numbers to show in rows */
    for(i = 0; i < Height; i++) {
        lenOfCurrRowStreak = 0;

        for(j = 0; j < Width; j++) {
            if (Map[i*Width + j] == MAP_TRUE)
                lenOfCurrRowStreak++;
            else if (lenOfCurrRowStreak > 0) {
                RowStreaks[i].push_back(lenOfCurrRowStreak);
                lenOfCurrRowStreak = 0;
            }
        }

        if (lenOfCurrRowStreak > 0)
            RowStreaks[i].push_back(lenOfCurrRowStreak);
    }

    /* calculate the numbers to show in columns */
    for(i = 0; i < Width; i++) {
        lenOfCurrColStreak = 0;

        for(j = 0; j < Height; j++) {
            if (Map[j*Width + i] == MAP_TRUE)
                lenOfCurrColStreak++;
            else if (lenOfCurrColStreak > 0) {
                ColStreaks[i].push_back(lenOfCurrColStreak);
                lenOfCurrColStreak = 0;
            }
        }

        if (lenOfCurrColStreak > 0)
            ColStreaks[i].push_back(lenOfCurrColStreak);
    }
}
