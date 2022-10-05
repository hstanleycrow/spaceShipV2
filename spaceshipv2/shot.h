#ifndef ASTEROIDS_SHOT_H_
#define ASTEROIDS_SHOT_H_

#include "screen.h"

class Shot
{
private:
    Screen Pos;
    int speed;

public:
    Shot();
    ~Shot();
    void setSpeed(int);
    void move();
    bool outLimits();
    void setPos(const int, const int);
    void del();
    const int *getPosX() const;
    const int *getPosY() const;
};

#endif /*ASTEROIDS_SHOT_H_*/