#include "GameBlade.h"

class Game {
    public:

    Game();

    void CalcPuzzle(int);
    void DrawPuzzle(int);
    void DrawMattoc(int);
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
		Locked_X,
		Locked_Y,
		plane,
        level,
        level_size,
        mapX,
        mapY,
        realX,
        realY,
        miss,
        hit,
        erase,
        hitcheck,
        check,
		cnt,
		startlir,
		start,
		quit,
		direction,
		animatestart,
		animatequit,
		count,
		tempcount,
		done;

    char
        TEMPMAP[15][15];

    unsigned char
        MattocShowFrame,
        HitMattocShowFrame,
        EraseShowFrame,
        CheckShowFrame,
        EraseBlockShowFrame,
        StartShowFrame,
        QuitShowFrame;

    GB_Sprite
        Black,
        FOUR,
        TEN,
        SIXTEEN,
        Block,
        PushedBlock,
        CheckedBlock,
        Mattoc,
        HitMattoc,
        Erase,
        EraseBlock,
        Check,
        HorBar,
        VertBar,
        Start,
        Quit,
        Title;

    GB_Background BG;

    GB_Sound Bip;
    GB_Sound Hit;

    /* temporary map for puzzle - to be replaced by a mechanism which loads bitmaps from icon folders and converts them to puzzles */
    char puzzleMap[16][16];
};
