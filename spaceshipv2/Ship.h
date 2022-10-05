#ifndef ASTEROIDS_SHIP_H_
#define ASTEROIDS_SHIP_H_
#include "screen.h"

class Ship
{
private:
    Screen Pos;
    int posX, posY;
    int remainingHearts;
    int lives;
    int speedX;
    int speedY;

public:
    Ship();
    ~Ship();
    void setPos(int, int);
    void setSpeed(int, int);
    void setRemainingHearts();
    void setRemainingHearts(int);
    void setLives();
    void setLives(int);
    void render();
    void clear();
    void move();
    void move(char keyPressed);
    void renderLives();
    void delLives();
    void renderHearts();
    void delHeart();
    bool shipIsDestroyed();
    void shipDies();
    void shipCrash();
    void restHearts();
    const int *getPosX() const;
    const int *getPosY() const;
    const int getLives() const;
    const int getShipHeight() const;
};
#endif /*ASTEROIDS_SHIP_H_*/