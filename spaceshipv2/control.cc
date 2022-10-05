#include <iostream>
#include <conio.h>
#include "control.h"

Control::Control() {}
Control::~Control() {}
char Control::controlKeyPressed()
{
    fflush(stdin);
    keyPressed = getch();
    return keyPressed;
}