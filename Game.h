#include "GameBlade.h"
#include "Puzzle.h"

class Game {
    public:

    Game();
    ~Game();

    void DrawStreaks();
    void ProcessDrawing();
    void ProcessLogic();
    void Initialize();
    void DoMainLoop();

    private:

    unsigned int
        level_size,         //the length of a level side (currently levels must be square)
        mapX,
        mapY;

    /* vars from original 2004 state of game */
    int level,
        hit,
        erase,
        hitcheck,
        check,
        quit,
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

    Puzzle *currentPuzzle;
};
