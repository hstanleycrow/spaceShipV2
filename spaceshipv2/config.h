#ifndef ASTEROIDS_CONFIG_H_
#define ASTEROIDS_CONFIG_H_

namespace Config
{
#ifndef SCREENWIDTH
#define SCREENWIDTH 1000
#endif
#ifndef SCREENHEIGHT
#define SCREENHEIGHT 650
#endif
#ifndef LINECHARSIZE
#define LINECHARSIZE 50
#endif
#ifndef ESC
#define ESC 27
#endif
#ifndef ENTER
#define ENTER 13
#endif
#ifndef SPACE
#define SPACE 32
#endif

#ifndef RIGHTLIMIT
#define RIGHTLIMIT 118
#endif

#ifndef BOTTOMLIMIT
#define BOTTOMLIMIT 36
#endif

#ifndef LEFTLIMIT
#define LEFTLIMIT 1
#endif

#ifndef TOPLIMIT
#define TOPLIMIT 3
#endif

#ifndef KEYUP
#define KEYUP 72
#endif
#ifndef KEYLEFT
#define KEYLEFT 75
#endif
#ifndef KEYRIGHT
#define KEYRIGHT 77
#endif
#ifndef KEYDOWN
#define KEYDOWN 80
#endif

}

#endif /*ASTEROIDS_CONFIG_H_*/