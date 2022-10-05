#include <iostream>
#include <conio.h>
#include <windows.h>
#include "config.h"
#include "shot.h"

#define SPEED_Shot 1

Shot::Shot()
{
    setSpeed(SPEED_Shot);
}

Shot::~Shot() {}

const int *Shot::getPosX() const { return Pos.getPosX(); };
const int *Shot::getPosY() const { return Pos.getPosY(); };

void Shot::setSpeed(int speed) { this->speed = speed; }

void Shot::setPos(const int posX, const int posY)
{
    Pos.setPosX(posX);
    Pos.setPosY(posY);
}

void Shot::del()
{
    Pos.message(*getPosX(), *getPosY(), " ");
}

void Shot::move()
{
    del();
    if (*getPosY() > TOPLIMIT + 1)
    {
        Pos.setPosY(*getPosY() - 1);
    }
    Pos.message(*getPosX(), *getPosY(), 248, "bright_white");
}

bool Shot::outLimits()
{
    if (*getPosY() == TOPLIMIT + 1)
    {
        return true;
    }
    return false;
}