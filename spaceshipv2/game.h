#ifndef ASTEROIDS_GAME_H_
#define ASTEROIDS_GAME_H_

#include "Ship.h"
#include "control.h"
#include "shot.h"
#include "asteroid.h"

class Game
{
private:
    Screen screen;
    Ship gameShip;
    Control control1;
    std::list<Shot *> shots;
    std::list<Shot *>::iterator itShots;
    std::list<Asteroid *> asteroids;
    std::list<Asteroid *>::iterator itAsteroids;
    int points;
    bool screenGameStatus;
    bool gameStatus;

    void setGameStatus(bool);
    void setScreenGameStatus(bool);
    void changeStatus(bool);
    void on();
    void shoot();
    void showPoints();
    void moveShots();
    void start();
    void stop();
    void play();
    void gameOver();
    void renderShip();
    void readControl();
    bool isActive();
    void setPoints(int);
    void addPoints(int);
    void renderAsteroids();
    void checkShipColision();
    void checkAsteroidColision();
    void checkColisions();
    void checkLives();
    void clearAsteroids();
    const int getPoints();
    char getControl1KeyPressed();

public:
    Game();
    ~Game();
    void initialize();
    const bool getGameStatus() const;
    const bool getScreenGameStatus() const;
    void showPresentation();
};

#endif /*ASTEROIDS_GAME_H_*/