#ifndef STREAK_H
#define STREAK_H

class Streak
{
public:
    Streak(unsigned int l);

    unsigned int GetLength();
    bool Solved;

private:
    unsigned int length;
};

#endif // STREAK_H
