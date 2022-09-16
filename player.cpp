#include "player.h"
#include <iostream>
Player::Player(float x, float y, int w, int h, unsigned int c, int btn1, int btn2, int btn3, int btn4, int vel) : Entity(x,y,w,h,c){
score=0;
btnUp=btn1;
btnDown=btn2;
btnLeft=btn3;
btnRight=btn4;
velocity=vel;
}
Player::Player(float x, float y, int w, int h, unsigned int c, int s) : Entity(x,y,w,h,c){
score=s;
}
Player::Player() : Entity(){}
void Player::setScore(int s){
score=s;
}
int Player::getScore(){
return score;
}
void Player::setBtnUp(int btn){
btnUp=btn;
}
int Player::getBtnUp(){
return btnUp;
}
void Player::setBtnDown(int btn){
btnDown=btn;
}
int Player::getBtnDown(){
return btnDown;
}
void Player::setBtnLeft(int btn){
btnLeft=btn;
}
int Player::getBtnLeft(){
return btnLeft;
}
void Player::setBtnRight(int btn){
btnRight=btn;
}
int Player::getBtnRight(){
return btnRight;
}
void Player::incScore(){
score++;
}
int Player::getVelocity(){
return velocity;
}
void Player::setVelocity(int vel){
velocity=vel;
}
