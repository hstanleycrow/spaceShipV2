#include <iostream>
#include <stdio.h>
#include <windows.h>
#include <string>
#include <conio.h>
#include <stdlib.h>
#include <list>
#include "config.h"
#include "game.h"
#include "Ship.h"
#include "asteroid.h"

Game::Game()
{
    on();
}

Game::~Game() {}

void Game::initialize()
{
    char key = getControl1KeyPressed();
    if (key == ENTER)
    {
        start();
        while (getGameStatus())
        {
            play();
        }
    }
    if (key == ESC)
    {
        setScreenGameStatus(false);
        clearAsteroids();
    }
}

void Game::on()
{
    screen.clearScreen();
    setGameStatus(false);
    setScreenGameStatus(true);
}

void Game::play()
{
    if (kbhit())
    {
        fflush(stdin);
        char gameKeyPressed = getControl1KeyPressed();
        if (gameKeyPressed == ESC)
        {
            stop();
            clearAsteroids();
        }
        if (gameKeyPressed == SPACE)
            shoot();
        gameShip.move(gameKeyPressed);
    }
    gameShip.renderLives();
    checkColisions();
    showPoints();
    moveShots();
    if (getGameStatus() == false)
    {
        gameOver();
    }
    Sleep(30);
}
void Game::setGameStatus(bool gameStatus)
{
    this->gameStatus = gameStatus;
}

bool const Game::getGameStatus() const
{
    return gameStatus;
}

void Game::setScreenGameStatus(bool screenGameStatus)
{
    this->screenGameStatus = screenGameStatus;
}

bool const Game::getScreenGameStatus() const
{
    return screenGameStatus;
}

char Game::getControl1KeyPressed()
{
    // screen.message(5, 5, "Segundo paso");
    return control1.controlKeyPressed();
}

void Game::showPresentation()
{
    screen.message((RIGHTLIMIT / 2) - 23, (BOTTOMLIMIT / 2), "PRESS <ENTER> TO START A NEW GAME OR ESC TO EXIT");
}

void Game::gameOver()
{
    clearAsteroids();
    screen.clearScreen();
    stop();
    screen.message((RIGHTLIMIT / 2) - 10, (BOTTOMLIMIT / 2), "                                             ");
    screen.message((RIGHTLIMIT / 2) - 8, (BOTTOMLIMIT / 2), "G A M E   O V E R", "red");
    Sleep(2000);
    setScreenGameStatus(true);
    screen.clearScreen();
    gameShip.~Ship();
    showPresentation();
}

void Game::renderShip()
{
    gameShip.setLives();
    gameShip.setPos((RIGHTLIMIT / 2), (BOTTOMLIMIT - gameShip.getShipHeight()));
    gameShip.render();
    gameShip.renderLives();
    gameShip.renderHearts();
    screen.message(4, 2, "Points");
}
void Game::shoot()
{
    shots.push_back(new Shot());
    itShots = shots.end();
    itShots--;
    (*itShots)->setPos(*gameShip.getPosX() + 2, *gameShip.getPosY() - 1);
}

void Game::checkColisions()
{
    checkAsteroidColision();
    checkShipColision();
    checkLives();
}

void Game::checkShipColision()
{
    // se mueven los asteroides y si chocan con la nave se restan corazones y/o vidas
    for (itAsteroids = asteroids.begin(); itAsteroids != asteroids.end(); itAsteroids++)
    {
        (*itAsteroids)->move();
        if (*(*itAsteroids)->getPosX() >= *gameShip.getPosX() && *(*itAsteroids)->getPosX() < (*gameShip.getPosX() + 6) && *(*itAsteroids)->getPosY() >= *gameShip.getPosY() && *(*itAsteroids)->getPosY() < (*gameShip.getPosY() + 2))
        {
            (*itAsteroids)->del();
            delete (*itAsteroids);
            itAsteroids = asteroids.erase(itAsteroids);
            // screen.message("Me dieron");
            gameShip.shipCrash();
            asteroids.push_back(new Asteroid());
            itAsteroids = asteroids.end();
            itAsteroids--;
            (*itAsteroids)->set();
        }
    }
}

void Game::checkAsteroidColision()
{
    // se verifica si los asteroides chocan con algun disparo, si es asi, se borran y se crea un nuevo asteroide
    for (itAsteroids = asteroids.begin(); itAsteroids != asteroids.end(); itAsteroids++)
    {
        for (itShots = shots.begin(); itShots != shots.end(); itShots++)
        {
            // se verifica si hay colision entre disparo y asteroide
            if ((*(*itAsteroids)->getPosX() == *(*itShots)->getPosX()) && (*(*itAsteroids)->getPosY() + 1 == *(*itShots)->getPosY() || *(*itAsteroids)->getPosY() == *(*itShots)->getPosY()))
            {
                addPoints(5);
                // CODIGO REPETIDO
                // Se borra el disparo
                (*itShots)->del();
                // se borra el puntero al disparo
                delete (*itShots);
                // se borra de la lista tambien para que no quede el espaci
                itShots = shots.erase(itShots);

                // borrar el asteroide
                (*itAsteroids)->del();
                delete (*itAsteroids);
                itAsteroids = asteroids.erase(itAsteroids);
                // se crea un asteroide nuevo CODIGO REPETIDO
                asteroids.push_back(new Asteroid());
                itAsteroids = asteroids.end();
                itAsteroids--;
                (*itAsteroids)->set();
            }
        }
    }
}

void Game::checkLives()
{
    if (gameShip.getLives() == 0)
    {
        setGameStatus(false);
    }
}

void Game::showPoints()
{
    screen.message(11, 2, std::to_string(getPoints()), "yellow");
}

void Game::moveShots()
{
    for (itShots = shots.begin(); itShots != shots.end(); itShots++)
    {
        (*itShots)->move();
        if ((*itShots)->outLimits())
        {
            // Se borra el disparo
            (*itShots)->del();
            // se borra el puntero al disparo
            delete (*itShots);
            // se borra de la lista tambien para que no quede el espaci
            itShots = shots.erase(itShots);
        }
    }
}

void Game::readControl()
{
    // screen.message(5, 5, "Primer paso");
}

void Game::setPoints(int points)
{
    this->points = points;
}

void Game::addPoints(int points)
{
    this->points += points;
}

void Game::changeStatus(bool newStatus)
{
    gameStatus = newStatus;
};

void Game::start()
{
    setPoints(0);
    setScreenGameStatus(false);
    setGameStatus(true);
    screen.clearScreen();
    renderShip();
    renderAsteroids();
}

void Game::renderAsteroids()
{
    for (int i = 0; i < 5; i++)
    {
        asteroids.push_back(new Asteroid());
    }
    for (itAsteroids = asteroids.begin(); itAsteroids != asteroids.end(); itAsteroids++)
    {
        (*itAsteroids)->set();
    }
}

void Game::stop()
{
    setScreenGameStatus(true);
    setGameStatus(false);
}

bool Game::isActive()
{
    return gameStatus;
}
const int Game::getPoints() { return points; }

void Game::clearAsteroids()
{
    for (itAsteroids = asteroids.begin(); itAsteroids != asteroids.end(); itAsteroids++)
    {
        delete (*itAsteroids);
        itAsteroids = asteroids.erase(itAsteroids);
    }
}
