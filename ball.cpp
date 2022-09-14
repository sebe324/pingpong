#include "ball.h"

Ball::Ball(float x, float y, int w, int h, unsigned int c, float b) : Entity(x,y,w,h,c){
bounce=b;
velX=450;
velY=0;
}
Ball::Ball():Entity(){}
void Ball::setBounce(float b){
bounce=b;
}
float Ball::getBounce(){
return bounce;
}
void Ball::setVelX(float x){
velX=x;
}
float Ball::getVelX(){
return velX;
}
void Ball::setVelY(float y){
velY=y;
}
float Ball::getVelY(){
return velY;
}
