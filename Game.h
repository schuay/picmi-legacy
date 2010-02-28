#include "GameBlade.h"

class Game {
    public:

    Game();

    void DrawStreaks();
    void DrawPuzzle();
    void DrawMattoc();
    void Initialize();
    void DoMainLoop();

    private:

    /* vars from original 2004 state of game */
    int Puzzle_PositionX,
        Puzzle_PositionY,
	Mattoc_PositionX,
	Mattoc_PositionY,
        VertBar_PositionX,
	HorBar_PositionY,
        level,
        level_size,         //the length of a level side (currently levels must be square)
        mapX,
        mapY,
        realX,
        realY,
        hit,
        erase,
        hitcheck,
        check,
	quit;

    char
        MattocShowFrame,
        HitMattocShowFrame,
        EraseShowFrame,
        CheckShowFrame,
        EraseBlockShowFrame;

    GB_Sprite
        FIFTEEN,
        PushedBlock,
        CheckedBlock,
        Mattoc,
        HitMattoc,
        Erase,
        EraseBlock,
        Check,
        HorBar,
        VertBar,
        Quit;

    GB_Background BG;

    /* temporary map for puzzle - to be replaced by a mechanism which loads bitmaps from icon folders and converts them to puzzles */
    char
        puzzleMap[16][16],
        tempMap[16][16];
};
