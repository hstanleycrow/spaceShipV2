/**
 * Desarrollado por Harold Crow
 * Septiembre 2022
 * */
#include <iostream>
#include <stdio.h>
#include <windows.h>
#include <string>
#include <conio.h>
#include <stdlib.h>
#include <list>
#include "config.h"
#include "game.h"
/*#include "ship.h"
#include "screen.h"
#include "ship.h"
#include "shoot.h"
#include "asteroid.h"*/

// using namespace std;
using namespace Config;

main()
{
    Game game;
    game.showPresentation();
    while (game.getScreenGameStatus())
    {
        if (game.getGameStatus() == false)
            game.initialize();
    }
    return 0;
}