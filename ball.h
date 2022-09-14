#ifndef BALL_H
#define BALL_H
#include "entity.h"
class Ball : public Entity{
    float bounce;
    float velX;
    float velY;
public:
    Ball(float x,float y,int w,int h, unsigned int c, float b);
    Ball();
    void setBounce(float b);
    float getBounce();
    float getVelX();
    void setVelX(float x);
    float getVelY();
    void setVelY(float y);

    };
#endif
