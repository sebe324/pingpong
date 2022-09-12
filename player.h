#ifndef PLAYER_H
#define PLAYER_H
#include "entity.h"
class Player: public Entity{
    private:
        int score;
        int btnUp, btnDown;
    public:
    Player(int x, int y, int w, int h, unsigned int c, int btn1, int btn2);
    Player(int x, int y, int w, int h, unsigned int c, int s);
    Player();
    void setScore(int s);
    int getScore();
    void setBtnUp(int btn);
    int getBtnUp();
    void setBtnDown(int btn);
    int getBtnDown();
    void incScore();
};
#endif
