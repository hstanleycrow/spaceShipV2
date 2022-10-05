#ifndef ASTEROIDS_ASTEROID_H_
#define ASTEROIDS_ASTEROID_H_

class Asteroid
{
private:
    Screen Pos;
    int speed;

public:
    Asteroid();
    ~Asteroid();
    void setPos(const int, const int);
    void set();
    void del();
    void render();
    void move();
    const int *getPosX() const;
    const int *getPosY() const;
    void setSpeed(int);
};

#endif /*ASTEROIDS_ASTEROID_H_*/