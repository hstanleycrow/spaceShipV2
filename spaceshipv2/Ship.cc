#include <iostream>
#include <conio.h>
#include <windows.h>
#include "screen.h"
#include "config.h"
#include "ship.h"
//#include "color.h"

// using namespace std;

#define SHIPWIDTH 5
#define SHIPHEIGHT 3
#define STARTLIVES 3
#define HEARTSNUMBERS 3
#define SPEED_X 3
#define SPEED_Y 1

Ship::Ship()
{
    setSpeed(SPEED_X, SPEED_Y);
    setLives(STARTLIVES);
    setRemainingHearts();
}

Ship::~Ship() {}

const int *Ship::getPosX() const { return Pos.getPosX(); }
const int *Ship::getPosY() const { return Pos.getPosY(); }
const int Ship::getLives() const { return lives; }

void Ship::restHearts()
{
    remainingHearts--;
}
void Ship::setSpeed(int speedX, int speedY)
{
    this->speedX = speedX;
    this->speedY = speedY;
}
void Ship::setPos(const int posX, const int posY)
{
    Pos.setPosX(posX);
    Pos.setPosY(posY);
}

const int Ship::getShipHeight() const { return SHIPHEIGHT; }

void Ship::setRemainingHearts()
{
    this->remainingHearts = HEARTSNUMBERS;
}

void Ship::setRemainingHearts(const int remainingHearts)
{
    this->remainingHearts = remainingHearts;
}

void Ship::setLives()
{
    this->lives = STARTLIVES;
}

void Ship::setLives(const int lives)
{
    this->lives = lives;
}

void Ship::render()
{
    /*std::cout << "x,y: " << *Pos.getPosX() << ", " << *Pos.getPosY();
    getch();*/
    Pos.message(*Pos.getPosX() + 2, *Pos.getPosY(), 30, "light_blue");

    Pos.message(*Pos.getPosX() + 1, *Pos.getPosY() + 1, 40, "bright_white");
    Pos.message(*Pos.getPosX() + 2, *Pos.getPosY() + 1, 207, "bright_white");
    Pos.message(*Pos.getPosX() + 3, *Pos.getPosY() + 1, 41, "bright_white");

    Pos.message(*Pos.getPosX(), *Pos.getPosY() + 2, 30, "light_blue");
    Pos.message(*Pos.getPosX() + 1, *Pos.getPosY() + 2, 190, "grey");
    Pos.message(*Pos.getPosX() + 3, *Pos.getPosY() + 2, 190, "grey");
    Pos.message(*Pos.getPosX() + 4, *Pos.getPosY() + 2, 30, "light_blue");
}

void Ship::clear()
{
    Pos.message(*Pos.getPosX(), *Pos.getPosY(), "       ");
    Pos.message(*Pos.getPosX(), *Pos.getPosY() + 1, "       ");
    Pos.message(*Pos.getPosX(), *Pos.getPosY() + 2, "       ");
}

void Ship::move(char keyPressed)
{
    if (keyPressed == KEYLEFT || keyPressed == KEYRIGHT || keyPressed == KEYUP || keyPressed == KEYDOWN)
    {
        clear();
        if (keyPressed == KEYLEFT && *Pos.getPosX() > (LEFTLIMIT + speedX))
            Pos.setPosX(*Pos.getPosX() - speedX);
        if (keyPressed == KEYRIGHT && *Pos.getPosX() < (RIGHTLIMIT - SHIPWIDTH))
            Pos.setPosX(*Pos.getPosX() + speedX);
        if (keyPressed == KEYUP && *Pos.getPosY() > (TOPLIMIT + speedY))
            Pos.setPosY(*Pos.getPosY() - speedY);
        if (keyPressed == KEYDOWN && *Pos.getPosY() < (BOTTOMLIMIT - SHIPHEIGHT))
            Pos.setPosY(*Pos.getPosY() + speedY);
        /* if (keyPressed == 'e')
        {
            restHearts();
            shipDies();
        }
        */
        render();
    }
}

void Ship::move()
{
    char keyPressed;
    if (kbhit())
    {
        keyPressed = getch();
        clear();
        if (keyPressed == KEYLEFT && *Pos.getPosX() > (LEFTLIMIT + speedX))
            Pos.setPosX(*Pos.getPosX() - speedX);
        if (keyPressed == KEYRIGHT && *Pos.getPosX() < (RIGHTLIMIT - SHIPWIDTH))
            Pos.setPosX(*Pos.getPosX() + speedX);
        if (keyPressed == KEYUP && *Pos.getPosY() > (TOPLIMIT + speedY))
            Pos.setPosY(*Pos.getPosY() - speedY);
        if (keyPressed == KEYDOWN && *Pos.getPosY() < (BOTTOMLIMIT - SHIPHEIGHT))
            Pos.setPosY(*Pos.getPosY() + speedY);
        /*if (keyPressed == 'e')
        {
            restHearts();
            shipDies();
            Pos.moveTo(20, 2);
            std::cout << "Mori manual";
            getch();
            Pos.moveTo(20, 2);
            std::cout << "             ";
        }*/
        render();
        renderLives();
    }
}

void Ship::delLives()
{
    Pos.message(66, 2, "             ");
}

void Ship::renderLives()
{
    Pos.message(60, 2, "Lives ");
    delLives();
    for (int i = 0; i < lives; i++)
    {
        Pos.message(66 + i, 2, 199, "green");
    }
}

void Ship::delHeart()
{
    Pos.message(100, 2, "     ");
}

void Ship::renderHearts()
{
    Pos.message(92, 2, "Health");
    delHeart();
    for (int i = 0; i < remainingHearts; i++)
    {
        Pos.message(100 + i, 2, 3, "red");
    }
}

bool Ship::shipIsDestroyed()
{
    return (remainingHearts == 0) ? true : false;
}

void Ship::shipDies()
{
    clear();
    for (int i = 0; i < 2; i++)
    {
        Pos.message(*Pos.getPosX(), *Pos.getPosY(), "   **   ", "white");
        Pos.message(*Pos.getPosX(), *Pos.getPosY() + 1, "  ****  ", "red");
        Pos.message(*Pos.getPosX(), *Pos.getPosY() + 2, "   **   ", "yellow");
        Sleep(200);
        clear();

        Pos.message(*Pos.getPosX(), *Pos.getPosY(), " * ** *", "red");
        Pos.message(*Pos.getPosX(), *Pos.getPosY() + 1, "  **** ", "yellow");
        Pos.message(*Pos.getPosX(), *Pos.getPosY() + 2, " * ** *", "white");
        Sleep(200);
        clear();
    };
    lives--;
    setRemainingHearts(HEARTSNUMBERS);
    renderLives();
    render();
}

void Ship::shipCrash()
{
    restHearts();
    clear();
    render();
    if (shipIsDestroyed())
        shipDies();
    renderHearts();
    renderLives();
}