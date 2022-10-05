#ifndef ASTEROIDS_CONTROL_H_
#define ASTEROIDS_CONTROL_H_
#include "config.h"

class Control
{
private:
    const char START = (char)ENTER;
    const char STOP = (char)ESC;
    char keyPressed;

public:
    Control();
    ~Control();
    char controlKeyPressed();
};

#endif /* ASTEROIDS_CONTROL_H_ */