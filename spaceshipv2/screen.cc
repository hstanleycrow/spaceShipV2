#include <iostream>
#include <windows.h>
#include <string>
#include <conio.h>
#include "config.h"
#include "screen.h"
#include "color.h"

Screen::Screen()
{
    setScreenSize(SCREENWIDTH, SCREENHEIGHT);
    // drawScreenLimitBorders();
    hideCursor();
    hideScrollbars();
    disableMaximize();
}

void Screen::setPosX(const int posX) { this->posX = posX; };
void Screen::setPosY(const int posY) { this->posY = posY; };
const int *Screen::getPosX() const { return &posX; };
const int *Screen::getPosY() const { return &posY; };

void Screen::message(std::string mensaje)
{
    moveTo(10, 20);
    std::cout << mensaje;
    getch();
    moveTo(10, 20);
    std::cout << "                                                                ";
}

/*void Screen::message(int posX, int posY, std::string mensaje)
{
    moveTo(posX, posY);
    std::cout << dye::colorize(mensaje, "white");
}*/
/*void Screen::message(int posX, int posY, char caracter)
{
    moveTo(posX, posY);
    std::cout << caracter;
}*/

void Screen::message(int posX, int posY, char caracter, std::string color)
{
    if (color.empty())
        color = "white";
    moveTo(posX, posY);
    std::cout << dye::colorize((char)caracter, color);
}

void Screen::message(int posX, int posY, std::string mensaje, std::string color)
{
    if (color.empty())
        color = "white";
    moveTo(posX, posY);
    std::cout << dye::colorize(mensaje, color);
}

void Screen::moveTo(const int posX, const int posY)
{
    HANDLE hCon;
    hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD dwPos;
    dwPos.X = posX;
    dwPos.Y = posY;
    SetConsoleCursorPosition(hCon, dwPos);
}

void Screen::hideCursor()
{
    HANDLE hCon;
    hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    _CONSOLE_CURSOR_INFO cci;
    cci.dwSize = 2;
    cci.bVisible = FALSE;
    SetConsoleCursorInfo(hCon, &cci);
}

void Screen::hideScrollbars()
{
    CONSOLE_SCREEN_BUFFER_INFO screenBufferInfo;

    // Get console handle and get screen buffer information from that handle.
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(hConsole, &screenBufferInfo);

    // Get rid of the scrollbar by setting the screen buffer size the same as
    // the console window size.
    COORD new_screen_buffer_size;

    // screenBufferInfo.srWindow allows us to obtain the width and height info
    // of the visible console in character cells.
    // That visible portion is what we want to set the screen buffer to, so that
    // no scroll bars are needed to view the entire buffer.
    new_screen_buffer_size.X = screenBufferInfo.srWindow.Right -
                               screenBufferInfo.srWindow.Left + 1; // Columns
    new_screen_buffer_size.Y = screenBufferInfo.srWindow.Bottom -
                               screenBufferInfo.srWindow.Top + 1; // Rows

    // Set new buffer size
    SetConsoleScreenBufferSize(hConsole, new_screen_buffer_size);
}

void Screen::disableMaximize()
{
    HWND hwnd = GetConsoleWindow();
    DWORD style = GetWindowLong(hwnd, GWL_STYLE);
    style &= ~WS_MAXIMIZEBOX;
    style &= ~WS_MINIMIZEBOX;
    SetWindowLong(hwnd, GWL_STYLE, style);
    SetWindowPos(hwnd, NULL, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE | SWP_FRAMECHANGED);
}

void Screen::drawScreenLimitBorders()
{
    for (int i = LEFTLIMIT; i < RIGHTLIMIT; i++)
    {
        moveTo(i, TOPLIMIT);
        printf("%c", 205);
        moveTo(i, BOTTOMLIMIT);
        printf("%c", 205);
    };
    for (int i = TOPLIMIT; i < BOTTOMLIMIT; i++)
    {
        moveTo(LEFTLIMIT, i);
        printf("%c", 186);
        moveTo(RIGHTLIMIT, i);
        printf("%c", 186);
    };
    moveTo(LEFTLIMIT, TOPLIMIT);
    printf("%c", 201);
    moveTo(LEFTLIMIT, BOTTOMLIMIT);
    printf("%c", 200);
    moveTo(RIGHTLIMIT, TOPLIMIT);
    printf("%c", 187);
    moveTo(RIGHTLIMIT, BOTTOMLIMIT);
    printf("%c", 188);
}

void Screen::clearScreen()
{
    for (int x = 1; x < RIGHTLIMIT; x++)
    {
        for (int y = 1; y < BOTTOMLIMIT; y++)
        {
            moveTo(x, y);
            printf(" ");
        }
    }
    // drawScreenLimitBorders();
}

void Screen::setScreenSize(const int width, const int height)
{
    HWND console = GetConsoleWindow();
    RECT ConsoleRect;
    GetWindowRect(console, &ConsoleRect);
    MoveWindow(console, ConsoleRect.left, ConsoleRect.top, width, height, TRUE);
}