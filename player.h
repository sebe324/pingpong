#ifndef PLAYER_H
#define PLAYER_H
#include "entity.h"
class Player: public Entity{
    private:
        int score;
        int btnUp, btnDown, btnLeft, btnRight;
        int velocity;
    public:
    Player(float x, float y, int w, int h, unsigned int c, int btn1, int btn2, int btn3, int btn4, int vel);
    Player(float x, float y, int w, int h, unsigned int c, int s);
    Player();
    void setScore(int s);
    int getScore();
    void setBtnUp(int btn);
    int getBtnUp();
    void setBtnDown(int btn);
    int getBtnDown();
    void setBtnLeft(int btn);
    int getBtnLeft();
    void setBtnRight(int btn);
    int getBtnRight();
    void incScore();
    int getVelocity();
    void setVelocity(int vel);
};
#endif
