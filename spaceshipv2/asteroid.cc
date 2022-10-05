#include <iostream>
#include "screen.h"
#include "config.h"
#include "asteroid.h"
#include "ship.h"

#define SPEED_ASTEROID 1

Asteroid::Asteroid()
{
    setSpeed(SPEED_ASTEROID);
}
Asteroid::~Asteroid() {}
const int *Asteroid::getPosX() const { return Pos.getPosX(); }
const int *Asteroid::getPosY() const { return Pos.getPosY(); }

void Asteroid::setSpeed(int speed)
{
    this->speed = speed;
}

void Asteroid::setPos(const int posX, const int posY)
{
    Pos.setPosX(posX);
    Pos.setPosY(posY);
}

void Asteroid::del()
{
    Pos.moveTo(*getPosX(), *getPosY());
    printf(" ");
}

void Asteroid::render()
{
    Pos.message(*getPosX(), *getPosY(), 220, "yellow");
}

void Asteroid::set()
{
    Pos.setPosX((rand() % (RIGHTLIMIT - 1)) + LEFTLIMIT);
    Pos.setPosY(TOPLIMIT + 1);
}

void Asteroid::move()
{
    del();
    Pos.setPosY(*getPosY() + speed);
    if (*getPosY() > BOTTOMLIMIT - 1)
    {
        set();
    }
    render();
}